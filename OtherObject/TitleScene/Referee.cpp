#include "Referee.h"

//コンストラクタ
Referee::Referee()
	:score_(new Score()), status_(GameStatus::NOW_SERVE_RECEIVE)
{
}

//描画
void Referee::Draw()
{
	score_->Draw();
}