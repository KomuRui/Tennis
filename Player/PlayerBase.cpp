#include "PlayerBase.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/GameObject/Light.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../Engine/ResourceManager/Audio.h"

////�萔
namespace
{
    //Player�̃p�����[�^��ۑ����Ă���p�X
    LPCTSTR parameterPath = "Parameter/Player/PlayerParameter.ini";

    ///////////////�L�����̕K�v�ȏ��///////////////////

    static const float PLAYER_ANIM_SPEED = GetPrivateProfilefloat("PLAYER", "AnimSpeed", "1.0", parameterPath);                //�A�j���[�V�����̍Đ����x
    static const int ANIM_START_FRAME = (int)GetPrivateProfilefloat("PLAYER", "AnimStartFrame", "1", parameterPath);                //�A�j���[�V�����̊J�n�t���[��
    static const int ANIM_END_FRAME = (int)GetPrivateProfilefloat("PLAYER", "AnimEndFrame", "60", parameterPath);			       //�A�j���[�V�����̏I���t���[��
    static const int MAX_NORMAL_RADIANS = (int)GetPrivateProfilefloat("PLAYER", "MaxNormalRadians", "50", parameterPath);   	       //�@���Ƃ̍ő�p�x			

    ////////////////�R���C�_�[///////////////////

    static const XMFLOAT3 COLLIDER_POS = { ZERO,ZERO,ZERO };  //�R���C�_�[�̈ʒu
    static const float    COLLIDER_SIZE = 1.0f;               //�R���C�_�[�̃T�C�Y
}

//�R���X�g���N�^
PlayerBase::PlayerBase(GameObject* parent)
    :Mob(parent, "MainCharacter/Star_Main_Character.fbx", "Player"),

    ///////////////�L�����̕K�v�ȏ��///////////////////

    //�L�����̎���]�ɕK�v�ȕϐ�
    jampRotationPreviousAngle_(ZERO),
    mPreviousAngle_(XMMatrixIdentity()),
    normalInterpolation_(0.045f),
    isCheckNormal_(true),
    isBeforeLand_(true),

    //���̑�
    acceleration_(1),
    pState_(new PlayerStateManager),

    ///////////////////�J����///////////////////////

    camMat_(XMMatrixIdentity()),
    vCam_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
    camVec_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
    camStatus_(LONG),
    camAngle_(1),
    isMoveCamPos_(true),
    isLockcam_(false)

{
    camVecTotal_[LONG] = XMVectorSet(ZERO, 15,-15, ZERO);
    camVecTotal_[SHORT] = XMVectorSet(ZERO, 3, -3, ZERO);
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void PlayerBase::ChildInitialize()
{
    ///////////////////������///////////////////////

    //���
    ARGUMENT_INITIALIZE(PlayerStateManager::playerState_ ,PlayerStateManager::playerStanding_);

    //�������ɏ��������Ă���
    ARGUMENT_INITIALIZE(camVec_, camVecTotal_[LONG]);

    //��]���鎞��]�s����g���悤�ɂ���
    ARGUMENT_INITIALIZE(transform_.mFlag_,true);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(COLLIDER_POS, COLLIDER_SIZE);
    AddCollider(collision);

    //���g�̃|�W�V�����Z�b�g
    ARGUMENT_INITIALIZE(transform_.position_, GameManager::GetpStage()->GetPos());

    ///////////////�A�j���[�V�����ݒ�///////////////////

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, PLAYER_ANIM_SPEED);

    //�p����p�̏�����
    ChildPlayerInitialize();
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void PlayerBase::ChildStartUpdate()
{
    //���g�̖@�������
    ARGUMENT_INITIALIZE(vNormal_, UP_VECTOR);

    //�p����p
    ChildPlayerStartUpdate();
}

//�X�V
void PlayerBase::Update()
{
    //null�Ȃ�return
    if (pstage_ == nullptr) return;

    //�^���̖@���𒲂ׂ�
    CheckUnderNormal();

    //�p����p�̍X�V
    ChildPlayerUpdate();

    //�J�����̋���
    CameraBehavior();
}

//�^���̖@���𒲂ׂăL�����̏㎲�����肷��
void PlayerBase::CheckUnderNormal()
{
    //���C��^���ɑł�
    RayCastData data;
    ARGUMENT_INITIALIZE(data.start,transform_.position_);
    ARGUMENT_INITIALIZE(data.dir,VectorToFloat3(down_));
    Model::AllRayCast(hGroundModel_, &data);

    //�@���𒲂ׂ邩�ǂ�����Flag��true�Ȃ�
    if (isCheckNormal_)
    {
        //���C���������Ă��Ă������ł���x�N�g����vNormal_�̒l���Ⴄ�̂Ȃ�
        if (data.hit && (XMVectorGetX(vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetY(-vNormal_) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetZ(-vNormal_) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data.normal)))))
        {
            //���̃L�����̏�x�N�g��vNormal�Ɖ��̖@���̓��ς����߂�
            float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data.normal)), XMVector3Normalize(vNormal_)));

            //�p�x��50�x�ȓ��Ɏ��܂��Ă�����(�ǂƂ��ɏ�点�Ȃ�����)
            if (acos(dotX) < XMConvertToRadians((float)MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-(float)MAX_NORMAL_RADIANS))
            {
                //������ƕ��
                vNormal_ = XMVector3Normalize((XMVectorLerp(XMVector3Normalize(vNormal_), XMLoadFloat3(&data.normal), normalInterpolation_)));
                ARGUMENT_INITIALIZE(down_,-vNormal_);
            }

        }
    }
}

//�J�����̏���
void PlayerBase::CameraBehavior()
{
    //�J�������Ԃ��Ĉړ����������̂�Player�̃|�W�V�������o���Ă���
    static XMFLOAT3 camTar = transform_.position_;
    static XMFLOAT3 campos = transform_.position_;

    //�J�����Œ肳��Ă���̂Ȃ�
    if (isLockcam_) { CameraLockBehavior(&campos, &camTar); return; }

    //Player�̃J�����̏���(2D��3D�ŃJ�����̓������Ⴄ)
    PlayerCameraBehavior(&campos,&camTar);
}


/// <summary>
/// �J���������b�N����Ă������̃J�����̏���
/// </summary>
void PlayerBase::CameraLockBehavior(XMFLOAT3 *pos, XMFLOAT3 *tar)
{
    //�J�����̃|�W�V������y����Player�Ɠ����ɂ���(���������Ōv�Z����������)
    XMFLOAT3 camPos = Camera::GetPosition();
    ARGUMENT_INITIALIZE(camPos.y, transform_.position_.y);

    //�J��������Player�ւ̕����x�N�g��
    XMVECTOR dir = XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&camPos);

    //�p�x���߂�
    float dotX = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(dir), pState_->GetFrontVec())));

    //���߂��p�x��������]
    transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, dotX);

    ARGUMENT_INITIALIZE(camAngle_, ZERO);
    ARGUMENT_INITIALIZE(*pos, Camera::GetPosition());
    ARGUMENT_INITIALIZE(*tar, Camera::GetTarget());

    //���C�g�ݒ�
    XMFLOAT3 lightPos;
    XMStoreFloat3(&lightPos, vNormal_ + XMLoadFloat3(&transform_.position_));
    Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));

}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void PlayerBase::TimeMethod()
{
    Enter();
}

//�����蔻��
void PlayerBase::OnCollision(GameObject* pTarget)
{

}
