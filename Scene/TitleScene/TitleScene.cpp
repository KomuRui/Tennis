#include "TitleScene.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"

//�萔
namespace
{
	static const float RATATION_SPEED = 0.5f;    //��]���x
	static const XMFLOAT3 CAM_POS = { 0, 0, 5 }; //�J�����̈ʒu
	static const XMFLOAT3 CAM_TAR = { 0, 0, 0 }; //�J�����̃^�[�Q�b�g
	static const int FIELD_ANGLE = 45;           //�J�����̉�p
}

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hModel_(-1)
{
}

//�f�X�g���N�^
TitleScene::~TitleScene()
{
}

//������
void TitleScene::Initialize()
{
	//////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Stage/Title/Model/BackGroundModel.fbx");
	assert(hModel_ >= ZERO);

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFileCreateStage(GetParent(), "Stage/Title/StageInformation/TitleScene1.txt");

	///////////////�J����///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(FIELD_ANGLE);
}

//�X�V�̑O�Ɉ�x�����Ă΂��X�V
void TitleScene::StartUpdate()
{
}

//�X�V
void TitleScene::Update()
{
}

//�`��
void TitleScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void TitleScene::Release()
{
}
