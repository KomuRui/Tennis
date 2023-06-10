#include "ServingState.h"
#include "../../Engine/System.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../OtherObject/TitleScene/Referee.h"

//定数
namespace
{
	static const XMFLOAT3 PLAYER_START_ROTATION_ANGLE = { 0,240,0 };       //プレイヤーの開始角度
	static const XMFLOAT3 RACKET_START_ROTATION_ANGLE = { 0,-185,0 };	   //ラケットの開始角度
	static const XMFLOAT3 PLAYER_CHARGE_ROTATION_ANGLE = { 0,240,0 };      //プレイヤーの溜める角度
	static const XMFLOAT3 RACKET_CHARGE_ROTATION_ANGLE = { 60,-265,-240 }; //ラケットの溜める角度
	static const XMFLOAT3 PLAYER_END_ROTATION_ANGLE = { 0,230,0 };         //プレイヤーの終了角度
	static const XMFLOAT3 RACKET_END_ROTATION_ANGLE = { -75,-265,-240 };   //ラケットの終了角度

	static const float SERVE_PULL_TIME = 0.2f;       //サーブの引く時間
	static const float SERVE_HIT_TIME = 0.2f;        //サーブの打つ時間
}


//更新
void ServingState::Update2D(PlayerBase* player)
{
	//入力処理関数を呼ぶ
	HandleInput(player);
}

//3D用更新
void ServingState::Update3D(PlayerBase* player)
{
	//打つ動作なら
	player->GetState()->IsHitMove() ? HitMove(player)
									: PullMove(player);

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
	//タイマー追加
	ARGUMENT_INITIALIZE(hTime_, Time::Add());

	//元の姿勢に戻すように
	player->GetState()->SetRestorePosture(true);

	//構えてるに設定
	ARGUMENT_INITIALIZE(isCharge_, true);

	//引く動作をするのfalseを設定しておく
	player->GetState()->SetHitMove(false);

	//開始角度
	player->GetComponent<Transform>()->SetRotate(PLAYER_START_ROTATION_ANGLE);
	player->GetRacket()->GetComponent<Transform>()->SetRotate(RACKET_START_ROTATION_ANGLE);
	ModelManager::SetAnimFlag(player->GetModelNum(), false);
}

//打つ時の動き
void ServingState::HitMove(PlayerBase* player)
{
	//割合を求める
	float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / SERVE_HIT_TIME);

	//各角度を求める
	player->GetComponent<Transform>()->SetRotate(VectorToFloat3(PLAYER_CHARGE_ROTATION_ANGLE - (PLAYER_CHARGE_ROTATION_ANGLE - PLAYER_END_ROTATION_ANGLE) * ratio));
	player->GetRacket()->GetComponent<Transform>()->SetRotate(VectorToFloat3(XMVectorLerp(XMLoadFloat3(&RACKET_CHARGE_ROTATION_ANGLE), XMLoadFloat3(&RACKET_END_ROTATION_ANGLE), ratio)));

	//もし回転が最後まで終わったのなら
	if (ratio >= 1)
	{
		//状態変更
		player->GetState()->ChangeState(player->GetState()->playerStanding_, player);

		//元の角度に戻す
		player->GetComponent<Transform>()->SetRotate(PLAYER_END_ROTATION_ANGLE);
		player->GetRacket()->GetComponent<Transform>()->SetRotate(RACKET_END_ROTATION_ANGLE);

		//構えていないに設定
		ARGUMENT_INITIALIZE(isCharge_, false);

		//打っていない状態にする
		player->GetState()->SetHitMove(false);
	}
}

//引く時の動き
void ServingState::PullMove(PlayerBase* player)
{
	//割合を求める
	float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / SERVE_PULL_TIME);

	//各角度を求める
	player->GetComponent<Transform>()->SetRotate(VectorToFloat3(PLAYER_CHARGE_ROTATION_ANGLE - (PLAYER_CHARGE_ROTATION_ANGLE - PLAYER_START_ROTATION_ANGLE) * ratio));
	player->GetRacket()->GetComponent<Transform>()->SetRotate(VectorToFloat3(XMVectorLerp(XMLoadFloat3(&RACKET_START_ROTATION_ANGLE), XMLoadFloat3(&RACKET_CHARGE_ROTATION_ANGLE), ratio)));

	//1以上にならないように
	ARGUMENT_INITIALIZE(ratio, min<float>(ratio, 1.0f));

	//もし最後まで終わっていないのならこの先は処理しない
	if (ratio < 1) return;

	//トスアップが終わっていたら元の状態に直す
	if (!GameManager::GetpBall()->isTossUp())
	{
		//状態変更
		player->GetState()->ChangeState(player->GetState()->playerStanding_, player);

		//構えていないに設定
		ARGUMENT_INITIALIZE(isCharge_, false);

		return;
	}

	//もし回転が最後まで終わったかつボタンを押したかどうか
	if ((Input::IsPadButtonDown(player->GetState()->GetNowButtonCode(), player->GetState()->GetPlayerNum())))
	{
		//タイマーリセット
		Time::Reset(hTime_);

		//タイムを取得
		float time = Time::GetTimef(hTime_);
		ARGUMENT_INITIALIZE(time, min<float>(time, 1.5f));

		//打つ時の倍率を設定
		player->GetRacket()->SetRatio(1 - (time / 3));

		//打つ動作に切り替える
		player->GetState()->SetHitMove(true);

		//ラリーモードにする
		GameManager::GetReferee()->SetGameStatus(GameStatus::NOW_RALLY);
	}
}
