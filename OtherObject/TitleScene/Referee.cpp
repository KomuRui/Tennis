#include "Referee.h"

//�R���X�g���N�^
Referee::Referee()
	:score_(new Score()), status_(GameStatus::NOW_SERVE_RECEIVE), side_(Side::DEUCE_SIDE), server_(nullptr), receiver_(nullptr)
{

	//�T�[�o�[�̓�����͈͂�ݒ�
	serverMoveRange_[{TennisCourtName::Z_PLUS_COURT, Side::DEUCE_SIDE}] = { -4.0f,0.0f };
	serverMoveRange_[{TennisCourtName::Z_PLUS_COURT,Side::AD_SIDE}] = { 0.0f,4.0f };
	serverMoveRange_[{TennisCourtName::Z_MINUS_COURT,Side::DEUCE_SIDE}] = { 0.0f,4.0f };
	serverMoveRange_[{TennisCourtName::Z_MINUS_COURT,Side::AD_SIDE}] = { -4.0f,0.0f };

	//���V�[�o�[�̏����ʒu��ݒ�
	receiverInitialPosition_[{TennisCourtName::Z_PLUS_COURT, Side::DEUCE_SIDE}] = -4.0f;
	receiverInitialPosition_[{TennisCourtName::Z_PLUS_COURT, Side::AD_SIDE}] = 4.0f;
	receiverInitialPosition_[{TennisCourtName::Z_MINUS_COURT, Side::DEUCE_SIDE}] = 4.0f;
	receiverInitialPosition_[{TennisCourtName::Z_MINUS_COURT, Side::AD_SIDE}] = -4.0f;
}

//������
void Referee::Initialize()
{
	//�ʒu������
	server_->GetComponent<Transform>()->SetPositionX(ZERO);
	receiver_->GetComponent<Transform>()->SetPositionX(receiverInitialPosition_[{receiver_->GetTennisCourtName(), side_}]);

	//�T�[�o�[�E���V�[�o�[��������Ԃɂ��Ă���
	server_->GetState()->ChangeState(server_->GetState()->playerStanding_, server_);
	receiver_->GetState()->ChangeState(receiver_->GetState()->playerStanding_, receiver_);
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

	//������
	Initialize();

	//������Ԃ��T�[�u���V�[�u��Ԃɂ���
	ARGUMENT_INITIALIZE(status_, GameStatus::NOW_SERVE_RECEIVE);
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