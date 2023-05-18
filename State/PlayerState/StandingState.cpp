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

	//�{�[���̃|�C���^���i�[���Ă���
	Ball* pBall = ((Ball*)player->FindObject("Ball"));

	//�t���b�g
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//�ݒ�
		pBall->SetType(Type::FLAT);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�g�b�v�X�s��
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		//�ݒ�
		pBall->SetType(Type::TOP_SPIN);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�X���C�X
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//�ݒ�
		pBall->SetType(Type::SLICE);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//���u
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y))
	{
		//�ݒ�
		pBall->SetType(Type::LOB);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�ł����̂Ȃ�
	if (isShot)
	{
		//�e�|�W�V�������L��
		float ballX = pBall->GetEndPosition().x;
		float playerX = player->GetPosition().x;

		//�{�[�����v���C���[�̉E���ɂ���̂Ȃ�
		if (ballX <= playerX)
		{
			PlayerStateManager::playerState_ = PlayerStateManager::playerForehanding_;
			PlayerStateManager::playerState_->Enter(player);
		}
		//����
		else
		{
			PlayerStateManager::playerState_ = PlayerStateManager::playerBackhanding_;
			PlayerStateManager::playerState_->Enter(player);
		}
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void StandingState::Enter(PlayerBase* player)
{
}
