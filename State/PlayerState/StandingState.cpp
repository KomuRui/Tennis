#include "StandingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../OtherObject/TitleScene/Ball.h"

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

	//ボールのポインタを格納しておく
	Ball* pBall = ((Ball*)player->FindObject("Ball"));

	//フラット
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//設定
		pBall->SetType(Type::FLAT);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//トップスピン
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		//設定
		pBall->SetType(Type::TOP_SPIN);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//スライス
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//設定
		pBall->SetType(Type::SLICE);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//ロブ
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y))
	{
		//設定
		pBall->SetType(Type::LOB);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//打ったのなら
	if (isShot)
	{
		//各ポジションを記憶
		float ballX = pBall->GetEndPosition().x;
		float playerX = player->GetPosition().x;

		//ボールがプレイヤーの右側にあるのなら
		if (ballX <= playerX)
		{
			PlayerStateManager::playerState_ = PlayerStateManager::playerForehanding_;
			PlayerStateManager::playerState_->Enter(player);
		}
		//左側
		else
		{
			PlayerStateManager::playerState_ = PlayerStateManager::playerBackhanding_;
			PlayerStateManager::playerState_->Enter(player);
		}
	}
}

//状態変化したとき一回だけ呼ばれる関数
void StandingState::Enter(PlayerBase* player)
{
}
