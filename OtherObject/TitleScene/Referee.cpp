#include "Referee.h"

//�R���X�g���N�^
Referee::Referee()
	:score_(new Score()), status_(GameStatus::NOW_SERVE_RECEIVE), side_(Side::DEUCE_SIDE), server_(nullptr), receiver_(nullptr), numGameFirstToGet_(5)
{

	//�T�[�o�[�̓�����͈͂�ݒ�
	serverMoveRange_[{TennisCourtName::Z_PLUS_COURT, Side::DEUCE_SIDE}] = { -4.0f,0.0f };
	serverMoveRange_[{TennisCourtName::Z_PLUS_COURT, Side::AD_SIDE}] = { 0.0f,4.0f };
	serverMoveRange_[{TennisCourtName::Z_MINUS_COURT, Side::DEUCE_SIDE}] = { 0.0f,4.0f };
	serverMoveRange_[{TennisCourtName::Z_MINUS_COURT, Side::AD_SIDE}] = { -4.0f,0.0f };

	//////�T�[�o�[�E���V�[�o�[�̏����ʒu

	//�T�[�o�[
	serverInitialPosition_[{TennisCourtName::Z_PLUS_COURT, Side::DEUCE_SIDE}] = { { -1.0f,ZERO,11.58f },{ ZERO,240,ZERO} };
	serverInitialPosition_[{TennisCourtName::Z_PLUS_COURT, Side::AD_SIDE}] = { { 1.0f,ZERO,11.58f },{ ZERO,300,ZERO } };
	serverInitialPosition_[{TennisCourtName::Z_MINUS_COURT, Side::DEUCE_SIDE}] = { { 1.0f, ZERO, -11.58f },{ ZERO,60,ZERO } };
	serverInitialPosition_[{TennisCourtName::Z_MINUS_COURT, Side::AD_SIDE}] = { { -1.0f, ZERO, -11.58f }, { ZERO,120,ZERO } };

	//���V�[�o�[
	receiverInitialPosition_[{TennisCourtName::Z_PLUS_COURT, Side::DEUCE_SIDE}] = {{ -4.0f,ZERO,11.58f },{ ZERO,180,ZERO } };
	receiverInitialPosition_[{TennisCourtName::Z_PLUS_COURT, Side::AD_SIDE}] = { { 4.0f,ZERO,11.58f },{ ZERO,180,ZERO } };
	receiverInitialPosition_[{TennisCourtName::Z_MINUS_COURT, Side::DEUCE_SIDE}] = { { 4.0f, ZERO, -11.58f },{ ZERO,ZERO,ZERO } };
	receiverInitialPosition_[{TennisCourtName::Z_MINUS_COURT, Side::AD_SIDE}] = { { -4.0f, ZERO, -11.58f },{ ZERO,ZERO,ZERO } };
}

//������
void Referee::Initialize()
{
	//�ʒu�E��]������
	server_->GetComponent<Transform>()->SetPosition(serverInitialPosition_[{server_->GetTennisCourtName(), side_}].first);
	server_->GetComponent<Transform>()->SetRotate(serverInitialPosition_[{server_->GetTennisCourtName(), side_}].second);
	receiver_->GetComponent<Transform>()->SetPosition(receiverInitialPosition_[{receiver_->GetTennisCourtName(), side_}].first);
	receiver_->GetComponent<Transform>()->SetRotate(receiverInitialPosition_[{receiver_->GetTennisCourtName(), side_}].second);

	//�T�[�o�[�E���V�[�o�[��������Ԃɂ��Ă���
	server_->GetState()->ChangeState(server_->GetState()->playerStanding_, server_);
	receiver_->GetState()->ChangeState(receiver_->GetState()->playerStanding_, receiver_);
}

//�`��
void Referee::Draw()
{
	score_->Draw();
}

//�|�C���g�I����
void Referee::EndPoint(TennisCourtName n)
{
	//�|�C���g���Z
	score_->AddScore(n);
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

	//�T�[�o�[�ƃ��V�[�o�[�����ւ���
	swap(server_, receiver_);

	//������
	Initialize();

	//������Ԃ��T�[�u���V�[�u��Ԃɂ���
	ARGUMENT_INITIALIZE(status_, GameStatus::NOW_SERVE_RECEIVE);
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