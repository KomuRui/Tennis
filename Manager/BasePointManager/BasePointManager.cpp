#include "BasePointManager.h"
#include "../GameManager/GameManager.h"
#include <map>
#include <fstream>
#include "../../Engine/nlohmann/json.hpp"
#include "../../OtherObject/ToolObj/BasePointModel.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../OtherObject/TitleScene/Referee.h"

using json = nlohmann::json;
using namespace std;

//定数
namespace
{
	//ラリー中の各基準点の名前
	static const string RALLY_BASE_POINT[] = {
		"Back_R",
		"Back_C",
		"Back_L",
		"Center_R",
		"Center_C",
		"Center_L",
		"Front_R",
		"Front_C",
		"Front_L",
	};

	//サーブ中の各基準点の名前
	static const string SERVE_BASE_POINT[] = {
		"Right_R",
		"Right_C",
		"Right_L",
		"Left_R",
		"Left_C",
		"Left_L",
	};

	//各軸
	static const string AXIS[] = {
		"X",
		"Y",
		"Z",
	};

	//各jsonファイルのパス
	static const string RALLY_PLAYER1_JSON_PATH = "Tool/BasePoint/RallyBasePointPlayer1Court.json";
	static const string RALLY_PLAYER2_JSON_PATH = "Tool/BasePoint/RallyBasePointPlayer2Court.json";
	static const string SERVE_PLAYER1_JSON_PATH = "Tool/BasePoint/ServeBasePointPlayer1Court.json";
	static const string SERVE_PLAYER2_JSON_PATH = "Tool/BasePoint/ServeBasePointPlayer2Court.json";

	//各アンビエント
	static const XMFLOAT4 RALLY_AMBIENT_COLOR_PLAYER1 = XMFLOAT4(1.0f, ZERO, ZERO, 1.0f);
	static const XMFLOAT4 RALLY_AMBIENT_COLOR_PLAYER2 = XMFLOAT4(1.0f, 1.0f, ZERO, 1.0f);
	static const XMFLOAT4 SERVE_AMBIENT_COLOR_PLAYER1 = XMFLOAT4(ZERO, 1.0f, ZERO, 1.0f);
	static const XMFLOAT4 SERVE_AMBIENT_COLOR_PLAYER2 = XMFLOAT4(ZERO, ZERO, 1.0f, 1.0f);

	//基準点を動かすときの倍率
	static const float MOVE_RATIO = 0.020f;
}

//テニスボールが飛んでいく基準点を管理している名前空間
namespace BasePointManager
{
	///////////////////////////////変数//////////////////////////////////

	//各基準点の位置
	map<string, XMFLOAT3> rallyBasePointPlayer1Court;
    map<string, XMFLOAT3> rallyBasePointPlayer2Court;
	map<string, XMFLOAT3> serveBasePointPlayer1Court;
	map<string, XMFLOAT3> serveBasePointPlayer2Court;

	//選択されている基準点のオブジェクト
	BasePointModel* isSelectBasePointModel;

	//動く状態かどうか
	bool isMove;

	//初期化
	void BasePointManager::Initialize()
	{
		//初期化
		ARGUMENT_INITIALIZE(isSelectBasePointModel, nullptr);
		ARGUMENT_INITIALIZE(isMove, false);

		// JSONファイルの読み込み

		//ラリー
		ifstream ifs_p1(RALLY_PLAYER1_JSON_PATH);
		ifstream ifs_p2(RALLY_PLAYER2_JSON_PATH);
		json j_p1;
		json j_p2;
		ifs_p1 >> j_p1;	
		ifs_p2 >> j_p2;

		//基準点分回す
		for (string name : RALLY_BASE_POINT)
		{
			rallyBasePointPlayer1Court[name] = XMFLOAT3(j_p1[name]["X"], j_p1[name]["Y"], j_p1[name]["Z"]);
			rallyBasePointPlayer2Court[name] = XMFLOAT3(j_p2[name]["X"], j_p2[name]["Y"], j_p2[name]["Z"]);
		}

		//サーブ
		ifstream ifs_Sp1(SERVE_PLAYER1_JSON_PATH);
		ifstream ifs_Sp2(SERVE_PLAYER2_JSON_PATH);
		json j_Sp1;
		json j_Sp2;
		ifs_Sp1 >> j_Sp1;
		ifs_Sp2 >> j_Sp2;

		//基準点分回す
		for (string name : SERVE_BASE_POINT)
		{
			serveBasePointPlayer1Court[name] = XMFLOAT3(j_Sp1[name]["X"], j_Sp1[name]["Y"], j_Sp1[name]["Z"]);
			serveBasePointPlayer2Court[name] = XMFLOAT3(j_Sp2[name]["X"], j_Sp2[name]["Y"], j_Sp2[name]["Z"]);
		}

	}

	//基準点モデルを生成
	void BasePointManager::InstantiateBasePointModel()
	{
		//ラリー中の基準点
		for (string name : RALLY_BASE_POINT)
		{
			BasePointModel*p = Instantiate<BasePointModel>(GameManager::GetpSceneManager());
			BasePointModel*e = Instantiate<BasePointModel>(GameManager::GetpSceneManager());

			p->GetComponent<Transform>()->SetPosition(rallyBasePointPlayer1Court[name]);
			e->GetComponent<Transform>()->SetPosition(rallyBasePointPlayer2Court[name]);

			p->SetBasePointName(name);
			e->SetBasePointName(name);

			p->SetPlayer1CourtType(true);
			e->SetPlayer1CourtType(false);

			ModelManager::SetAmbient(p->GetModelNum(), RALLY_AMBIENT_COLOR_PLAYER1);
			ModelManager::SetAmbient(e->GetModelNum(), RALLY_AMBIENT_COLOR_PLAYER2);

		}

		//サーブ中の基準点
		for (string name : SERVE_BASE_POINT)
		{
			BasePointModel* p = Instantiate<BasePointModel>(GameManager::GetpSceneManager());
			BasePointModel* e = Instantiate<BasePointModel>(GameManager::GetpSceneManager());

			p->GetComponent<Transform>()->SetPosition(serveBasePointPlayer1Court[name]);
			e->GetComponent<Transform>()->SetPosition(serveBasePointPlayer2Court[name]);

			p->SetBasePointName(name);
			e->SetBasePointName(name);

			p->SetPlayer1CourtType(true);
			e->SetPlayer1CourtType(false);

			p->SetServeReceiveBasePoint(true);
			e->SetServeReceiveBasePoint(true);

			ModelManager::SetAmbient(p->GetModelNum(), SERVE_AMBIENT_COLOR_PLAYER1);
			ModelManager::SetAmbient(e->GetModelNum(), SERVE_AMBIENT_COLOR_PLAYER2);

		}
	}

	//更新
	void BasePointManager::Update()
	{
		//マウスをクリックしたのなら
		if (Input::IsMouseButtonDown(0) && Direct3D::GetTwoWindowHandle() == GetForegroundWindow() && !isMove)
		{
			//2つ目のウィンドウでクリックした位置にレイを飛ばしたデータをとってくる
			RayCastData data = Camera::GetTwoWindowClickRayCastData();
			ModelManager::AllRayCast(-1, &data);

			//当たった基準点のオブジェクトがnullならこの先処理しない
			if (data.basePoint == nullptr) return;

			//違う基準点なら選択オブジェを更新
			if (data.basePoint != isSelectBasePointModel) ARGUMENT_INITIALIZE(isSelectBasePointModel, data.basePoint);

			//動く状態に設定
			ARGUMENT_INITIALIZE(isMove, true);
		}
		
		//クリックが離れたら動く状態解除してポジション更新
		if (Input::IsMouseButtonUp(0))
		{
			//解除
			ARGUMENT_INITIALIZE(isMove, false);

			//nullptrならこの先処理しない
			if (isSelectBasePointModel == nullptr) return;

			//プレイヤータイプかどうか
			if (isSelectBasePointModel->isPlaye1CourtType())
				rallyBasePointPlayer1Court[isSelectBasePointModel->GetBasePointName()] = isSelectBasePointModel->GetComponent<Transform>()->GetPosition();
			else								       
				rallyBasePointPlayer2Court[isSelectBasePointModel->GetBasePointName()] = isSelectBasePointModel->GetComponent<Transform>()->GetPosition();

		}

		//動く状態なら
		if (isMove)
		{
			//マウスの動きを取得
			XMFLOAT3 mouseMove = Input::GetMouseMove();

			//現在の位置を取得
			XMFLOAT3 nowPos = isSelectBasePointModel->GetComponent<Transform>()->GetPosition();

			//マウスの移動量分動かす
			isSelectBasePointModel->GetComponent<Transform>()->SetPosition(XMFLOAT3(nowPos.x + mouseMove.y * MOVE_RATIO, nowPos.y, nowPos.z + mouseMove.x * MOVE_RATIO));
		}
	}

	//基準点エクスポート
	void BasePointManager::BasePointExport()
	{
		//JSONファイル
		json j_p;
		json j_e;
		
		//基準点分回す
		for (string name : RALLY_BASE_POINT)
		{
			j_p[name]["X"] = rallyBasePointPlayer1Court[name].x;
			j_p[name]["Y"] = rallyBasePointPlayer1Court[name].y;
			j_p[name]["Z"] = rallyBasePointPlayer1Court[name].z;

			j_e[name]["X"] = rallyBasePointPlayer2Court[name].x;
			j_e[name]["Y"] = rallyBasePointPlayer2Court[name].y;
			j_e[name]["Z"] = rallyBasePointPlayer2Court[name].z;
		}
		
		//JSONファイルの書き込み
		ofstream ofs_p(RALLY_PLAYER1_JSON_PATH);
		ofs_p << j_p;

		ofstream ofs_e(RALLY_PLAYER2_JSON_PATH);
		ofs_e << j_e;
	}

	//基準点を取得
	XMFLOAT3 BasePointManager::GetBasePoint(string name, TennisCourtName n)
	{
		//ラリー中なら
		if (GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_RALLY)
		{
			//プラス方向のコートの基準点取得なら
			if (n == TennisCourtName::Z_PLUS_COURT)
				return rallyBasePointPlayer1Court[name];
			else
				return rallyBasePointPlayer2Court[name];
		}
		//サーブ中なら
		else
		{
			//マイナス方向のコートの基準点取得なら
			if (n == TennisCourtName::Z_PLUS_COURT)
				return serveBasePointPlayer1Court[name];
			else
				return serveBasePointPlayer2Court[name];
		}
	}

	//基準点をランダムに取得
	XMFLOAT3 GetRandomBasePoint(TennisCourtName n)
	{
		//マイナス方向のコートの基準点取得なら
		if (n == TennisCourtName::Z_PLUS_COURT)
			return rallyBasePointPlayer1Court[RALLY_BASE_POINT[Random(0,2)]];
		else
			return rallyBasePointPlayer2Court[RALLY_BASE_POINT[Random(0,2)]];
	}

	//入力に対する基準点の名前を取得
	string GetInputBasePoint(PlayerBase* p)
	{
		//最終的に返す文字列
		string name = "";

		//Lスティックの傾きを取得
		XMFLOAT3 stickL = Input::GetPadStickL(p->GetState()->GetPlayerNum());

		//ラリー中なら
		if (GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_RALLY)
		{
			//奥行
			if (stickL.y > 0.1f)
				name += "Back_";
			else if (stickL.y < -0.1f)
				name += "Front_";
			else
				name += "Center_";

			if (stickL.x < 0.1f && stickL.x > -0.1f)
				name += "C";
			else if (stickL.x < 0.1f)
				name += "L";
			else
				name += "R";
		}
		//サーブレシーブ中なら
		else
		{
			if (stickL.x < 0.1f && stickL.x > -0.1f)
				name += "Left_C";
			else if (stickL.x < 0.1f)
				name += "Left_L";
			else
				name += "Left_R";
		}

		return name;
	}

	//基準点の名前をランダムに取得
	string GetRandomBasePointName() { return RALLY_BASE_POINT[Random(0, 8)]; }
}
