#include "BasePointManager.h"
#include "../GameManager/GameManager.h"
#include <map>
#include <fstream>
#include "../../Engine/nlohmann/json.hpp"
#include "../../OtherObject/ToolObj/BasePointModel.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/GameObject/Camera.h"

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
	static const string SERVE_PLAYER1_JSON_PATH = "Tool/BasePoint/BasePointPlayerCourt.json";
	static const string SERVE_PLAYER2_JSON_PATH = "Tool/BasePoint/BasePointEnemyCourt.json";

	//各アンビエント
	static const XMFLOAT4 RALLY_AMBIENT_COLOR_PLAYER1 = XMFLOAT4(1.0f, ZERO, ZERO, 1.0f);
	static const XMFLOAT4 RALLY_AMBIENT_COLOR_PLAYER2 = XMFLOAT4(1.0f, 1.0f, ZERO, 1.0f);

	//基準点を動かすときの倍率
	static const float MOVE_RATIO = 0.020f;
}

//テニスボールが飛んでいく基準点を管理している名前空間
namespace BasePointManager
{
	///////////////////////////////変数//////////////////////////////////

	//各基準点の位置
	map<string, XMFLOAT3> basePointPlayerCourt;
    map<string, XMFLOAT3> basePointEnemyCourt;

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
		ifstream ifs_p(RALLY_PLAYER1_JSON_PATH);
		ifstream ifs_e(RALLY_PLAYER2_JSON_PATH);
		json j_p;
		json j_e;
		ifs_p >> j_p;	
		ifs_e >> j_e;

		//基準点分回す
		for (string name : RALLY_BASE_POINT)
		{
			basePointPlayerCourt[name] = XMFLOAT3(j_p[name]["X"], j_p[name]["Y"], j_p[name]["Z"]);
			basePointEnemyCourt[name] = XMFLOAT3(j_e[name]["X"], j_e[name]["Y"], j_e[name]["Z"]);
		}

	}

	//基準点モデルを生成
	void BasePointManager::InstantiateBasePointModel()
	{
		for (string name : RALLY_BASE_POINT)
		{
			BasePointModel*p = Instantiate<BasePointModel>(GameManager::GetpSceneManager());
			BasePointModel*e = Instantiate<BasePointModel>(GameManager::GetpSceneManager());

			p->GetComponent<Transform>()->SetPosition(basePointPlayerCourt[name]);
			e->GetComponent<Transform>()->SetPosition(basePointEnemyCourt[name]);

			p->SetBasePointName(name);
			e->SetBasePointName(name);

			p->SetPlayerType(true);
			e->SetPlayerType(false);

			ModelManager::SetAmbient(p->GetModelNum(), RALLY_AMBIENT_COLOR_PLAYER1);
			ModelManager::SetAmbient(e->GetModelNum(), RALLY_AMBIENT_COLOR_PLAYER2);

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
			if (isSelectBasePointModel->isPlayerType())
				basePointPlayerCourt[isSelectBasePointModel->GetBasePointName()] = isSelectBasePointModel->GetComponent<Transform>()->GetPosition();
			else								       
				basePointEnemyCourt[isSelectBasePointModel->GetBasePointName()] = isSelectBasePointModel->GetComponent<Transform>()->GetPosition();

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
			j_p[name]["X"] = basePointPlayerCourt[name].x;
			j_p[name]["Y"] = basePointPlayerCourt[name].y;
			j_p[name]["Z"] = basePointPlayerCourt[name].z;

			j_e[name]["X"] = basePointEnemyCourt[name].x;
			j_e[name]["Y"] = basePointEnemyCourt[name].y;
			j_e[name]["Z"] = basePointEnemyCourt[name].z;
		}
		
		//JSONファイルの書き込み
		ofstream ofs_p(RALLY_PLAYER1_JSON_PATH);
		ofs_p << j_p;

		ofstream ofs_e(RALLY_PLAYER2_JSON_PATH);
		ofs_e << j_e;
	}

	//基準点を取得
	XMFLOAT3 BasePointManager::GetBasePoint(string name, bool isPlayer)
	{
		//プレイヤーの基準点取得なら
		if (isPlayer)
			return basePointPlayerCourt[name];
		else
			return basePointEnemyCourt[name];
	}

	//基準点をランダムに取得
	XMFLOAT3 GetRandomBasePoint(bool isPlayer)
	{
		//プレイヤーの基準点取得なら
		if (isPlayer)
			return basePointPlayerCourt[RALLY_BASE_POINT[Random(0,2)]];
		else
			return basePointEnemyCourt[RALLY_BASE_POINT[Random(0,2)]];
	}

	//基準点の名前をランダムに取得
	string GetRandomBasePointName() { return RALLY_BASE_POINT[Random(0, 8)]; }
}
