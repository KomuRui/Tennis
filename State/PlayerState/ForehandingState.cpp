#include "ForehandingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/ResourceManager/Easing.h"

//定数
namespace
{
	static const int PLAYER_START_ROTATION_ANGLE = 290; //プレイヤーの開始角度
	static const int RACKET_START_ROTATION_ANGLE = -90; //ラケットの開始角度
	static const int PLAYER_END_ROTATION_ANGLE = 180;   //プレイヤーの終了角度
	static const int RACKET_END_ROTATION_ANGLE = -185;  //ラケットの終了角度

	static const float FOREHAND_PULL_TIME = 0.2f;       //フォアハンドの引く時間
	static const float FOREHAND_HIT_TIME = 0.2f;        //フォアハンドの打つ時間
}

//更新
void ForehandingState::Update2D(PlayerBase* player)
{
	//入力処理関数を呼ぶ
	HandleInput(player);
}

//3D用更新
void ForehandingState::Update3D(PlayerBase* player)
{
	//打つ動作なら
	if (player->pState_->IsHitMove())
	{
		//割合を求める
		float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / FOREHAND_HIT_TIME);

		//各角度を求める
		player->SetRotateY(PLAYER_START_ROTATION_ANGLE - (PLAYER_START_ROTATION_ANGLE - PLAYER_END_ROTATION_ANGLE) * ratio);
		player->GetRacket()->SetRotateY(RACKET_START_ROTATION_ANGLE - (RACKET_START_ROTATION_ANGLE - RACKET_END_ROTATION_ANGLE) * ratio);

		//もし回転が最後まで終わったのなら
		if (ratio >= 1)
		{
			//状態変更
			PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
			PlayerStateManager::playerState_->Enter(player);

			//元の角度に戻す
			player->SetRotateY(PLAYER_END_ROTATION_ANGLE);
			player->GetRacket()->SetRotateY(RACKET_END_ROTATION_ANGLE);

			//打っていない状態にする
			player->pState_->SetHitMove(false);
		}
	}
	else
	{
		//割合を求める
		float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / FOREHAND_PULL_TIME);

		//各角度を求める
		player->SetRotateY(PLAYER_END_ROTATION_ANGLE - (PLAYER_END_ROTATION_ANGLE - PLAYER_START_ROTATION_ANGLE) * ratio);
		player->GetRacket()->SetRotateY(RACKET_END_ROTATION_ANGLE - (RACKET_END_ROTATION_ANGLE - RACKET_START_ROTATION_ANGLE) * ratio);

		//もし回転が最後まで終わったのなら
		if (ratio >= 1)
		{
			//タイマーリセット
			Time::Reset(hTime_);

			//打つ動作に切り替える
			player->pState_->SetHitMove(true);
		}
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
	//タイマー追加
	ARGUMENT_INITIALIZE(hTime_, Time::Add());

	//引く動作をするのfalseを設定しておく
	player->pState_->SetHitMove(false);

	//開始角度
	player->SetRotateY(PLAYER_END_ROTATION_ANGLE);
	player->GetRacket()->SetRotateY(RACKET_END_ROTATION_ANGLE);
	Model::SetAnimFlag(player->GetModelNum(), false);
}
