#include "ForehandingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"

//更新
void ForehandingState::Update2D(PlayerBase* player)
{
	//入力処理関数を呼ぶ
	HandleInput(player);
}

//3D用更新
void ForehandingState::Update3D(PlayerBase* player)
{
	//もしアニメーションが最後まで終わったのなら
	if (Model::GetAnimFrame(player->GetModelNum()) >= 130)
	{
		//状態変更
		PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
		PlayerStateManager::playerState_->Enter(player);

		//アニメーション
		Model::SetAnimFrame(player->GetModelNum(), 1, 60, 2.0f);
		Model::SetAnimFrame(player->GetRacket()->GetModelNum(), 1, 60, 2.0f);
	}

	//入力処理関数を呼ぶ
	HandleInput(player);
}

//入力によって状態変化する
void ForehandingState::HandleInput(PlayerBase* player)
{
}

//状態変化したとき一回だけ呼ばれる関数
void ForehandingState::Enter(PlayerBase* player)
{
	//アニメーション
	Model::SetAnimFrame(player->GetModelNum(), 70, 130, 4.0f);
	Model::SetAnimFrame(player->GetRacket()->GetModelNum(), 70, 130, 4.0f);
	Model::SetAnimLoop(player->GetRacket()->GetModelNum(), false);
}
