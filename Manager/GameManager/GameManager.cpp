#include "GameManager.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/ImageManager.h"
#include "../TextManager/TextManager.h"
#include "../ButtonManager/ButtonManager.h"
#include "../ScoreManager/ScoreManager.h"
#include "../AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../AudioManager/OtherAudioManager/OtherAudioManager.h"
#include "../BasePointManager/BasePointManager.h"
#include <cmath>

//�Q�[���̂��낢��ȊǗ�������
namespace GameManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	//���ݎg�p����Ă���v���C���[�̃|�C���^�i�[�p
	PlayerBase* pNowPlayer_;

	//���݂̎g�p����Ă���X�e�[�W�̃|�C���^�i�[�p
	Stage* pNowStage_;

	//�V�[���}�l�[�W���[�̃|�C���^�i�[�p
	SceneManager* pSceneManager_;

	//�v���C���[�l��
	Players player_;

	//���݂̃v���C���[�o�^�l��
	int nowPlayerRegistration_;

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void GameManager::Initialize()
	{
		//��������
		OtherAudioManager::Initialize();
		PlayerAudioManager::Initialize();

		//�e�L�X�g�}�l�[�W���̏�����
		TextManager::Initialize();

		//�X�R�A�}�l�[�W���[�̏�����
		ScoreManager::Initialize();

		//��_�̃}�l�[�W���[��������
		BasePointManager::Initialize();

		//�t�F�C�h�̏�����
		Fade::Initialize();

		//�e�ϐ�������
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(pSceneManager_, nullptr);
		ARGUMENT_INITIALIZE(player_, Players::ONE);
		ARGUMENT_INITIALIZE(nowPlayerRegistration_, ZERO);
	}

	//�V�[���J�ڂ̎��̏�����
	void GameManager::SceneTransitionInitialize()
	{
		//���낢�돉������Ԃɂ��Ă���
		Light::Initialize();
		Fade::SceneTransitionInitialize();
		OtherAudioManager::SceneTransitionInitialize();
		PlayerAudioManager::SceneTransitionInitialize();
		ScoreManager::SceneTransitionInitialize();
	}

	//Player�����S��������LifeManager����Ă΂��
	void GameManager::PlayerDie()
	{

	}

	//�X�V
	void GameManager::Update()
	{
		//�{�^���}�l�[�W���̍X�V���Ă�
		ButtonManager::Update();

		//��_�̃}�l�[�W���[���X�V
		BasePointManager::Update();
	}

	//�`��(�R�C���̎擾����Player���C�t�̕\��)
	void GameManager::Draw()
	{
		//Ui�Ȃǂ�\��
		ImageManager::UiDraw();

		//�X�R�A�}�l�[�W���[�̕`��
		ScoreManager::Draw();

		//�t�F�[�h�p�̕`��
		Fade::Draw();
	}


	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////
	
	//�v���C���[�̃|�C���^�Z�b�g
	void GameManager::SetpPlayer(PlayerBase* player) { pNowPlayer_ = player; }

	//�v���C���[�̃|�C���^�Q�b�g
	PlayerBase* GameManager::GetpPlayer() { return pNowPlayer_; }

	//�X�e�[�W�̃|�C���^�Z�b�g
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GameManager::GetpStage() { return pNowStage_; }

	//�V�[���}�l�[�W���[�̃|�C���^�Z�b�g
	void GameManager::SetpSceneManager(SceneManager* scene) { pSceneManager_ = scene; }

	//�V�[���}�l�[�W���[�̃|�C���^�Q�b�g
	SceneManager* GameManager::GetpSceneManager() { return pSceneManager_; }

	//�v���C���[�l���̐ݒ�
	void GameManager::SetPlayers(Players s) { player_ = s; }

	//�v���C���[�l���̎擾
	Players GameManager::GetPlayers() { return player_; }

	//�v���C���[�Z�b�g
	int  GameManager::SetPlayer() { 

		//�v���C���[�ԍ��Ԃ�
		return nowPlayerRegistration_++;
	};
}