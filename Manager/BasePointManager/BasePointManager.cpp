#include "BasePointManager.h"
#include "../GameManager/GameManager.h"
#include <map>
#include <fstream>
#include "../../Engine/nlohmann/json.hpp"
#include "../../OtherObject/ToolObj/BasePointModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Camera.h"

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

	//�e�A���r�G���g
	static const XMFLOAT4 AMBIENT_COLOR_PLAYER = XMFLOAT4(1.0f, ZERO, ZERO, 1.0f);
	static const XMFLOAT4 AMBIENT_COLOR_ENEMY = XMFLOAT4(1.0f, 1.0f, ZERO, 1.0f);

	//��_�𓮂����Ƃ��̔{��
	static const float MOVE_RATIO = 0.020f;
}

//�e�j�X�{�[�������ł�����_���Ǘ����Ă��閼�O���
namespace BasePointManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	//�e��_�̈ʒu
	map<string, XMFLOAT3> basePointPlayerCourt;
    map<string, XMFLOAT3> basePointEnemyCourt;

	//�I������Ă����_�̃I�u�W�F�N�g
	BasePointModel* isSelectBasePointModel;

	//������Ԃ��ǂ���
	bool isMove;

	//������
	void BasePointManager::Initialize()
	{
		//������
		ARGUMENT_INITIALIZE(isSelectBasePointModel, nullptr);
		ARGUMENT_INITIALIZE(isMove, false);

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
			BasePointModel*p = Instantiate<BasePointModel>(GameManager::GetpSceneManager());
			BasePointModel*e = Instantiate<BasePointModel>(GameManager::GetpSceneManager());

			p->SetPosition(basePointPlayerCourt[name]);
			e->SetPosition(basePointEnemyCourt[name]);

			p->SetBasePointName(name);
			e->SetBasePointName(name);

			p->SetPlayerType(true);
			e->SetPlayerType(false);

			ModelManager::SetAmbient(p->GetModelNum(), AMBIENT_COLOR_PLAYER);
			ModelManager::SetAmbient(e->GetModelNum(), AMBIENT_COLOR_ENEMY);

		}
	}

	//�X�V
	void BasePointManager::Update()
	{
		//�}�E�X���N���b�N�����̂Ȃ�
		if (Input::IsMouseButtonDown(0) && Direct3D::GetTwoWindowHandle() == GetForegroundWindow() && !isMove)
		{
			//2�ڂ̃E�B���h�E�ŃN���b�N�����ʒu�Ƀ��C���΂����f�[�^���Ƃ��Ă���
			RayCastData data = Camera::GetTwoWindowClickRayCastData();
			ModelManager::AllRayCast(-1, &data);

			//����������_�̃I�u�W�F�N�g��null�Ȃ炱�̐揈�����Ȃ�
			if (data.basePoint == nullptr) return;

			//�Ⴄ��_�Ȃ�I���I�u�W�F���X�V
			if (data.basePoint != isSelectBasePointModel) ARGUMENT_INITIALIZE(isSelectBasePointModel, data.basePoint);

			//������Ԃɐݒ�
			ARGUMENT_INITIALIZE(isMove, true);
		}
		
		//�N���b�N�����ꂽ�瓮����ԉ������ă|�W�V�����X�V
		if (Input::IsMouseButtonUp(0))
		{
			//����
			ARGUMENT_INITIALIZE(isMove, false);

			//nullptr�Ȃ炱�̐揈�����Ȃ�
			if (isSelectBasePointModel == nullptr) return;

			//�v���C���[�^�C�v���ǂ���
			if (isSelectBasePointModel->isPlayerType())
				basePointPlayerCourt[isSelectBasePointModel->GetBasePointName()] = isSelectBasePointModel->GetPosition();
			else								       
				basePointEnemyCourt[isSelectBasePointModel->GetBasePointName()] = isSelectBasePointModel->GetPosition();

		}

		//������ԂȂ�
		if (isMove)
		{
			//�}�E�X�̓������擾
			XMFLOAT3 mouseMove = Input::GetMouseMove();

			//���݂̈ʒu���擾
			XMFLOAT3 nowPos = isSelectBasePointModel->GetPosition();

			//�}�E�X�̈ړ��ʕ�������
			isSelectBasePointModel->SetPosition(XMFLOAT3(nowPos.x + mouseMove.y * MOVE_RATIO, nowPos.y, nowPos.z + mouseMove.x * MOVE_RATIO));
		}
	}

	//��_�G�N�X�|�[�g
	void BasePointManager::BasePointExport()
	{
		//JSON�t�@�C��
		json j_p;
		json j_e;
		
		//��_����
		for (string name : BASE_POINT)
		{
			j_p[name]["X"] = basePointPlayerCourt[name].x;
			j_p[name]["Y"] = basePointPlayerCourt[name].y;
			j_p[name]["Z"] = basePointPlayerCourt[name].z;

			j_e[name]["X"] = basePointEnemyCourt[name].x;
			j_e[name]["Y"] = basePointEnemyCourt[name].y;
			j_e[name]["Z"] = basePointEnemyCourt[name].z;
		}
		
		//JSON�t�@�C���̏�������
		ofstream ofs_p(PLAYER_JSON_PATH);
		ofs_p << j_p;

		ofstream ofs_e(ENEMY_JSON_PATH);
		ofs_e << j_e;
	}

	//��_���擾
	XMFLOAT3 BasePointManager::GetBasePoint(string name, bool isPlayer)
	{
		//�v���C���[�̊�_�擾�Ȃ�
		if (isPlayer)
			return basePointPlayerCourt[name];
		else
			return basePointEnemyCourt[name];
	}

	//��_�������_���Ɏ擾
	XMFLOAT3 GetRandomBasePoint(bool isPlayer)
	{
		//�v���C���[�̊�_�擾�Ȃ�
		if (isPlayer)
			return basePointPlayerCourt[BASE_POINT[Random(0,2)]];
		else
			return basePointEnemyCourt[BASE_POINT[Random(0,2)]];
	}

	//��_�̖��O�������_���Ɏ擾
	string GetRandomBasePointName() { return BASE_POINT[Random(0, 8)]; }
}
