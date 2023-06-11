#include "GameManager.h"
#include "../../Engine/System.h"
#include "../../OtherObject/TitleScene/Referee.h"
#include <cmath>

//�Q�[���̂��낢��ȊǗ�������
namespace GameManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	//���ݎg�p����Ă���v���C���[�̃|�C���^�i�[�p
	PlayerBase* pNowPlayer_;

	//���݂̎g�p����Ă���X�e�[�W�̃|�C���^�i�[�p
	Stage* pNowStage_;

	//���݂̎g�p����Ă���{�[���̃|�C���^�i�[�p
	Ball* pNowBall_;

	//�V�[���}�l�[�W���[�̃|�C���^�i�[�p
	SceneManager* pSceneManager_;

	//�R��
	Referee* referee_;

	//�v���C���[�l��
	Players player_;

	//���݂̃v���C���[�o�^�l��
	int nowPlayerRegistration_;

	//�v���C���[�̃��X�g�ۑ��p
	list<PlayerBase*> playerlist_;

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void GameManager::Initialize()
	{

		//�e�L�X�g�}�l�[�W���̏�����
		TextManager::Initialize();

		//��_�̃}�l�[�W���[��������
		BasePointManager::Initialize();

		//�t�F�C�h�̏�����
		Fade::Initialize();

		//�e�ϐ�������
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(pNowBall_, nullptr);
		ARGUMENT_INITIALIZE(pSceneManager_, nullptr);
		ARGUMENT_INITIALIZE(player_, Players::ONE);
		ARGUMENT_INITIALIZE(referee_, new Referee());
		ARGUMENT_INITIALIZE(nowPlayerRegistration_, ZERO);
	}

	//�V�[���J�ڂ̎��̏�����
	void GameManager::SceneTransitionInitialize()
	{
		//���낢�돉������Ԃɂ��Ă���
		Light::Initialize();
		Fade::SceneTransitionInitialize();
	}

	//�X�V
	void GameManager::Update()
	{
		//�{�^���}�l�[�W���̍X�V���Ă�
		ButtonManager::Update();

		//��_�̃}�l�[�W���[���X�V
		BasePointManager::Update();
	}

	//�`��
	void GameManager::Draw()
	{
		//Ui�Ȃǂ�\��
		ImageManager::UiDraw();

		//�X�R�A�Ƃ��\��
		referee_->Draw();

		//�t�F�[�h�p�̕`��
		Fade::Draw();
	}

	//�v���C���[��ǉ�
	void GameManager::AddPlayer(PlayerBase* p){ playerlist_.push_back(p);}

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

	//�{�[���̃|�C���^�Z�b�g
	void GameManager::SetpBall(Ball* ball) { pNowBall_ = ball; }

	//�{�[���̃|�C���^�Q�b�g
	Ball* GameManager::GetpBall() { return pNowBall_; }

	//�v���C���[�l���̐ݒ�
	void GameManager::SetPlayers(Players s) { player_ = s; }

	//�v���C���[�l���̎擾
	Players GameManager::GetPlayers() { return player_; }

	//�v���C���[�Z�b�g
	int  GameManager::SetPlayer(PlayerBase* p) { 

		//�o�^
		playerlist_.push_back(p); 

		//1�l�ڂȂ�T�[�o�[�ɂ��Ă���
		if (playerlist_.size() == 1)
		{
			referee_->SetServer(p);
		}
		//���̓��V�[�o�[�ɐݒ�
		else
		{
			referee_->SetReceiver(p);
		}

		return nowPlayerRegistration_++; 
	}

	//�R���擾
	Referee* GameManager::GetReferee() { return referee_; }

	//�����̃v���C���[�ȊO�̃v���C���[���擾
	PlayerBase* GetNotMyPlayer(PlayerBase* p)
	{
		for (auto i = playerlist_.begin(); i != playerlist_.end(); i++)
		{
			if ((*i) != p)
				return (*i);
		}

		return nullptr;
	}
}