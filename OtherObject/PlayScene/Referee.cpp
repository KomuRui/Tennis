#include "Referee.h"

//コンストラクタ
Referee::Referee()
	:score_(new Score()), status_(GameStatus::NOW_SERVE_RECEIVE), side_(Side::DEUCE_SIDE), server_(nullptr), receiver_(nullptr), numGameFirstToGet_(5)
{

	//サーバーの動ける範囲を設定
	serverMoveRange_[{TennisCourtName::Z_PLUS_COURT, Side::DEUCE_SIDE}] = { -4.0f,0.0f };
	serverMoveRange_[{TennisCourtName::Z_PLUS_COURT, Side::AD_SIDE}] = { 0.0f,4.0f };
	serverMoveRange_[{TennisCourtName::Z_MINUS_COURT, Side::DEUCE_SIDE}] = { 0.0f,4.0f };
	serverMoveRange_[{TennisCourtName::Z_MINUS_COURT, Side::AD_SIDE}] = { -4.0f,0.0f };

	//////サーバー・レシーバーの初期位置

	//サーバー
	serverInitialPosition_[{TennisCourtName::Z_PLUS_COURT, Side::DEUCE_SIDE}] = { { -1.0f,ZERO,11.58f },{ ZERO,240,ZERO} };
	serverInitialPosition_[{TennisCourtName::Z_PLUS_COURT, Side::AD_SIDE}] = { { 1.0f,ZERO,11.58f },{ ZERO,300,ZERO } };
	serverInitialPosition_[{TennisCourtName::Z_MINUS_COURT, Side::DEUCE_SIDE}] = { { 1.0f, ZERO, -11.58f },{ ZERO,60,ZERO } };
	serverInitialPosition_[{TennisCourtName::Z_MINUS_COURT, Side::AD_SIDE}] = { { -1.0f, ZERO, -11.58f }, { ZERO,120,ZERO } };

	//レシーバー
	receiverInitialPosition_[{TennisCourtName::Z_PLUS_COURT, Side::DEUCE_SIDE}] = {{ -4.0f,ZERO,11.58f },{ ZERO,180,ZERO } };
	receiverInitialPosition_[{TennisCourtName::Z_PLUS_COURT, Side::AD_SIDE}] = { { 4.0f,ZERO,11.58f },{ ZERO,180,ZERO } };
	receiverInitialPosition_[{TennisCourtName::Z_MINUS_COURT, Side::DEUCE_SIDE}] = { { 4.0f, ZERO, -11.58f },{ ZERO,ZERO,ZERO } };
	receiverInitialPosition_[{TennisCourtName::Z_MINUS_COURT, Side::AD_SIDE}] = { { -4.0f, ZERO, -11.58f },{ ZERO,ZERO,ZERO } };
}

//初期化
void Referee::Initialize()
{
	//位置・回転初期化
	server_->GetComponent<Transform>()->SetPosition(serverInitialPosition_[{server_->GetTennisCourtName(), side_}].first);
	server_->GetComponent<Transform>()->SetRotate(serverInitialPosition_[{server_->GetTennisCourtName(), side_}].second);
	receiver_->GetComponent<Transform>()->SetPosition(receiverInitialPosition_[{receiver_->GetTennisCourtName(), side_}].first);
	receiver_->GetComponent<Transform>()->SetRotate(receiverInitialPosition_[{receiver_->GetTennisCourtName(), side_}].second);

	//サーバー・レシーバーを初期状態にしておく
	server_->GetState()->ChangeState(server_->GetState()->playerStanding_, server_);
	receiver_->GetState()->ChangeState(receiver_->GetState()->playerStanding_, receiver_);
}

//描画
void Referee::Draw()
{
	score_->Draw();
}

//ポイント終了時
void Referee::EndPoint(TennisCourtName n)
{
	//ポイント加算
	score_->AddScore(n);
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

	//サーバーとレシーバーを入れ替える
	swap(server_, receiver_);

	//初期化
	Initialize();

	//試合状態をサーブレシーブ状態にする
	ARGUMENT_INITIALIZE(status_, GameStatus::NOW_SERVE_RECEIVE);
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