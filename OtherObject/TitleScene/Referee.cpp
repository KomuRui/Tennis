#include "Referee.h"

//�R���X�g���N�^
Referee::Referee()
	:score_(new Score())
{
}

//�`��
void Referee::Draw()
{
	score_->Draw();
}