#include "Referee.h"

//コンストラクタ
Referee::Referee()
	:score_(new Score()), status_(GameStatus::NOW_SERVE_RECEIVE), side_(Side::DEUCE_SIDE), server_(nullptr), receiver_(nullptr)
{

	//サーバーの動ける範囲を設定
	serverMoveRange_[{TennisCourtName::Z_PLUS_COURT, Side::DEUCE_SIDE}] = { -4.0f,0.0f };
	serverMoveRange_[{TennisCourtName::Z_PLUS_COURT,Side::AD_SIDE}] = { 0.0f,4.0f };
	serverMoveRange_[{TennisCourtName::Z_MINUS_COURT,Side::DEUCE_SIDE}] = { 0.0f,4.0f };
	serverMoveRange_[{TennisCourtName::Z_MINUS_COURT,Side::AD_SIDE}] = { -4.0f,0.0f };

	//レシーバーの初期位置を設定
	receiverInitialPosition_[{TennisCourtName::Z_PLUS_COURT, Side::DEUCE_SIDE}] = -4.0f;
	receiverInitialPosition_[{TennisCourtName::Z_PLUS_COURT, Side::AD_SIDE}] = 4.0f;
	receiverInitialPosition_[{TennisCourtName::Z_MINUS_COURT, Side::DEUCE_SIDE}] = 4.0f;
	receiverInitialPosition_[{TennisCourtName::Z_MINUS_COURT, Side::AD_SIDE}] = -4.0f;
}

//初期化
void Referee::Initialize()
{
	//位置初期化
	server_->GetComponent<Transform>()->SetPositionX(ZERO);
	receiver_->GetComponent<Transform>()->SetPositionX(receiverInitialPosition_[{receiver_->GetTennisCourtName(), side_}]);

	//サーバー・レシーバーを初期状態にしておく
	server_->GetState()->ChangeState(server_->GetState()->playerStanding_, server_);
	receiver_->GetState()->ChangeState(receiver_->GetState()->playerStanding_, receiver_);
}

//描画
void Referee::Draw()
{
	score_->Draw();
}

//どちらかがポイント取得時に呼ばれる
void Referee::GetPoint()
{
	//サイド変更
	ChangeSide();

	//初期化
	Initialize();

	//試合状態をサーブレシーブ状態にする
	ARGUMENT_INITIALIZE(status_, GameStatus::NOW_SERVE_RECEIVE);
}

//どちらかがゲーム取得時に呼ばれる
void Referee::GetGame()
{
	//初期サイドに設定
	SideReset();
}

//試合終了時に呼ばれる
void Referee::GameMatch()
{
}

//サイドチェンジ
void Referee::ChangeSide()
{
	switch (side_)
	{
	//デュースサイド
	case Side::DEUCE_SIDE:
		ARGUMENT_INITIALIZE(side_, Side::AD_SIDE);
		break;

	//アドサイド
	case Side::AD_SIDE:
		ARGUMENT_INITIALIZE(side_, Side::DEUCE_SIDE);
		break;
	default:
		break;
	}
}