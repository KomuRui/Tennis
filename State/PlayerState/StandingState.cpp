#include "StandingState.h"
#include "../../Engine/System.h"
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
		player->GetState()->SetNowButtonCode(XINPUT_GAMEPAD_A);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�g�b�v�X�s��
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::TOP_SPIN);
		player->GetState()->SetNowButtonCode(XINPUT_GAMEPAD_B);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�X���C�X
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::SLICE);
		player->GetState()->SetNowButtonCode(XINPUT_GAMEPAD_X);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//���u
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::LOB);
		player->GetState()->SetNowButtonCode(XINPUT_GAMEPAD_Y);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�ł����̂Ȃ�
	if (isShot)
	{
		//�G�t�F�N�g�\��
		XMFLOAT3 pos = player->GetComponent<Transform>()->GetPosition();
		pos.y += 1;
		EffectManager::Draw(player->GetState()->GetChargeEffectNum(),"Effect/charge.txt",pos);

		//�{�[���̃|�C���^
		Ball* pBall = ((Ball*)player->FindObject("Ball"));

		//�e�|�W�V�������L��
		float ballEndX = pBall->GetSpecifyPosZBallPosition(player->GetComponent<Transform>()->GetPosition().z).x;
		float playerX = player->GetComponent<Transform>()->GetPosition().x;

		//�E���Ȃ�
		if (ballEndX <= playerX)
		{
			player->GetRacket()->SetStroke(Stroke::FOREHAND);
			player->GetState()->ChangeState(player->GetState()->playerForehanding_, player);
		}
		//�����Ȃ�
		else
		{
			player->GetRacket()->SetStroke(Stroke::BACKHAND);
			player->GetState()->ChangeState(player->GetState()->playerBackhanding_, player);
		}
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void StandingState::Enter(PlayerBase* player)
{
}
