#include "StandingState.h"
#include "../../Engine/System.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../OtherObject/TitleScene/Ball.h"
#include "../../OtherObject/TitleScene/Referee.h"

//更新
void StandingState::Update2D(PlayerBase* player)
{
	//入力処理関数を呼ぶ
	HandleInput(player);
}

//3D用更新
void StandingState::Update3D(PlayerBase* player)
{
	//入力処理関数を呼ぶ
	HandleInput(player);
}

//入力によって状態変化する
void StandingState::HandleInput(PlayerBase* player)
{
	//打ったかどうか
	bool isShot = false;
	int Padnum = player->GetState()->GetPlayerNum();

	//フラット
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, Padnum))
	{
		//設定
		player->GetRacket()->SetType(Type::FLAT);
		player->GetState()->SetNowButtonCode(XINPUT_GAMEPAD_A);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//トップスピン
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B, Padnum))
	{
		//設定
		player->GetRacket()->SetType(Type::TOP_SPIN);
		player->GetState()->SetNowButtonCode(XINPUT_GAMEPAD_B);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//スライス
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X, Padnum))
	{
		//設定
		player->GetRacket()->SetType(Type::SLICE);
		player->GetState()->SetNowButtonCode(XINPUT_GAMEPAD_X);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//ロブ
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y, Padnum))
	{
		//設定
		player->GetRacket()->SetType(Type::LOB);
		player->GetState()->SetNowButtonCode(XINPUT_GAMEPAD_Y);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//打つボタンを押してかつサーブレシーブ中かつサーバーなら
	if (isShot && GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_SERVE_RECEIVE &&
	   (GameManager::GetReferee()->IsPlayer1Server() == player->GetState()->GetPlayerNum() == 0 ||
        GameManager::GetReferee()->IsPlayer2Server() == player->GetState()->GetPlayerNum() == 1))
	{
		player->GetState()->ChangeState(player->GetState()->playerServing_, player);
		return;
	}

	//打ったのなら
	if (isShot)
	{
		//エフェクト表示
		XMFLOAT3 pos = player->GetComponent<Transform>()->GetPosition();
		pos.y += 1;
		EffectManager::Draw(player->GetState()->GetChargeEffectNum(),"Effect/charge.txt",pos);

		//ボールのポインタ
		Ball* pBall = ((Ball*)player->FindObject("Ball"));

		//各ポジションを記憶
		float ballEndX = pBall->GetSpecifyPosZBallPosition(player->GetComponent<Transform>()->GetPosition().z).x;
		float playerX = player->GetComponent<Transform>()->GetPosition().x;

		//右側なら
		if (ballEndX <= playerX)
		{
			//二人目なら
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
		//左側なら
		else
		{
			//二人目なら
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

//状態変化したとき一回だけ呼ばれる関数
void StandingState::Enter(PlayerBase* player)
{
}
