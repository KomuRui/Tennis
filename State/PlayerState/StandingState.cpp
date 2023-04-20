#include "StandingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"

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
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//状態変更
		PlayerStateManager::playerState_ = PlayerStateManager::playerForehanding_;
		PlayerStateManager::playerState_->Enter(player);
	}

	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		//状態変更
		PlayerStateManager::playerState_ = PlayerStateManager::playerBackhanding_;
		PlayerStateManager::playerState_->Enter(player);
	}

	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//状態変更
		PlayerStateManager::playerState_ = PlayerStateManager::playerServing_;
		PlayerStateManager::playerState_->Enter(player);
	}
}

//状態変化したとき一回だけ呼ばれる関数
void StandingState::Enter(PlayerBase* player)
{
}
