#include "ServingState.h"
#include "../../Engine/System.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../OtherObject/TitleScene/Referee.h"

//�萔
namespace
{
	static const XMFLOAT3 PLAYER_START_ROTATION_ANGLE = { 0,240,0 };       //�v���C���[�̊J�n�p�x
	static const XMFLOAT3 RACKET_START_ROTATION_ANGLE = { 0,-185,0 };	   //���P�b�g�̊J�n�p�x
	static const XMFLOAT3 PLAYER_CHARGE_ROTATION_ANGLE = { 0,240,0 };      //�v���C���[�̗��߂�p�x
	static const XMFLOAT3 RACKET_CHARGE_ROTATION_ANGLE = { 60,-265,-240 }; //���P�b�g�̗��߂�p�x
	static const XMFLOAT3 PLAYER_END_ROTATION_ANGLE = { 0,230,0 };         //�v���C���[�̏I���p�x
	static const XMFLOAT3 RACKET_END_ROTATION_ANGLE = { -75,-265,-240 };   //���P�b�g�̏I���p�x

	static const float SERVE_PULL_TIME = 0.2f;       //�T�[�u�̈�������
	static const float SERVE_HIT_TIME = 0.2f;        //�T�[�u�̑ł���
}


//�X�V
void ServingState::Update2D(PlayerBase* player)
{
	//���͏����֐����Ă�
	HandleInput(player);
}

//3D�p�X�V
void ServingState::Update3D(PlayerBase* player)
{
	//�ł���Ȃ�
	player->GetState()->IsHitMove() ? HitMove(player)
									: PullMove(player);

	//���͏����֐����Ă�
	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void ServingState::HandleInput(PlayerBase* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void ServingState::Enter(PlayerBase* player)
{
	//�^�C�}�[�ǉ�
	ARGUMENT_INITIALIZE(hTime_, Time::Add());

	//���̎p���ɖ߂��悤��
	player->GetState()->SetRestorePosture(true);

	//�\���Ă�ɐݒ�
	ARGUMENT_INITIALIZE(isCharge_, true);

	//��������������false��ݒ肵�Ă���
	player->GetState()->SetHitMove(false);

	//�J�n�p�x
	player->GetComponent<Transform>()->SetRotate(PLAYER_START_ROTATION_ANGLE);
	player->GetRacket()->GetComponent<Transform>()->SetRotate(RACKET_START_ROTATION_ANGLE);
	ModelManager::SetAnimFlag(player->GetModelNum(), false);
}

//�ł��̓���
void ServingState::HitMove(PlayerBase* player)
{
	//���������߂�
	float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / SERVE_HIT_TIME);

	//�e�p�x�����߂�
	player->GetComponent<Transform>()->SetRotate(VectorToFloat3(PLAYER_CHARGE_ROTATION_ANGLE - (PLAYER_CHARGE_ROTATION_ANGLE - PLAYER_END_ROTATION_ANGLE) * ratio));
	player->GetRacket()->GetComponent<Transform>()->SetRotate(VectorToFloat3(XMVectorLerp(XMLoadFloat3(&RACKET_CHARGE_ROTATION_ANGLE), XMLoadFloat3(&RACKET_END_ROTATION_ANGLE), ratio)));

	//������]���Ō�܂ŏI������̂Ȃ�
	if (ratio >= 1)
	{
		//��ԕύX
		player->GetState()->ChangeState(player->GetState()->playerStanding_, player);

		//���̊p�x�ɖ߂�
		player->GetComponent<Transform>()->SetRotate(PLAYER_END_ROTATION_ANGLE);
		player->GetRacket()->GetComponent<Transform>()->SetRotate(RACKET_END_ROTATION_ANGLE);

		//�\���Ă��Ȃ��ɐݒ�
		ARGUMENT_INITIALIZE(isCharge_, false);

		//�ł��Ă��Ȃ���Ԃɂ���
		player->GetState()->SetHitMove(false);
	}
}

//�������̓���
void ServingState::PullMove(PlayerBase* player)
{
	//���������߂�
	float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / SERVE_PULL_TIME);

	//�e�p�x�����߂�
	player->GetComponent<Transform>()->SetRotate(VectorToFloat3(PLAYER_CHARGE_ROTATION_ANGLE - (PLAYER_CHARGE_ROTATION_ANGLE - PLAYER_START_ROTATION_ANGLE) * ratio));
	player->GetRacket()->GetComponent<Transform>()->SetRotate(VectorToFloat3(XMVectorLerp(XMLoadFloat3(&RACKET_START_ROTATION_ANGLE), XMLoadFloat3(&RACKET_CHARGE_ROTATION_ANGLE), ratio)));

	//1�ȏ�ɂȂ�Ȃ��悤��
	ARGUMENT_INITIALIZE(ratio, min<float>(ratio, 1.0f));

	//�����Ō�܂ŏI����Ă��Ȃ��̂Ȃ炱�̐�͏������Ȃ�
	if (ratio < 1) return;

	//�g�X�A�b�v���I����Ă����猳�̏�Ԃɒ���
	if (!GameManager::GetpBall()->isTossUp())
	{
		//��ԕύX
		player->GetState()->ChangeState(player->GetState()->playerStanding_, player);

		//�\���Ă��Ȃ��ɐݒ�
		ARGUMENT_INITIALIZE(isCharge_, false);

		return;
	}

	//������]���Ō�܂ŏI��������{�^�������������ǂ���
	if ((Input::IsPadButtonDown(player->GetState()->GetNowButtonCode(), player->GetState()->GetPlayerNum())))
	{
		//�^�C�}�[���Z�b�g
		Time::Reset(hTime_);

		//�^�C�����擾
		float time = Time::GetTimef(hTime_);
		ARGUMENT_INITIALIZE(time, min<float>(time, 1.5f));

		//�ł��̔{����ݒ�
		player->GetRacket()->SetRatio(1 - (time / 3));

		//�ł���ɐ؂�ւ���
		player->GetState()->SetHitMove(true);

		//�����[���[�h�ɂ���
		GameManager::GetReferee()->SetGameStatus(GameStatus::NOW_RALLY);
	}
}
