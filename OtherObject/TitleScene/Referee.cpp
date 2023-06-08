#include "Referee.h"

//コンストラクタ
Referee::Referee()
	:score_(new Score())
{
}

//描画
void Referee::Draw()
{
	score_->Draw();
}