#include "BackhandingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/ResourceManager/Easing.h"

//�萔
namespace
{
	static const int PLAYER_START_ROTATION_ANGLE = 70;  //�v���C���[�̊J�n�p�x
	static const int RACKET_START_ROTATION_ANGLE = -200;//���P�b�g�̊J�n�p�x
	static const int PLAYER_END_ROTATION_ANGLE = 180;   //�v���C���[�̏I���p�x
	static const int RACKET_END_ROTATION_ANGLE = -105;  //���P�b�g�̏I���p�x

	static const float BACKHAND_PULL_TIME = 0.2f;       //�o�b�N�n���h�̈�������
	static const float BACKHAND_HIT_TIME = 0.1f;        //�o�b�N�n���h�̑ł���
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
	if (isHitMove_)
	{
		//���������߂�
		float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / BACKHAND_HIT_TIME);

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

			//���̎p���ɖ߂��悤��
			player->pState_->SetRestorePosture(true);
		}
	}
	else
	{
		//���������߂�
		float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / BACKHAND_PULL_TIME);

		//�e�p�x�����߂�
		player->SetRotateY(PLAYER_END_ROTATION_ANGLE - (PLAYER_END_ROTATION_ANGLE - PLAYER_START_ROTATION_ANGLE) * ratio);
		player->GetRacket()->SetRotateY(RACKET_END_ROTATION_ANGLE - (RACKET_END_ROTATION_ANGLE - RACKET_START_ROTATION_ANGLE) * ratio);

		//������]���Ō�܂ŏI������̂Ȃ�
		if (ratio >= 1)
		{
			//�^�C�}�[���Z�b�g
			Time::Reset(hTime_);

			//�ł���ɐ؂�ւ���
			ARGUMENT_INITIALIZE(isHitMove_, true);
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

	//��������������false��ݒ肵�Ă���
	ARGUMENT_INITIALIZE(isHitMove_, false);

	//�J�n�p�x
	player->SetRotateY(PLAYER_END_ROTATION_ANGLE);
	player->GetRacket()->SetRotateY(RACKET_END_ROTATION_ANGLE);
	Model::SetAnimFlag(player->GetModelNum(), false);
}
