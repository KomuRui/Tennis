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

	//フラット
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//設定
		player->GetRacket()->SetType(Type::FLAT);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//トップスピン
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		//設定
		player->GetRacket()->SetType(Type::TOP_SPIN);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//スライス
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//設定
		player->GetRacket()->SetType(Type::SLICE);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//ロブ
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y))
	{
		//設定
		player->GetRacket()->SetType(Type::LOB);
		ARGUMENT_INITIALIZE(isShot, true);
	}

	//打ったのなら
	if (isShot)
	{
		//ボールのポインタ
		Ball* pBall = ((Ball*)player->FindObject("Ball"));

		//各ポジションを記憶
		float ballEndX = pBall->GetEndPosition().x;
		float playerX = player->GetPosition().x;

		//ボールがバウンド後なら
		if (pBall->GetBallStatus() == BallStatus::BOUND_MOVE)
		{
			//右側なら
			if (pBall->GetPosition().x <= playerX)
			{
				PlayerStateManager::playerState_ = PlayerStateManager::playerForehanding_;
				PlayerStateManager::playerState_->Enter(player);
			}
			//左側なら
			else
			{
				PlayerStateManager::playerState_ = PlayerStateManager::playerBackhanding_;
				PlayerStateManager::playerState_->Enter(player);
			}
		}
		//ボールがバウンド前なら
		else
		{
			//ボールの位置が左側かつボールの終点が右側なら
			if (pBall->GetPosition().x >= playerX && ballEndX <= playerX)
			{
				PlayerStateManager::playerState_ = PlayerStateManager::playerForehanding_;
				PlayerStateManager::playerState_->Enter(player);
			}
			//ボールの位置が左側かつボールの終点が左側なら
			else if (pBall->GetPosition().x >= playerX && ballEndX >= playerX)
			{
				PlayerStateManager::playerState_ = PlayerStateManager::playerBackhanding_;
				PlayerStateManager::playerState_->Enter(player);
			}
			//ボールの位置が右側かつボールの終点が左側なら
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

//状態変化したとき一回だけ呼ばれる関数
void StandingState::Enter(PlayerBase* player)
{
}
