#include "Referee.h"

//�R���X�g���N�^
Referee::Referee()
	:score_(new Score()), status_(GameStatus::NOW_SERVE_RECEIVE)
{
}

//�`��
void Referee::Draw()
{
	score_->Draw();
}