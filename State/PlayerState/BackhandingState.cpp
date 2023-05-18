#include "BackhandingState.h"
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
	static const int PLAYER_START_ROTATION_ANGLE = 70;  //プレイヤーの開始角度
	static const int RACKET_START_ROTATION_ANGLE = -200;//ラケットの開始角度
	static const int PLAYER_END_ROTATION_ANGLE = 180;   //プレイヤーの終了角度
	static const int RACKET_END_ROTATION_ANGLE = -105;  //ラケットの終了角度

	static const float BACKHAND_PULL_TIME = 0.2f;       //バックハンドの引く時間
	static const float BACKHAND_HIT_TIME = 0.1f;        //バックハンドの打つ時間
}

//更新
void BackhandingState::Update2D(PlayerBase* player)
{
	//入力処理関数を呼ぶ
	HandleInput(player);
}

//3D用更新
void BackhandingState::Update3D(PlayerBase* player)
{
	//打つ動作なら
	if (isHitMove_)
	{
		//割合を求める
		float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / BACKHAND_HIT_TIME);

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

			//元の姿勢に戻すように
			player->pState_->SetRestorePosture(true);
		}
	}
	else
	{
		//割合を求める
		float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / BACKHAND_PULL_TIME);

		//各角度を求める
		player->SetRotateY(PLAYER_END_ROTATION_ANGLE - (PLAYER_END_ROTATION_ANGLE - PLAYER_START_ROTATION_ANGLE) * ratio);
		player->GetRacket()->SetRotateY(RACKET_END_ROTATION_ANGLE - (RACKET_END_ROTATION_ANGLE - RACKET_START_ROTATION_ANGLE) * ratio);

		//もし回転が最後まで終わったのなら
		if (ratio >= 1)
		{
			//タイマーリセット
			Time::Reset(hTime_);

			//打つ動作に切り替える
			ARGUMENT_INITIALIZE(isHitMove_, true);
		}
	}


	//入力処理関数を呼ぶ
	HandleInput(player);
}

//入力によって状態変化する
void BackhandingState::HandleInput(PlayerBase* player)
{
}

//状態変化したとき一回だけ呼ばれる関数
void BackhandingState::Enter(PlayerBase* player)
{
	//タイマー追加
	ARGUMENT_INITIALIZE(hTime_, Time::Add());

	//引く動作をするのfalseを設定しておく
	ARGUMENT_INITIALIZE(isHitMove_, false);

	//開始角度
	player->SetRotateY(PLAYER_END_ROTATION_ANGLE);
	player->GetRacket()->SetRotateY(RACKET_END_ROTATION_ANGLE);
	Model::SetAnimFlag(player->GetModelNum(), false);
}
