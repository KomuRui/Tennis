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

//�萔
namespace
{
	//�����[���̊e��_�̖��O
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

	//�T�[�u���̊e��_�̖��O
	static const string SERVE_BASE_POINT[] = {
		"Right_R",
		"Right_C",
		"Right_L",
		"Left_R",
		"Left_C",
		"Left_L",
	};

	//�e��
	static const string AXIS[] = {
		"X",
		"Y",
		"Z",
	};

	//�ejson�t�@�C���̃p�X
	static const string RALLY_PLAYER1_JSON_PATH = "Tool/BasePoint/RallyBasePointPlayer1Court.json";
	static const string RALLY_PLAYER2_JSON_PATH = "Tool/BasePoint/RallyBasePointPlayer2Court.json";
	static const string SERVE_PLAYER1_JSON_PATH = "Tool/BasePoint/ServeBasePointPlayer1Court.json";
	static const string SERVE_PLAYER2_JSON_PATH = "Tool/BasePoint/ServeBasePointPlayer2Court.json";

	//�e�A���r�G���g
	static const XMFLOAT4 RALLY_AMBIENT_COLOR_PLAYER1 = XMFLOAT4(1.0f, ZERO, ZERO, 1.0f);
	static const XMFLOAT4 RALLY_AMBIENT_COLOR_PLAYER2 = XMFLOAT4(1.0f, 1.0f, ZERO, 1.0f);
	static const XMFLOAT4 SERVE_AMBIENT_COLOR_PLAYER1 = XMFLOAT4(ZERO, 1.0f, ZERO, 1.0f);
	static const XMFLOAT4 SERVE_AMBIENT_COLOR_PLAYER2 = XMFLOAT4(ZERO, ZERO, 1.0f, 1.0f);

	//��_�𓮂����Ƃ��̔{��
	static const float MOVE_RATIO = 0.020f;
}

//�e�j�X�{�[�������ł�����_���Ǘ����Ă��閼�O���
namespace BasePointManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	//�e��_�̈ʒu
	map<string, XMFLOAT3> rallyBasePointPlayer1Court;
    map<string, XMFLOAT3> rallyBasePointPlayer2Court;
	map<string, XMFLOAT3> serveBasePointPlayer1Court;
	map<string, XMFLOAT3> serveBasePointPlayer2Court;

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

		//�����[
		ifstream ifs_p1(RALLY_PLAYER1_JSON_PATH);
		ifstream ifs_p2(RALLY_PLAYER2_JSON_PATH);
		json j_p1;
		json j_p2;
		ifs_p1 >> j_p1;	
		ifs_p2 >> j_p2;

		//��_����
		for (string name : RALLY_BASE_POINT)
		{
			rallyBasePointPlayer1Court[name] = XMFLOAT3(j_p1[name]["X"], j_p1[name]["Y"], j_p1[name]["Z"]);
			rallyBasePointPlayer2Court[name] = XMFLOAT3(j_p2[name]["X"], j_p2[name]["Y"], j_p2[name]["Z"]);
		}

		//�T�[�u
		ifstream ifs_Sp1(SERVE_PLAYER1_JSON_PATH);
		ifstream ifs_Sp2(SERVE_PLAYER2_JSON_PATH);
		json j_Sp1;
		json j_Sp2;
		ifs_Sp1 >> j_Sp1;
		ifs_Sp2 >> j_Sp2;

		//��_����
		for (string name : SERVE_BASE_POINT)
		{
			serveBasePointPlayer1Court[name] = XMFLOAT3(j_Sp1[name]["X"], j_Sp1[name]["Y"], j_Sp1[name]["Z"]);
			serveBasePointPlayer2Court[name] = XMFLOAT3(j_Sp2[name]["X"], j_Sp2[name]["Y"], j_Sp2[name]["Z"]);
		}

	}

	//��_���f���𐶐�
	void BasePointManager::InstantiateBasePointModel()
	{
		//�����[���̊�_
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

		//�T�[�u���̊�_
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
			if (isSelectBasePointModel->isPlaye1CourtType())
				rallyBasePointPlayer1Court[isSelectBasePointModel->GetBasePointName()] = isSelectBasePointModel->GetComponent<Transform>()->GetPosition();
			else								       
				rallyBasePointPlayer2Court[isSelectBasePointModel->GetBasePointName()] = isSelectBasePointModel->GetComponent<Transform>()->GetPosition();

		}

		//������ԂȂ�
		if (isMove)
		{
			//�}�E�X�̓������擾
			XMFLOAT3 mouseMove = Input::GetMouseMove();

			//���݂̈ʒu���擾
			XMFLOAT3 nowPos = isSelectBasePointModel->GetComponent<Transform>()->GetPosition();

			//�}�E�X�̈ړ��ʕ�������
			isSelectBasePointModel->GetComponent<Transform>()->SetPosition(XMFLOAT3(nowPos.x + mouseMove.y * MOVE_RATIO, nowPos.y, nowPos.z + mouseMove.x * MOVE_RATIO));
		}
	}

	//��_�G�N�X�|�[�g
	void BasePointManager::BasePointExport()
	{
		//JSON�t�@�C��
		json j_p;
		json j_e;
		
		//��_����
		for (string name : RALLY_BASE_POINT)
		{
			j_p[name]["X"] = rallyBasePointPlayer1Court[name].x;
			j_p[name]["Y"] = rallyBasePointPlayer1Court[name].y;
			j_p[name]["Z"] = rallyBasePointPlayer1Court[name].z;

			j_e[name]["X"] = rallyBasePointPlayer2Court[name].x;
			j_e[name]["Y"] = rallyBasePointPlayer2Court[name].y;
			j_e[name]["Z"] = rallyBasePointPlayer2Court[name].z;
		}
		
		//JSON�t�@�C���̏�������
		ofstream ofs_p(RALLY_PLAYER1_JSON_PATH);
		ofs_p << j_p;

		ofstream ofs_e(RALLY_PLAYER2_JSON_PATH);
		ofs_e << j_e;
	}

	//��_���擾
	XMFLOAT3 BasePointManager::GetBasePoint(string name, TennisCourtName n)
	{
		//�����[���Ȃ�
		if (GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_RALLY)
		{
			//�v���X�����̃R�[�g�̊�_�擾�Ȃ�
			if (n == TennisCourtName::Z_PLUS_COURT)
				return rallyBasePointPlayer1Court[name];
			else
				return rallyBasePointPlayer2Court[name];
		}
		//�T�[�u���Ȃ�
		else
		{
			//�}�C�i�X�����̃R�[�g�̊�_�擾�Ȃ�
			if (n == TennisCourtName::Z_PLUS_COURT)
				return serveBasePointPlayer1Court[name];
			else
				return serveBasePointPlayer2Court[name];
		}
	}

	//��_�������_���Ɏ擾
	XMFLOAT3 GetRandomBasePoint(TennisCourtName n)
	{
		//�}�C�i�X�����̃R�[�g�̊�_�擾�Ȃ�
		if (n == TennisCourtName::Z_PLUS_COURT)
			return rallyBasePointPlayer1Court[RALLY_BASE_POINT[Random(0,2)]];
		else
			return rallyBasePointPlayer2Court[RALLY_BASE_POINT[Random(0,2)]];
	}

	//���͂ɑ΂����_�̖��O���擾
	string GetInputBasePoint(PlayerBase* p)
	{
		//�ŏI�I�ɕԂ�������
		string name = "";

		//L�X�e�B�b�N�̌X�����擾
		XMFLOAT3 stickL = Input::GetPadStickL(p->GetState()->GetPlayerNum());

		//�����[���Ȃ�
		if (GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_RALLY)
		{
			//���s
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
		//�T�[�u���V�[�u���Ȃ�
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

	//��_�̖��O�������_���Ɏ擾
	string GetRandomBasePointName() { return RALLY_BASE_POINT[Random(0, 8)]; }
}
