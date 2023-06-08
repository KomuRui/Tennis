#include "Referee.h"

//コンストラクタ
Referee::Referee()
	:score_(new Score()), status_(GameStatus::NOW_SERVE_RECEIVE), isPlayer1Server_(true)
{
}

//描画
void Referee::Draw()
{
	score_->Draw();
}