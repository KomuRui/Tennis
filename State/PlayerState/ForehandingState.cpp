#include "ForehandingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Engine/ResourceManager/VFX.h"
#include "../../Manager/EffectManager/EffectManager.h"

//�萔
namespace
{
	static const int PLAYER_START_ROTATION_ANGLE = 290; //�v���C���[�̊J�n�p�x
	static const int RACKET_START_ROTATION_ANGLE = -90; //���P�b�g�̊J�n�p�x
	static const int PLAYER_END_ROTATION_ANGLE = 180;   //�v���C���[�̏I���p�x
	static const int RACKET_END_ROTATION_ANGLE = -185;  //���P�b�g�̏I���p�x

	static const float FOREHAND_PULL_TIME = 0.2f;       //�t�H�A�n���h�̈�������
	static const float FOREHAND_HIT_TIME = 0.2f;        //�t�H�A�n���h�̑ł���

	////////////�G�t�F�N�g////////////

	static const float EFFECT_SIZE_ADD_VALUE = 0.04f;   //�G�t�F�N�g�̃T�C�Y�����Z����Ƃ��̒l
	static const float EFFECT_COLOR_ADD_VALUE = 0.01f;  //�G�t�F�N�g�̐F�����Z����Ƃ��̒l
	static const float EFFECT_SPIN_ADD_VALUE = 0.5f;    //�G�t�F�N�g�̉�]���x�����Z����Ƃ��̒l
	static const float EFFECT_MAX_SIZE = 4.0f;		    //�G�t�F�N�g�̍ő�T�C�Y
}

//�X�V
void ForehandingState::Update2D(PlayerBase* player)
{
	//���͏����֐����Ă�
	HandleInput(player);
}

//3D�p�X�V
void ForehandingState::Update3D(PlayerBase* player)
{
	//�ł���Ȃ�
	if (player->pState_->IsHitMove())
	{
		//���������߂�
		float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / FOREHAND_HIT_TIME);

		//�e�p�x�����߂�
		player->SetRotateY(PLAYER_START_ROTATION_ANGLE - (PLAYER_START_ROTATION_ANGLE - PLAYER_END_ROTATION_ANGLE) * ratio);
		player->GetRacket()->SetRotateY(RACKET_START_ROTATION_ANGLE - (RACKET_START_ROTATION_ANGLE - RACKET_END_ROTATION_ANGLE) * ratio);

		//������]���Ō�܂ŏI������̂Ȃ�
		if (ratio >= 1)
		{
			//��ԕύX
			PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
			PlayerStateManager::playerState_->Enter(player);

			//���̊p�x�ɖ߂�
			player->SetRotateY(PLAYER_END_ROTATION_ANGLE);
			player->GetRacket()->SetRotateY(RACKET_END_ROTATION_ANGLE);

			//�ł��Ă��Ȃ���Ԃɂ���
			player->pState_->SetHitMove(false);
		}
	}
	else
	{
		//���������߂�
		float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / FOREHAND_PULL_TIME);

		//�e�p�x�����߂�
		player->SetRotateY(PLAYER_END_ROTATION_ANGLE - (PLAYER_END_ROTATION_ANGLE - PLAYER_START_ROTATION_ANGLE) * ratio);
		player->GetRacket()->SetRotateY(RACKET_END_ROTATION_ANGLE - (RACKET_END_ROTATION_ANGLE - RACKET_START_ROTATION_ANGLE) * ratio);

		//1�ȏ�ɂȂ�Ȃ��悤��
		ARGUMENT_INITIALIZE(ratio,min<float>(ratio, 1.0f));
		 
		//�G�~�b�^�[���擾����
		VFX::Emitter* d = VFX::GetEmitter(player->pState_->GetChargeEffectNum());

		//���X�ɏk������悤��
		if (d != nullptr)
		{
			d->data.size.x += EFFECT_SIZE_ADD_VALUE;
			d->data.size.y += EFFECT_SIZE_ADD_VALUE;

			ARGUMENT_INITIALIZE(d->data.size.x,Clamp(d->data.size.x, EFFECT_MAX_SIZE, effectSize_.x));
			ARGUMENT_INITIALIZE(d->data.size.y,Clamp(d->data.size.y, EFFECT_MAX_SIZE, effectSize_.y));

			d->data.color.x += EFFECT_COLOR_ADD_VALUE;
			d->data.color.y -= EFFECT_COLOR_ADD_VALUE;
			d->data.color.z -= EFFECT_COLOR_ADD_VALUE;
			d->data.color.w += EFFECT_COLOR_ADD_VALUE;
			d->data.spin.z += EFFECT_SPIN_ADD_VALUE;
		}

		//������]���Ō�܂ŏI��������{�^���𗣂��Ă��邩���Ƃ��{�^���𗣂��Ă�����
		if (ratio >= 1 && (Input::IsPadButtonUp(player->pState_->GetNowButtonCode()) || !Input::IsPadButton(player->pState_->GetNowButtonCode())))
		{
			//�`���[�W�G�t�F�N�g�폜
			VFX::ForcedEnd(player->pState_->GetChargeEffectNum());

			//�ł��̔{����ݒ�
			player->GetRacket()->SetRatio(1 - (Time::GetTimef(hTime_) / 3));

			//�^�C�}�[���Z�b�g
			Time::Reset(hTime_);

			//�ł���ɐ؂�ւ���
			player->pState_->SetHitMove(true);
		}
	}
	
	//���͏����֐����Ă�
	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void ForehandingState::HandleInput(PlayerBase* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void ForehandingState::Enter(PlayerBase* player)
{
	//�^�C�}�[�ǉ�
	ARGUMENT_INITIALIZE(hTime_, Time::Add());

	//�G�t�F�N�g�̃T�C�Y�ۑ�
	ARGUMENT_INITIALIZE(effectSize_, VFX::GetEmitter(player->pState_->GetChargeEffectNum())->data.size);

	//��������������false��ݒ肵�Ă���
	player->pState_->SetHitMove(false);

	//�J�n�p�x
	player->SetRotateY(PLAYER_END_ROTATION_ANGLE);
	player->GetRacket()->SetRotateY(RACKET_END_ROTATION_ANGLE);
	Model::SetAnimFlag(player->GetModelNum(), false);
}
