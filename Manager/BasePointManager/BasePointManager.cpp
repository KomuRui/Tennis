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

			Model::SetAmbient(p->GetModelNum(), AMBIENT_COLOR_PLAYER);
			Model::SetAmbient(e->GetModelNum(), AMBIENT_COLOR_ENEMY);
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
			Model::AllRayCast(-1, &data);

			//����������_�̃I�u�W�F�N�g��null�Ȃ炱�̐揈�����Ȃ�
			if (data.basePoint == nullptr) return;

			//�Ⴄ��_�Ȃ�I���I�u�W�F���X�V
			if (data.basePoint != isSelectBasePointModel) ARGUMENT_INITIALIZE(isSelectBasePointModel, data.basePoint);

			//������Ԃɐݒ�
			ARGUMENT_INITIALIZE(isMove, true);
		}
		
		//�N���b�N�����ꂽ�瓮����ԉ���
		if (Input::IsMouseButtonUp(0)) ARGUMENT_INITIALIZE(isMove, false);

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
}
