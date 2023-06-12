#include "PlayerStateManager.h"
#include "../../Engine/System.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../OtherObject/TitleScene/Ball.h"
#include "../../OtherObject/TitleScene/Referee.h"
#include <math.h>


////�萔
namespace
{
    static const XMFLOAT3 RACKET_END_ROTATION_ANGLE = { 0,-185,0 }; //���P�b�g�̏I���p�x
    static const float RUN_SPEED = 1.5f;                            //�����Ă���Ƃ��̃L�����̃X�s�[�h
    static const float PLAYER_WALK_ANIM_SPEED = 1.0f;               //�A�j���[�V�����̍Đ����x
    static const float ANIM_RUN_SPEED = 2.0f;                       //�A�j���[�V�����̍Đ����x(�����Ă�Ƃ�)
    static const float POSSTURE_RESTORE_TIME = 5.0f;                //���̎p���ɖ߂�����
}

//�R���X�g���N�^
PlayerStateManager::PlayerStateManager():front_(STRAIGHT_VECTOR),hTime_(Time::Add()), 
    isRestorePosture_(false), isHitMove_(false),buttonCode_(XINPUT_GAMEPAD_A), hChargeEffectName_("chargeEffect"), chargeTime_(ZERO), playerNum_(ZERO)
{
    playerStanding_ = new StandingState;
    playerForehanding_ = new ForehandingState;
    playerBackhanding_ = new BackhandingState;
    playerServing_ = new ServingState;
    playerState_ = playerStanding_;
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
    if (playerState_ != playerStanding_)
    {
        //�^�C�}�[������
        Time::Reset(hTime_);
        Time::Lock(hTime_);
    }

    //���̎p���ɖ߂��̂Ȃ�
    if (isRestorePosture_)
    {
        //���b�N����Ă���̂Ȃ����
        if (Time::isLock(hTime_))Time::UnLock(hTime_);

        //���������߂�
        float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / POSSTURE_RESTORE_TIME);

        //�e�p�x�����߂�
        player->GetRacket()->GetComponent<Transform>()->SetRotate(VectorToFloat3(XMVectorLerp(XMLoadFloat3(new XMFLOAT3(player->GetRacket()->GetComponent<Transform>()->GetRotate())), XMLoadFloat3(&RACKET_END_ROTATION_ANGLE), ratio)));
        
        //������]���Ō�܂ŏI������̂Ȃ�
        if (ratio >= 1)
        {
            //�߂����ɐݒ�
            ARGUMENT_INITIALIZE(isRestorePosture_, false);

            //�^�C�}�[������
            Time::Reset(hTime_);
            Time::Lock(hTime_);
        }
    }

    //L�X�e�B�b�N�̌X�����擾
    float PadLx = Input::GetPadStickL(playerNum_).x;
    float PadLy = Input::GetPadStickL(playerNum_).y;

    //2�l�ڂ̃v���C���[�Ȃ甽�]������
    if (playerNum_ == 1)
    {
        PadLx *= -1;
        PadLy *= -1;
    }

    //�T�[�u��Ԃ��T�[�o�[�Ȃ�
    if (GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_SERVE_RECEIVE &&
       (GameManager::GetReferee()->IsServer(player)))
    {
        //�T�[�u�̎��̈ړ�����
        ServeMove(player, PadLx, PadLy);

        //���݂̏�Ԃ̍X�V���Ă�
        playerState_->Update3D(player);

        return;
    }
    
    //�ړ�
    Move(player, PadLx, PadLy);

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
    playerState_ = change;
    playerState_->Enter(player);
}

/// <summary>
/// �ړ�
/// </summary>
void PlayerStateManager::Move(PlayerBase* player, float padLx, float padLy)
{
    //�����ł��������̂Ȃ�
    if (padLx != ZERO || padLy != ZERO)
    {
        //�������̂ŃA�j���[�V����
        ModelManager::SetAnimFlag(player->GetModelNum(), true);

        //��]�s��
        XMMATRIX rotateX, rotateY, rotateZ;
        rotateX = XMMatrixRotationX(XMConvertToRadians(ZERO));
        rotateY = XMMatrixRotationY(XMConvertToRadians(XMConvertToDegrees(atan2(-padLx, -padLy))));
        rotateZ = XMMatrixRotationZ(XMConvertToRadians(ZERO));
        XMMATRIX matRotate = rotateZ * rotateX * rotateY;

        //Player�̈ړ�
        //�t�H�A���o�b�N�n���h��ԂȂ�
        if (playerState_ == PlayerStateManager::playerBackhanding_ || playerState_ == PlayerStateManager::playerForehanding_)
        {
            //�A�j���[�V�����~�߂�
            ModelManager::SetAnimFlag(player->GetModelNum(), false);

            //�{�[���̃|�C���^
            Ball* pBall = GameManager::GetpBall();

            //�e�|�W�V�������L���p
            float ballEndX = ZERO;
            float playerX = ZERO;

            //nullptr����Ȃ��̂Ȃ�
            if (pBall != nullptr)
            {
                ballEndX = pBall->GetSpecifyPosZBallPosition(player->GetComponent<Transform>()->GetPosition().z).x;
                playerX = player->GetComponent<Transform>()->GetPosition().x;
            }

            //�������擾
            float dis = abs(playerX - ballEndX);

            //�������萔�ȉ��Ȃ�
            if (dis <= 3.0f)
            {
                player->GetComponent<Transform>()->SetPosition(Float3Add(player->GetComponent<Transform>()->GetPosition(), VectorToFloat3(XMVector3TransformCoord(((front_ / 10.0f) * RUN_SPEED) * (dis / 3.0f * 0.5f), matRotate))));
            }
            else
            {
                player->GetComponent<Transform>()->SetPosition(Float3Add(player->GetComponent<Transform>()->GetPosition(), VectorToFloat3(XMVector3TransformCoord(((front_ / 10.0f) * RUN_SPEED) * 0.5f, matRotate))));
            }
        }
        //�T�[�u��Ԃ���Ȃ��̂Ȃ�
        else if (playerState_ != PlayerStateManager::playerServing_)
            player->GetComponent<Transform>()->SetPosition(Float3Add(player->GetComponent<Transform>()->GetPosition(), VectorToFloat3(XMVector3TransformCoord((front_ / 10.0f) * RUN_SPEED, matRotate))));

        //��]
        player->GetComponent<Transform>()->SetRotateY(XMConvertToDegrees(atan2(-padLx, -padLy)));
    }
    //�����Ă��Ȃ��̂Ȃ�A�j���[�V�������~�߂�
    else
        ModelManager::SetAnimFlag(player->GetModelNum(), false);
}

/// <summary>
/// �T�[�u�̎��̈ړ�
/// </summary>
void PlayerStateManager::ServeMove(PlayerBase* player, float padLx, float padLy)
{
    //�\���Ă��Ȃ��̂Ȃ�
    if (!playerServing_->IsCharge())
    {
        //�{�[���ʒu���C������
        XMFLOAT3 ballPos = ModelManager::GetBonePosition(player->GetModelNum(), "Left");
        GameManager::GetpBall()->GetComponent<Transform>()->SetPosition(ballPos);
    }

    //�����ł������Ă邩�\���Ă��Ȃ����
    if ((padLx != ZERO || padLy != ZERO) && !playerServing_->IsCharge())
    {
        //�A�j���[�V�����͂��Ȃ�
        ModelManager::SetAnimFlag(player->GetModelNum(), false);

        //��]�s��
        XMMATRIX rotateX, rotateY, rotateZ;
        rotateX = XMMatrixRotationX(XMConvertToRadians(ZERO));
        rotateY = XMMatrixRotationY(XMConvertToRadians(XMConvertToDegrees(atan2(-padLx,0))));
        rotateZ = XMMatrixRotationZ(XMConvertToRadians(ZERO));
        XMMATRIX matRotate = rotateZ * rotateX * rotateY;

        //�ړ�
        XMFLOAT3 moveValue = VectorToFloat3(XMVector3TransformCoord(((front_ / 10.0f) * RUN_SPEED) * 0.5f, matRotate));
        ARGUMENT_INITIALIZE(moveValue.z, ZERO);
        player->GetComponent<Transform>()->SetPosition(Float3Add(player->GetComponent<Transform>()->GetPosition(), moveValue));
        player->GetComponent<Transform>()->SetPositionX(Clamp<float>(player->GetComponent<Transform>()->GetPosition().x, 0, -4));
    }
}