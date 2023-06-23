#include "sceneManager.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/ResourceManager/ImageManager.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Scene/PlayScene/PlayScene.h"
#include "../../Scene/TitleScene/TitleScene.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "../../Engine/ResourceManager/VFX.h"
#include "../../Engine/GUI/ImGuiSet.h"


//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager"), isLoadDraw_(true), isSameSceneInitialize_(false)
{
}

//������
void SceneManager::Initialize()
{
	//���g��ǉ�
	GameManager::SetpSceneManager(this);

	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_ || isSameSceneInitialize_)
	{
		SceneUpdate();
	}
}

//�V�[�����X�V
void SceneManager::SceneUpdate()
{
	//���[�h���ɕ`�悷��Ȃ�
	if (isLoadDraw_)
	{
		//���[�h���Ă���Ƃ��p�̉摜�\��(�����\���������̂ŕ`��I�����Ă�)
		Fade::SetFadeStatus(DRAW);
		Direct3D::EndDraw();
	}

	//���̃V�[���̃I�u�W�F�N�g��S�폜
	KillAllChildren();

	//���[�h�����f�[�^��S�폜
	ButtonManager::Reset();
	VFX::Release();
	Audio::AllRelease();
	ModelManager::AllRelease();
	ImageManager::AllRelease();
	Time::AllRelease();

	//�V�[���J�ڎ��̏�����
	GameManager::SceneTransitionInitialize();

	//���̃V�[�����쐬
	switch (nextSceneID_)
	{
	case SCENE_ID_PLAY:				 Instantiate<PlayScene>(this); break;
	case SCENE_ID_TITLE:			 Instantiate<TitleScene>(this); break;
	}

	//�J�����g�V�[�����X�V
	ARGUMENT_INITIALIZE(currentSceneID_, nextSceneID_);

	//���[�h���ɕ`�悷��ɏ��������Ă���
	ARGUMENT_INITIALIZE(isLoadDraw_, true);

	//��������Ԃ�
	ARGUMENT_INITIALIZE(isSameSceneInitialize_, false);
}

//�����V�[������������Ԃɂ���
void SceneManager::SameSceneInitializ(SCENE_ID next)
{
	//���Ԏ~�߂Ă���Ή���
	Direct3D::SetTimeScale(false);

	//�}�b�v�G�f�B�^��ԂȂ�������Ă���
	Direct3D::SetScreenGameStatus(true);

	//������Ԃ�
	ImGuiSet::SetGameMode(static_cast<int>(Mode::START));
	ImGuiSet::SetScreenMode(static_cast<int>(Mode::GAME));
	Direct3D::SetBackScreenColor(XMFLOAT4(0, 0, 0, 1));

	//�V�[���؂�ւ�
	ChangeScene(next);

	//�����V�[��������������ɐݒ�
	ARGUMENT_INITIALIZE(isSameSceneInitialize_,true);
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next){ 	

	//���Ԏ~�߂Ă���Ή���
	Direct3D::SetTimeScale(false);

	//�}�b�v�G�f�B�^��ԂȂ�������Ă���
	Direct3D::SetScreenGameStatus(true);
	
	//������Ԃ�
	ImGuiSet::SetGameMode(static_cast<int>(Mode::START));
	ImGuiSet::SetScreenMode(static_cast<int>(Mode::GAME));
	Direct3D::SetBackScreenColor(XMFLOAT4(0, 0, 0, 1));
	
	ARGUMENT_INITIALIZE(nextSceneID_,next);
}

//��O�̃V�[��ID���Q�b�g
SCENE_ID SceneManager::GetBeforeSceneId() { return currentSceneID_; }

//���݂̃V�[��ID�Q�b�g
SCENE_ID SceneManager::GetSceneId(){ return nextSceneID_;}

//���[�h�����Ă鎞�ɉ摜�\�����邩�Z�b�g����
void SceneManager::SetLoadDrawFlag(bool flag){ ARGUMENT_INITIALIZE(isLoadDraw_, flag);}