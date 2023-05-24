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

	//フラット
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//設定
		player->GetRacket()->SetType(Type::FLAT);
		player->pState_->SetNowButtonCode(XINPUT_GAMEPAD_A);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//トップスピン
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		//設定
		player->GetRacket()->SetType(Type::TOP_SPIN);
		player->pState_->SetNowButtonCode(XINPUT_GAMEPAD_B);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//スライス
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//設定
		player->GetRacket()->SetType(Type::SLICE);
		player->pState_->SetNowButtonCode(XINPUT_GAMEPAD_X);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//ロブ
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y))
	{
		//設定
		player->GetRacket()->SetType(Type::LOB);
		player->pState_->SetNowButtonCode(XINPUT_GAMEPAD_Y);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//打ったのなら
	if (isShot)
	{
		//エフェクト表示
		XMFLOAT3 pos = player->GetPosition();
		pos.y += 1;
		player->pState_->SetChargeEffectNum(EffectManager::Draw("Effect/charge.txt",pos));

		//ボールのポインタ
		Ball* pBall = ((Ball*)player->FindObject("Ball"));

		//各ポジションを記憶
		float ballEndX = pBall->GetSpecifyPosZBallPosition(player->GetPosition().z).x;
		float playerX = player->GetPosition().x;

		//右側なら
		if (ballEndX <= playerX)
		{
			player->GetRacket()->SetStroke(Stroke::FOREHAND);

			PlayerStateManager::playerState_ = PlayerStateManager::playerForehanding_;
			PlayerStateManager::playerState_->Enter(player);
		}
		//左側なら
		else
		{
			player->GetRacket()->SetStroke(Stroke::BACKHAND);

			PlayerStateManager::playerState_ = PlayerStateManager::playerBackhanding_;
			PlayerStateManager::playerState_->Enter(player);
		}
	}
}

//状態変化したとき一回だけ呼ばれる関数
void StandingState::Enter(PlayerBase* player)
{
}
