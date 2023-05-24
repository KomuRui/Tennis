#include "StandingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../OtherObject/TitleScene/Ball.h"
#include "../../Manager/EffectManager/EffectManager.h"

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
		player->pState_->SetNowButtonCode(XINPUT_GAMEPAD_A);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�g�b�v�X�s��
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::TOP_SPIN);
		player->pState_->SetNowButtonCode(XINPUT_GAMEPAD_B);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�X���C�X
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::SLICE);
		player->pState_->SetNowButtonCode(XINPUT_GAMEPAD_X);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//���u
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::LOB);
		player->pState_->SetNowButtonCode(XINPUT_GAMEPAD_Y);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�ł����̂Ȃ�
	if (isShot)
	{
		//�G�t�F�N�g�\��
		XMFLOAT3 pos = player->GetPosition();
		pos.y += 1;
		player->pState_->SetChargeEffectNum(EffectManager::Draw("Effect/charge.txt",pos));

		//�{�[���̃|�C���^
		Ball* pBall = ((Ball*)player->FindObject("Ball"));

		//�e�|�W�V�������L��
		float ballEndX = pBall->GetSpecifyPosZBallPosition(player->GetPosition().z).x;
		float playerX = player->GetPosition().x;

		//�E���Ȃ�
		if (ballEndX <= playerX)
		{
			player->GetRacket()->SetStroke(Stroke::FOREHAND);

			PlayerStateManager::playerState_ = PlayerStateManager::playerForehanding_;
			PlayerStateManager::playerState_->Enter(player);
		}
		//�����Ȃ�
		else
		{
			player->GetRacket()->SetStroke(Stroke::BACKHAND);

			PlayerStateManager::playerState_ = PlayerStateManager::playerBackhanding_;
			PlayerStateManager::playerState_->Enter(player);
		}
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void StandingState::Enter(PlayerBase* player)
{
}
