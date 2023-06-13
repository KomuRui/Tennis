#include "Referee.h"

//コンストラクタ
Referee::Referee()
	:score_(new Score()), status_(GameStatus::NOW_SERVE_RECEIVE), side_(Side::DEUCE_SIDE), server_(nullptr), receiver_(nullptr)
{
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