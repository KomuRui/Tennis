#include "Referee.h"

//�R���X�g���N�^
Referee::Referee()
	:score_(new Score()), status_(GameStatus::NOW_SERVE_RECEIVE), side_(Side::DEUCE_SIDE), server_(nullptr), receiver_(nullptr)
{
}

//�`��
void Referee::Draw()
{
	score_->Draw();
}

//�ǂ��炩���|�C���g�擾���ɌĂ΂��
void Referee::GetPoint()
{
	//�T�C�h�ύX
	ChangeSide();
}

//�ǂ��炩���Q�[���擾���ɌĂ΂��
void Referee::GetGame()
{
	//�����T�C�h�ɐݒ�
	SideReset();
}

//�����I�����ɌĂ΂��
void Referee::GameMatch()
{
}

//�T�C�h�`�F���W
void Referee::ChangeSide()
{
	switch (side_)
	{
	//�f���[�X�T�C�h
	case Side::DEUCE_SIDE:
		ARGUMENT_INITIALIZE(side_, Side::AD_SIDE);
		break;

	//�A�h�T�C�h
	case Side::AD_SIDE:
		ARGUMENT_INITIALIZE(side_, Side::DEUCE_SIDE);
		break;
	default:
		break;
	}
}