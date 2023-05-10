#include "BasePointManager.h"
#include "../GameManager/GameManager.h"
#include <map>
#include <fstream>
#include "../../Engine/nlohmann/json.hpp"
#include "../../OtherObject/ToolObj/BasePointModel.h"

using json = nlohmann::json;
using namespace std;

//�萔
namespace
{
	//�e��_�̖��O
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

	//�e��
	static const string AXIS[] = {
		"X",
		"Y",
		"Z",
	};

	//�ejson�t�@�C���̃p�X
	static const string PLAYER_JSON_PATH = "Tool/BasePoint/BasePointPlayerCourt.json";
	static const string ENEMY_JSON_PATH = "Tool/BasePoint/BasePointEnemyCourt.json";
}

//�e�j�X�{�[�������ł�����_���Ǘ����Ă��閼�O���
namespace BasePointManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	map<string, XMFLOAT3> basePointPlayerCourt;
    map<string, XMFLOAT3> basePointEnemyCourt;

	//������
	void BasePointManager::Initialize()
	{
		
		// JSON�t�@�C���̓ǂݍ���
		ifstream ifs_p(PLAYER_JSON_PATH);
		ifstream ifs_e(ENEMY_JSON_PATH);
		json j_p;
		json j_e;
		ifs_p >> j_p;	
		ifs_e >> j_e;

		//��_����
		for (string name : BASE_POINT)
		{
			basePointPlayerCourt[name] = XMFLOAT3(j_p[name]["X"], j_p[name]["Y"], j_p[name]["Z"]);
			basePointEnemyCourt[name] = XMFLOAT3(j_e[name]["X"], j_e[name]["Y"], j_e[name]["Z"]);
		}

	}

	//��_���f���𐶐�
	void BasePointManager::InstantiateBasePointModel()
	{
		for (string name : BASE_POINT)
		{
			Instantiate<BasePointModel>(GameManager::GetpSceneManager())->SetPosition(basePointPlayerCourt[name]);
			Instantiate<BasePointModel>(GameManager::GetpSceneManager())->SetPosition(basePointEnemyCourt[name]);
		}
	}
}
