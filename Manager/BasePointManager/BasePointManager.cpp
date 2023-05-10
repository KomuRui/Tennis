#include "BasePointManager.h"
#include "../GameManager/GameManager.h"
#include <map>
#include <fstream>
#include "../../Engine/nlohmann/json.hpp"
#include "../../OtherObject/ToolObj/BasePointModel.h"
#include "../../Engine/ResourceManager/Model.h"

using json = nlohmann::json;
using namespace std;

//定数
namespace
{
	//各基準点の名前
	static const string BASE_POINT[] = {
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

	//各軸
	static const string AXIS[] = {
		"X",
		"Y",
		"Z",
	};

	//各jsonファイルのパス
	static const string PLAYER_JSON_PATH = "Tool/BasePoint/BasePointPlayerCourt.json";
	static const string ENEMY_JSON_PATH = "Tool/BasePoint/BasePointEnemyCourt.json";

	//各アンビエント
	static const XMFLOAT4 AMBIENT_COLOR_PLAYER = XMFLOAT4(1.0f, ZERO, ZERO, 1.0f);
	static const XMFLOAT4 AMBIENT_COLOR_ENEMY = XMFLOAT4(1.0f, 1.0f, ZERO, 1.0f);
}

//テニスボールが飛んでいく基準点を管理している名前空間
namespace BasePointManager
{
	///////////////////////////////変数//////////////////////////////////

	map<string, XMFLOAT3> basePointPlayerCourt;
    map<string, XMFLOAT3> basePointEnemyCourt;

	//初期化
	void BasePointManager::Initialize()
	{
		
		// JSONファイルの読み込み
		ifstream ifs_p(PLAYER_JSON_PATH);
		ifstream ifs_e(ENEMY_JSON_PATH);
		json j_p;
		json j_e;
		ifs_p >> j_p;	
		ifs_e >> j_e;

		//基準点分回す
		for (string name : BASE_POINT)
		{
			basePointPlayerCourt[name] = XMFLOAT3(j_p[name]["X"], j_p[name]["Y"], j_p[name]["Z"]);
			basePointEnemyCourt[name] = XMFLOAT3(j_e[name]["X"], j_e[name]["Y"], j_e[name]["Z"]);
		}

	}

	//基準点モデルを生成
	void BasePointManager::InstantiateBasePointModel()
	{
		for (string name : BASE_POINT)
		{
			BasePointModel*p = Instantiate<BasePointModel>(GameManager::GetpSceneManager());
			BasePointModel*e = Instantiate<BasePointModel>(GameManager::GetpSceneManager());

			p->SetPosition(basePointPlayerCourt[name]);
			e->SetPosition(basePointEnemyCourt[name]);

			Model::SetAmbient(p->GetModelNum(), AMBIENT_COLOR_PLAYER);
			Model::SetAmbient(p->GetModelNum(), AMBIENT_COLOR_ENEMY);
		}
	}

	//更新
	void BasePointManager::Update()
	{

	}
}
