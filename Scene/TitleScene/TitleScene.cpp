#include "TitleScene.h"
#include "../../Engine/System.h"

//�萔
namespace
{
	static const float RATATION_SPEED = 0.5f;                  //��]���x
	static const XMFLOAT3 CAM_POS = { 0, 20, 25 };		       //�J�����̈ʒu
	static const XMFLOAT3 CAM_TAR = { ZERO,ZERO,ZERO };        //�J�����̃^�[�Q�b�g
	static const int FIELD_ANGLE = 45;						   //�J�����̉�p
}


//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), nowLookNum_(ZERO)
{
}

//�f�X�g���N�^
TitleScene::~TitleScene()
{
}

//������
void TitleScene::Initialize()
{
	///////////////�J����///////////////////

	//��ڂ̃J����
	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(FIELD_ANGLE);

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFileCreateStage(this, "Data/StageData/Title/Title.json");

	/////////////////�t�@�C���ǂݍ���Ńp�X���Ƃ̈ʒu�擾///////////////////

	SetData("Data/PathData/TitleCamera/CamPos1.json", "Data/PathData/TitleCamera/CamTar1.json");
	SetData("Data/PathData/TitleCamera/CamPos2.json", "Data/PathData/TitleCamera/CamTar2.json");
	SetData("Data/PathData/TitleCamera/CamPos3.json", "Data/PathData/TitleCamera/CamTar3.json");
	
	//�J�n
	hermiteMoveTable_[nowLookNum_].first->Start();
	hermiteMoveTable_[nowLookNum_].second->Start();

}

//�X�V
void TitleScene::Update()
{
	//�V�[���ڍs
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		Direct3D::SetNowScreenShoot(false);
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_MODE_SELECT);
	}
	//�J����
	CameraMove();
}

//�`��
void TitleScene::Draw()
{
}

//�J�����̓���
void TitleScene::CameraMove()
{
	//�J�����ݒ�
	Camera::SetPosition(hermiteMoveTable_[nowLookNum_].first->Updata());
	Camera::SetTarget(hermiteMoveTable_[nowLookNum_].second->Updata());

	//�������I������̂Ȃ�
	if (hermiteMoveTable_[nowLookNum_].first->IsFinish())
	{
		nowLookNum_++;

		//�T�C�Y�I�[�o�[���Ă����Ȃ�
		if (hermiteMoveTable_.size() == nowLookNum_)
			ARGUMENT_INITIALIZE(nowLookNum_, ZERO);

		//�J�n
		hermiteMoveTable_[nowLookNum_].first->ReStart();
		hermiteMoveTable_[nowLookNum_].second->ReStart();
	}
}

//�f�[�^�Z�b�g
void TitleScene::SetData(string posFileName, string tarFileName)
{
	//�V�����ǉ�
	hermiteMoveTable_.push_back({ std::make_unique<HermiteSplineMove>(), std::make_unique<HermiteSplineMove>() });

	//�ǂݍ���
	ifstream ifsPos(posFileName);
	json json_object_Pos;
	ifsPos >> json_object_Pos;

	//�e�l�擾
	for (auto it = json_object_Pos.begin(); it != json_object_Pos.end(); it++) {

		hermiteMoveTable_[hermiteMoveTable_.size() - 1].first->AddPath(XMFLOAT3(json_object_Pos[it.key()]["Position"][0], json_object_Pos[it.key()]["Position"][1], json_object_Pos[it.key()]["Position"][2]), XMFLOAT3(50, ZERO, ZERO));
	}

	//�ǂݍ���
	ifstream ifsTar(tarFileName);
	json json_object_Tar;
	ifsTar >> json_object_Tar;

	//�e�l�擾
	for (auto it = json_object_Tar.begin(); it != json_object_Tar.end(); it++) {

		hermiteMoveTable_[hermiteMoveTable_.size() - 1].second->AddPath(XMFLOAT3(json_object_Tar[it.key()]["Position"][0], json_object_Tar[it.key()]["Position"][1], json_object_Tar[it.key()]["Position"][2]), XMFLOAT3(ZERO, ZERO, ZERO));
	}
}