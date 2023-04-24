#include "PlayerStateManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include <math.h>

//�estatic�ϐ��̏�����
StandingState* PlayerStateManager::playerStanding_ = new StandingState;
ForehandingState* PlayerStateManager::playerForehanding_ = new ForehandingState;
BackhandingState* PlayerStateManager::playerBackhanding_ = new BackhandingState;
ServingState* PlayerStateManager::playerServing_ = new ServingState;
PlayerState* PlayerStateManager::playerState_ = playerStanding_;

////�萔
namespace
{
    const float RUN_SPEED = 1.5f;                 //�����Ă���Ƃ��̃L�����̃X�s�[�h
    const float PLAYER_WALK_ANIM_SPEED = 1.0f;    //�A�j���[�V�����̍Đ����x
    const float ANIM_RUN_SPEED = 2.0f;            //�A�j���[�V�����̍Đ����x(�����Ă�Ƃ�)
}

//�R���X�g���N�^
PlayerStateManager::PlayerStateManager():front_(STRAIGHT_VECTOR)
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

    //�����Ă����Ԃ���Ȃ��̂Ȃ�
    if (playerState_ != PlayerStateManager::playerStanding_)
    {
        //�������̂ŃA�j���[�V����
        Model::SetAnimFlag(player->GetModelNum(), true);
        Model::SetAnimFlag(player->GetRacket()->GetModelNum(), true);

        //���݂̏�Ԃ̍X�V���Ă�
        playerState_->Update3D(player);
        return;
    }

    //L�X�e�B�b�N�̌X�����擾
    float PadLx = Input::GetPadStickL().x;
    float PadLy = Input::GetPadStickL().y;

    //�����ł��������̂Ȃ�
    if (PadLx != ZERO || PadLy != ZERO)
    {
        //�������̂ŃA�j���[�V����
        Model::SetAnimFlag(player->GetModelNum(), true);
        Model::SetAnimFlag(player->GetRacket()->GetModelNum(), true);

        //��]�s��
        XMMATRIX rotateX, rotateY, rotateZ;
        rotateX = XMMatrixRotationX(XMConvertToRadians(ZERO));
        rotateY = XMMatrixRotationY(XMConvertToRadians(XMConvertToDegrees(atan2(-PadLx, -PadLy))));
        rotateZ = XMMatrixRotationZ(XMConvertToRadians(ZERO));
        XMMATRIX matRotate = rotateZ * rotateX * rotateY;

        //Player�̈ړ�
        player->SetPosition(Float3Add(player->GetPosition(), VectorToFloat3(XMVector3TransformCoord(front_ / 10.0f, matRotate))));
    }
    //�����Ă��Ȃ��̂Ȃ�A�j���[�V�������~�߂�
    else
    {
        Model::SetAnimFlag(player->GetModelNum(), false);
        Model::SetAnimFlag(player->GetRacket()->GetModelNum(), false);
    }

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