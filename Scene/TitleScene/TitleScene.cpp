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
#include "../../Manager/BasePointManager/BasePointManager.h"
#include "../../OtherObject/TitleScene/Ball.h"

//�萔
namespace
{
	static const float RATATION_SPEED = 0.5f;                  //��]���x
	static const XMFLOAT3 CAM_POS = { 0, 10.67f, 24.17f };     //�J�����̈ʒu
	static const XMFLOAT3 CAM_TAR = { 0, 2.27f, 8.01f };       //�J�����̃^�[�Q�b�g
															   
	static const XMFLOAT3 CAM_POS_2 = { 0, 10.67f, -24.17f };  //�J�����̈ʒu
	static const XMFLOAT3 CAM_TAR_2 = { 0, 2.27f, -8.01f };    //�J�����̃^�[�Q�b�g

	static const XMFLOAT3 CAM_POS_TOW_WINDOW = { 0, 20, 0 };   //�J�����̈ʒu2
	static const XMFLOAT3 CAM_TAR_TOW_WINDOW = { 0, 0, 0 };    //�J�����̃^�[�Q�b�g2
	static const XMVECTOR CAM_UP_TOW_WINDOW = { -1, 0, 0, 0 }; //�J�����̏����
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

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFileCreateStage(this, "Stage/Title/StageInformation/TitleScene.txt");

	////////////////////////�c�[���̊�_���f���𐶐�/////////////////////////////////

	BasePointManager::InstantiateBasePointModel();

	GameManager::SetPlayers(Players::ONE);

	///////////////�J����///////////////////

	//��ڂ̃J����
	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(FIELD_ANGLE);
	Camera::FrameCameraInitialize();

	//��ڂ̃J����
	Camera::SetPositionTwo(CAM_POS_2);
	Camera::SetTargetTwo(CAM_TAR_2);

	//��ڂ̃E�B���h�E�̃J����
	Camera::TwoWindowSetPosition(CAM_POS_TOW_WINDOW);
	Camera::TwoWindowSetTarget(CAM_TAR_TOW_WINDOW);
	Camera::SetTwoWindowUpDirection(CAM_UP_TOW_WINDOW);
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
}

//�J��
void TitleScene::Release()
{
}
