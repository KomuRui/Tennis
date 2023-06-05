#include "ServingState.h"
#include "../../Engine/System.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"

//更新
void ServingState::Update2D(PlayerBase* player)
{
	//入力処理関数を呼ぶ
	HandleInput(player);
}

//3D用更新
void ServingState::Update3D(PlayerBase* player)
{
	//もしアニメーションが最後まで終わったのなら
	if (ModelManager::GetAnimFrame(player->GetModelNum()) == 270)
	{
		//状態変更
		player->GetState()->ChangeState(player->GetState()->playerStanding_, player);

		//アニメーション
		ModelManager::SetAnimFrame(player->GetModelNum(), 1, 60, 2.0f);
		ModelManager::SetAnimFrame(player->GetRacket()->GetModelNum(), 1, 60, 2.0f);
	}

	//入力処理関数を呼ぶ
	HandleInput(player);
}

//入力によって状態変化する
void ServingState::HandleInput(PlayerBase* player)
{
}

//状態変化したとき一回だけ呼ばれる関数
void ServingState::Enter(PlayerBase* player)
{
	//アニメーション
	ModelManager::SetAnimFrame(player->GetModelNum(), 210, 270, 2.0f);
	ModelManager::SetAnimFrame(player->GetRacket()->GetModelNum(), 210, 270, 2.0f);
}
