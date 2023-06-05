#include "BackhandingState.h"
#include "../../Engine/System.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"

//�萔
namespace
{
	static const int PLAYER_START_ROTATION_ANGLE = 70;  //�v���C���[�̊J�n�p�x
	static const int RACKET_START_ROTATION_ANGLE = -200;//���P�b�g�̊J�n�p�x
	static const int PLAYER_END_ROTATION_ANGLE = 180;   //�v���C���[�̏I���p�x
	static const int RACKET_END_ROTATION_ANGLE = -105;  //���P�b�g�̏I���p�x

	static const float BACKHAND_PULL_TIME = 0.2f;       //�o�b�N�n���h�̈�������
	static const float BACKHAND_HIT_TIME = 0.2f;        //�o�b�N�n���h�̑ł���

	////////////�G�t�F�N�g////////////

	static const float EFFECT_SIZE_ADD_VALUE = 0.04f;   //�G�t�F�N�g�̃T�C�Y�����Z����Ƃ��̒l
	static const float EFFECT_COLOR_ADD_VALUE = 0.01f;  //�G�t�F�N�g�̐F�����Z����Ƃ��̒l
	static const float EFFECT_SPIN_ADD_VALUE = 0.5f;    //�G�t�F�N�g�̉�]���x�����Z����Ƃ��̒l
	static const float EFFECT_MAX_SIZE = 4.0f;			//�G�t�F�N�g�̍ő�T�C�Y
}

//�X�V
void BackhandingState::Update2D(PlayerBase* player)
{
	//���͏����֐����Ă�
	HandleInput(player);
}

//3D�p�X�V
void BackhandingState::Update3D(PlayerBase* player)
{
	//�ł���Ȃ�
	if (player->GetState()->IsHitMove())
	{
		//���������߂�
		float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / BACKHAND_HIT_TIME);

		//�e�p�x�����߂�
		player->GetComponent<Transform>()->SetRotateY(startPlayerRotationAngle - (startPlayerRotationAngle - endPlayerRotationAngle) * ratio);
		player->GetRacket()->GetComponent<Transform>()->SetRotateY(RACKET_START_ROTATION_ANGLE - (RACKET_START_ROTATION_ANGLE - RACKET_END_ROTATION_ANGLE) * ratio);

		//������]���Ō�܂ŏI������̂Ȃ�
		if (ratio >= 1)
		{
			//��ԕύX
			player->GetState()->ChangeState(player->GetState()->playerStanding_, player);

			//���̊p�x�ɖ߂�
			player->GetComponent<Transform>()->SetRotateY(endPlayerRotationAngle);
			player->GetRacket()->GetComponent<Transform>()->SetRotateY(RACKET_END_ROTATION_ANGLE);

			//���̎p���ɖ߂��悤��
			player->GetState()->SetRestorePosture(true);

			//�ł��Ă��Ȃ���Ԃɂ���
			player->GetState()->SetHitMove(false);
		}
	}
	else
	{
		//���������߂�
		float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / BACKHAND_PULL_TIME);

		//�e�p�x�����߂�
		player->GetComponent<Transform>()->SetRotateY(endPlayerRotationAngle - (endPlayerRotationAngle - startPlayerRotationAngle) * ratio);
		player->GetRacket()->GetComponent<Transform>()->SetRotateY(RACKET_END_ROTATION_ANGLE - (RACKET_END_ROTATION_ANGLE - RACKET_START_ROTATION_ANGLE) * ratio);

		//1�ȏ�ɂȂ�Ȃ��悤��
		ARGUMENT_INITIALIZE(ratio, min<float>(ratio, 1.0f));

		//�G�~�b�^�[���擾����
		VFX::Emitter* d = VFX::GetEmitter(player->GetState()->GetChargeEffectNum());

		//���X�ɏk������悤��
		if (d != nullptr)
		{
			//�ʒu�X�V
			ARGUMENT_INITIALIZE(d->data.position, player->GetComponent<Transform>()->GetPosition());
			d->data.position.y += 1.0f;

			//�T�C�Y�X�V
			d->data.size.x += EFFECT_SIZE_ADD_VALUE;
			d->data.size.y += EFFECT_SIZE_ADD_VALUE;

			ARGUMENT_INITIALIZE(d->data.size.x, Clamp(d->data.size.x, EFFECT_MAX_SIZE, effectSize_.x));
			ARGUMENT_INITIALIZE(d->data.size.y, Clamp(d->data.size.y, EFFECT_MAX_SIZE, effectSize_.y));

			//�F�X�V
			d->data.color.x += EFFECT_COLOR_ADD_VALUE;
			d->data.color.y -= EFFECT_COLOR_ADD_VALUE;
			d->data.color.z -= EFFECT_COLOR_ADD_VALUE;
			d->data.color.w += EFFECT_COLOR_ADD_VALUE;
			d->data.spin.z  += EFFECT_SPIN_ADD_VALUE;
		}

		//������]���Ō�܂ŏI��������{�^���𗣂��Ă��邩���Ƃ��{�^���𗣂��Ă�����
		if (ratio >= 1 && (Input::IsPadButtonUp(player->GetState()->GetNowButtonCode(), player->GetState()->GetPlayerNum()) || !Input::IsPadButton(player->GetState()->GetNowButtonCode(), player->GetState()->GetPlayerNum())))
		{
			//�`���[�W�G�t�F�N�g�폜
			VFX::ForcedEnd(player->GetState()->GetChargeEffectNum());

			//�^�C�����擾
			float time = Time::GetTimef(hTime_);
			ARGUMENT_INITIALIZE(time,min<float>(time, 1.5f));

			//�ł��̔{����ݒ�
			player->GetRacket()->SetRatio(1-(time / 3));

			//�^�C�}�[���Z�b�g
			Time::Reset(hTime_);

			//�ł���ɐ؂�ւ���
			player->GetState()->SetHitMove(true);
		}
	}


	//���͏����֐����Ă�
	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void BackhandingState::HandleInput(PlayerBase* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void BackhandingState::Enter(PlayerBase* player)
{
	//�^�C�}�[�ǉ�
	ARGUMENT_INITIALIZE(hTime_, Time::Add());

	//�G�t�F�N�g�̃T�C�Y�ۑ�
	ARGUMENT_INITIALIZE(effectSize_, VFX::GetEmitter(player->GetState()->GetChargeEffectNum())->data.size);

	//��������������false��ݒ肵�Ă���
	player->GetState()->SetHitMove(false);

	//�p�x�ݒ�
	ARGUMENT_INITIALIZE(startPlayerRotationAngle,PLAYER_START_ROTATION_ANGLE);
	ARGUMENT_INITIALIZE(endPlayerRotationAngle,PLAYER_END_ROTATION_ANGLE);

	//��l�ڂ̃v���C���[�Ȃ�
	if (player->GetState()->GetPlayerNum() == 1)
	{
		startPlayerRotationAngle -= 180;
		endPlayerRotationAngle -= 180;
	}

	//�J�n�p�x
	player->GetComponent<Transform>()->SetRotateY(endPlayerRotationAngle);
	player->GetRacket()->GetComponent<Transform>()->SetRotateY(RACKET_END_ROTATION_ANGLE);
	ModelManager::SetAnimFlag(player->GetModelNum(), false);
}
