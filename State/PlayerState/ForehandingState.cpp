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
#include "../../Engine/ResourceManager/VFX.h"
#include "../../Manager/EffectManager/EffectManager.h"

//定数
namespace
{
	static const int PLAYER_START_ROTATION_ANGLE = 290; //プレイヤーの開始角度
	static const int RACKET_START_ROTATION_ANGLE = -90; //ラケットの開始角度
	static const int PLAYER_END_ROTATION_ANGLE = 180;   //プレイヤーの終了角度
	static const int RACKET_END_ROTATION_ANGLE = -185;  //ラケットの終了角度

	static const float FOREHAND_PULL_TIME = 0.2f;       //フォアハンドの引く時間
	static const float FOREHAND_HIT_TIME = 0.2f;        //フォアハンドの打つ時間

	////////////エフェクト////////////

	static const float EFFECT_SIZE_ADD_VALUE = 0.04f;   //エフェクトのサイズを加算するときの値
	static const float EFFECT_COLOR_ADD_VALUE = 0.01f;  //エフェクトの色を加算するときの値
	static const float EFFECT_SPIN_ADD_VALUE = 0.5f;    //エフェクトの回転速度を加算するときの値
	static const float EFFECT_MAX_SIZE = 4.0f;		    //エフェクトの最大サイズ
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

		//1以上にならないように
		ARGUMENT_INITIALIZE(ratio,min<float>(ratio, 1.0f));
		 
		//エミッターを取得する
		VFX::Emitter* d = VFX::GetEmitter(player->pState_->GetChargeEffectNum());

		//徐々に縮小するように
		if (d != nullptr)
		{
			d->data.size.x += EFFECT_SIZE_ADD_VALUE;
			d->data.size.y += EFFECT_SIZE_ADD_VALUE;

			ARGUMENT_INITIALIZE(d->data.size.x,Clamp(d->data.size.x, EFFECT_MAX_SIZE, effectSize_.x));
			ARGUMENT_INITIALIZE(d->data.size.y,Clamp(d->data.size.y, EFFECT_MAX_SIZE, effectSize_.y));

			d->data.color.x += EFFECT_COLOR_ADD_VALUE;
			d->data.color.y -= EFFECT_COLOR_ADD_VALUE;
			d->data.color.z -= EFFECT_COLOR_ADD_VALUE;
			d->data.color.w += EFFECT_COLOR_ADD_VALUE;
			d->data.spin.z += EFFECT_SPIN_ADD_VALUE;
		}

		//もし回転が最後まで終わったかつボタンを離しているかもともボタンを離していたら
		if (ratio >= 1 && (Input::IsPadButtonUp(player->pState_->GetNowButtonCode()) || !Input::IsPadButton(player->pState_->GetNowButtonCode())))
		{
			//チャージエフェクト削除
			VFX::ForcedEnd(player->pState_->GetChargeEffectNum());

			//打つ時の倍率を設定
			player->GetRacket()->SetRatio(1 - (Time::GetTimef(hTime_) / 3));

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

	//エフェクトのサイズ保存
	ARGUMENT_INITIALIZE(effectSize_, VFX::GetEmitter(player->pState_->GetChargeEffectNum())->data.size);

	//引く動作をするのfalseを設定しておく
	player->pState_->SetHitMove(false);

	//開始角度
	player->SetRotateY(PLAYER_END_ROTATION_ANGLE);
	player->GetRacket()->SetRotateY(RACKET_END_ROTATION_ANGLE);
	Model::SetAnimFlag(player->GetModelNum(), false);
}
