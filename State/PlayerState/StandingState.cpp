#include "StandingState.h"
#include "../../Engine/System.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../OtherObject/TitleScene/Ball.h"
#include "../../OtherObject/TitleScene/Referee.h"

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
	int Padnum = player->GetState()->GetPlayerNum();

	//�t���b�g
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, Padnum))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::FLAT);
		player->GetState()->SetNowButtonCode(XINPUT_GAMEPAD_A);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�g�b�v�X�s��
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B, Padnum))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::TOP_SPIN);
		player->GetState()->SetNowButtonCode(XINPUT_GAMEPAD_B);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�X���C�X
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X, Padnum))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::SLICE);
		player->GetState()->SetNowButtonCode(XINPUT_GAMEPAD_X);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//���u
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y, Padnum))
	{
		//�ݒ�
		player->GetRacket()->SetType(Type::LOB);
		player->GetState()->SetNowButtonCode(XINPUT_GAMEPAD_Y);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//�ł{�^���������Ă��T�[�u���V�[�u�����T�[�o�[�Ȃ�
	if (isShot && GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_SERVE_RECEIVE &&
	   (GameManager::GetReferee()->IsPlayer1Server() == player->GetState()->GetPlayerNum() == 0 ||
        GameManager::GetReferee()->IsPlayer2Server() == player->GetState()->GetPlayerNum() == 1))
	{
		player->GetState()->ChangeState(player->GetState()->playerServing_, player);
		return;
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
			//��l�ڂȂ�
			if (player->GetState()->GetPlayerNum() == 1)
			{
				player->GetRacket()->SetStroke(Stroke::BACKHAND);
				player->GetState()->ChangeState(player->GetState()->playerBackhanding_, player);
			}
			else
			{
				player->GetRacket()->SetStroke(Stroke::FOREHAND);
				player->GetState()->ChangeState(player->GetState()->playerForehanding_, player);
			}
		}
		//�����Ȃ�
		else
		{
			//��l�ڂȂ�
			if (player->GetState()->GetPlayerNum() == 1)
			{
				player->GetRacket()->SetStroke(Stroke::FOREHAND);
				player->GetState()->ChangeState(player->GetState()->playerForehanding_, player);
			}
			else
			{
				player->GetRacket()->SetStroke(Stroke::BACKHAND);
				player->GetState()->ChangeState(player->GetState()->playerBackhanding_, player);
			}
		}

	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void StandingState::Enter(PlayerBase* player)
{
}
