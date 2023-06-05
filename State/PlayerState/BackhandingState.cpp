#include "BackhandingState.h"
#include "../../Engine/System.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"

//定数
namespace
{
	static const int PLAYER_START_ROTATION_ANGLE = 70;  //プレイヤーの開始角度
	static const int RACKET_START_ROTATION_ANGLE = -200;//ラケットの開始角度
	static const int PLAYER_END_ROTATION_ANGLE = 180;   //プレイヤーの終了角度
	static const int RACKET_END_ROTATION_ANGLE = -105;  //ラケットの終了角度

	static const float BACKHAND_PULL_TIME = 0.2f;       //バックハンドの引く時間
	static const float BACKHAND_HIT_TIME = 0.2f;        //バックハンドの打つ時間

	////////////エフェクト////////////

	static const float EFFECT_SIZE_ADD_VALUE = 0.04f;   //エフェクトのサイズを加算するときの値
	static const float EFFECT_COLOR_ADD_VALUE = 0.01f;  //エフェクトの色を加算するときの値
	static const float EFFECT_SPIN_ADD_VALUE = 0.5f;    //エフェクトの回転速度を加算するときの値
	static const float EFFECT_MAX_SIZE = 4.0f;			//エフェクトの最大サイズ
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
	if (player->GetState()->IsHitMove())
	{
		//割合を求める
		float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / BACKHAND_HIT_TIME);

		//各角度を求める
		player->GetComponent<Transform>()->SetRotateY(startPlayerRotationAngle - (startPlayerRotationAngle - endPlayerRotationAngle) * ratio);
		player->GetRacket()->GetComponent<Transform>()->SetRotateY(RACKET_START_ROTATION_ANGLE - (RACKET_START_ROTATION_ANGLE - RACKET_END_ROTATION_ANGLE) * ratio);

		//もし回転が最後まで終わったのなら
		if (ratio >= 1)
		{
			//状態変更
			player->GetState()->ChangeState(player->GetState()->playerStanding_, player);

			//元の角度に戻す
			player->GetComponent<Transform>()->SetRotateY(endPlayerRotationAngle);
			player->GetRacket()->GetComponent<Transform>()->SetRotateY(RACKET_END_ROTATION_ANGLE);

			//元の姿勢に戻すように
			player->GetState()->SetRestorePosture(true);

			//打っていない状態にする
			player->GetState()->SetHitMove(false);
		}
	}
	else
	{
		//割合を求める
		float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / BACKHAND_PULL_TIME);

		//各角度を求める
		player->GetComponent<Transform>()->SetRotateY(endPlayerRotationAngle - (endPlayerRotationAngle - startPlayerRotationAngle) * ratio);
		player->GetRacket()->GetComponent<Transform>()->SetRotateY(RACKET_END_ROTATION_ANGLE - (RACKET_END_ROTATION_ANGLE - RACKET_START_ROTATION_ANGLE) * ratio);

		//1以上にならないように
		ARGUMENT_INITIALIZE(ratio, min<float>(ratio, 1.0f));

		//エミッターを取得する
		VFX::Emitter* d = VFX::GetEmitter(player->GetState()->GetChargeEffectNum());

		//徐々に縮小するように
		if (d != nullptr)
		{
			//位置更新
			ARGUMENT_INITIALIZE(d->data.position, player->GetComponent<Transform>()->GetPosition());
			d->data.position.y += 1.0f;

			//サイズ更新
			d->data.size.x += EFFECT_SIZE_ADD_VALUE;
			d->data.size.y += EFFECT_SIZE_ADD_VALUE;

			ARGUMENT_INITIALIZE(d->data.size.x, Clamp(d->data.size.x, EFFECT_MAX_SIZE, effectSize_.x));
			ARGUMENT_INITIALIZE(d->data.size.y, Clamp(d->data.size.y, EFFECT_MAX_SIZE, effectSize_.y));

			//色更新
			d->data.color.x += EFFECT_COLOR_ADD_VALUE;
			d->data.color.y -= EFFECT_COLOR_ADD_VALUE;
			d->data.color.z -= EFFECT_COLOR_ADD_VALUE;
			d->data.color.w += EFFECT_COLOR_ADD_VALUE;
			d->data.spin.z  += EFFECT_SPIN_ADD_VALUE;
		}

		//もし回転が最後まで終わったかつボタンを離しているかもともボタンを離していたら
		if (ratio >= 1 && (Input::IsPadButtonUp(player->GetState()->GetNowButtonCode(), player->GetState()->GetPlayerNum()) || !Input::IsPadButton(player->GetState()->GetNowButtonCode(), player->GetState()->GetPlayerNum())))
		{
			//チャージエフェクト削除
			VFX::ForcedEnd(player->GetState()->GetChargeEffectNum());

			//タイムを取得
			float time = Time::GetTimef(hTime_);
			ARGUMENT_INITIALIZE(time,min<float>(time, 1.5f));

			//打つ時の倍率を設定
			player->GetRacket()->SetRatio(1-(time / 3));

			//タイマーリセット
			Time::Reset(hTime_);

			//打つ動作に切り替える
			player->GetState()->SetHitMove(true);
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

	//エフェクトのサイズ保存
	ARGUMENT_INITIALIZE(effectSize_, VFX::GetEmitter(player->GetState()->GetChargeEffectNum())->data.size);

	//引く動作をするのfalseを設定しておく
	player->GetState()->SetHitMove(false);

	//角度設定
	ARGUMENT_INITIALIZE(startPlayerRotationAngle,PLAYER_START_ROTATION_ANGLE);
	ARGUMENT_INITIALIZE(endPlayerRotationAngle,PLAYER_END_ROTATION_ANGLE);

	//二人目のプレイヤーなら
	if (player->GetState()->GetPlayerNum() == 1)
	{
		startPlayerRotationAngle -= 180;
		endPlayerRotationAngle -= 180;
	}

	//開始角度
	player->GetComponent<Transform>()->SetRotateY(endPlayerRotationAngle);
	player->GetRacket()->GetComponent<Transform>()->SetRotateY(RACKET_END_ROTATION_ANGLE);
	ModelManager::SetAnimFlag(player->GetModelNum(), false);
}
