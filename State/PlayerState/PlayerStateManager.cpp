#include "PlayerStateManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/GUI/ImGuiSet.h"

//�estatic�ϐ��̏�����
StandingState* PlayerStateManager::playerStanding_ = new StandingState;
PlayerState* PlayerStateManager::playerState_ = playerStanding_;

////�萔
namespace
{
    const float RUN_SPEED = 1.5f;                 // GetPrivateProfilefloat("PLAYER", "RunSpeed", "0.02", ".\\/Parameter/Player/PlayerParameter.ini");//�����Ă���Ƃ��̃L�����̃X�s�[�h
    const float PLAYER_WALK_ANIM_SPEED = 1.0f;    //�A�j���[�V�����̍Đ����x
    const float ANIM_RUN_SPEED = 2.0f;            //�A�j���[�V�����̍Đ����x(�����Ă�Ƃ�)
}

//�R���X�g���N�^
PlayerStateManager::PlayerStateManager():front_(XMVectorSet(0, 0, 1.0f, 0))
{
}

//�X�V
void PlayerStateManager::Update2D(PlayerBase* player)
{
   
	//���݂̏�Ԃ̍X�V���Ă�
	playerState_->Update2D(player);
}

//3D�p�X�V
void PlayerStateManager::Update3D(PlayerBase* player)
{

    //���݂̏�Ԃ̍X�V���Ă�
    playerState_->Update3D(player);
}

//���͂ɂ���ď�ԕω�����
void PlayerStateManager::HandleInput(PlayerBase* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void PlayerStateManager::Enter(PlayerBase* player)
{
}

//��ԃ`�F���W�p
void PlayerStateManager::ChangeState(PlayerState* change, PlayerBase* player)
{
    PlayerStateManager::playerState_ = change;
    PlayerStateManager::playerState_->Enter(player);
}