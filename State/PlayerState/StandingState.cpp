#include "StandingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../OtherObject/TitleScene/Ball.h"

//�X�V
void StandingState::Update2D(PlayerBase* player)
{
	//���͏����֐����Ă�
	HandleInput(player);
}

//3D�p�X�V
void StandingState::Update3D(PlayerBase* player)
{
	//���͏����֐����Ă�
	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void StandingState::HandleInput(PlayerBase* player)
{
	//�ł������ǂ���
	bool isShot = false;

	//�t���b�g
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::FLAT);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�g�b�v�X�s��
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::TOP_SPIN);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�X���C�X
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::SLICE);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//���u
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::LOB);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�ł����̂Ȃ�
	if (isShot)
	{
		//�{�[���̃|�C���^
		Ball* pBall = ((Ball*)player->FindObject("Ball"));

		//�e�|�W�V�������L��
		float ballEndX = pBall->GetEndPosition().x;
		float playerX = player->GetPosition().x;

		//�{�[�����o�E���h��Ȃ�
		if (pBall->GetBallStatus() == BallStatus::BOUND_MOVE)
		{
			//�E���Ȃ�
			if (pBall->GetPosition().x <= playerX)
			{
				PlayerStateManager::playerState_ = PlayerStateManager::playerForehanding_;
				PlayerStateManager::playerState_->Enter(player);
			}
			//�����Ȃ�
			else
			{
				PlayerStateManager::playerState_ = PlayerStateManager::playerBackhanding_;
				PlayerStateManager::playerState_->Enter(player);
			}
		}
		//�{�[�����o�E���h�O�Ȃ�
		else
		{
			//�{�[���̈ʒu���������{�[���̏I�_���E���Ȃ�
			if (pBall->GetPosition().x >= playerX && ballEndX <= playerX)
			{
				PlayerStateManager::playerState_ = PlayerStateManager::playerForehanding_;
				PlayerStateManager::playerState_->Enter(player);
			}
			//�{�[���̈ʒu���������{�[���̏I�_�������Ȃ�
			else if (pBall->GetPosition().x >= playerX && ballEndX >= playerX)
			{
				PlayerStateManager::playerState_ = PlayerStateManager::playerBackhanding_;
				PlayerStateManager::playerState_->Enter(player);
			}
			//�{�[���̈ʒu���E�����{�[���̏I�_�������Ȃ�
			else if (pBall->GetPosition().x <= playerX && ballEndX >= playerX)
			{
				PlayerStateManager::playerState_ = PlayerStateManager::playerBackhanding_;
				PlayerStateManager::playerState_->Enter(player);
			}
			else
			{
				PlayerStateManager::playerState_ = PlayerStateManager::playerForehanding_;
				PlayerStateManager::playerState_->Enter(player);
			}
		}
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void StandingState::Enter(PlayerBase* player)
{
}
