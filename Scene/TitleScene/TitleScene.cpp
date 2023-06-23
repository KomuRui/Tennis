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
	: GameObject(parent, "TitleScene")
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

	hermiteMoveCamPos_->AddPath(CAM_POS,XMFLOAT3(15,0,15));
	hermiteMoveCamPos_->AddPath(XMFLOAT3(5,20,30));
	hermiteMoveCamPos_->AddPath(XMFLOAT3(-25,20,25));
	hermiteMoveCamPos_->AddPath(XMFLOAT3(28,20,40));
	hermiteMoveCamPos_->AddPath(XMFLOAT3(-3,20,10));
	hermiteMoveCamPos_->AddPath(XMFLOAT3(15,20,40));
	hermiteMoveCamPos_->Start();

	hermiteMoveCamTar_->AddPath(CAM_TAR, XMFLOAT3(15, 0, 15));
	hermiteMoveCamTar_->AddPath(XMFLOAT3(15, 0, -5));
	hermiteMoveCamTar_->AddPath(XMFLOAT3(5, 0, -15));
	hermiteMoveCamTar_->AddPath(XMFLOAT3(-18, 0, 9));
	hermiteMoveCamTar_->AddPath(XMFLOAT3(20, 0, 10));
	hermiteMoveCamTar_->AddPath(XMFLOAT3(1, 0, -10));
	hermiteMoveCamTar_->Start();
}

//�X�V
void TitleScene::Update()
{
	//Camera::SetPosition(hermiteMoveCamPos_->Updata());
	//Camera::SetTarget(hermiteMoveCamTar_->Updata());
}

//�`��
void TitleScene::Draw()
{
}
