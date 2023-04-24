#include "PlayerBase.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/GameObject/Light.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../Engine/ResourceManager/Audio.h"
#include "../OtherObject/TitleScene/Racket.h"

////�萔
namespace
{
    ///////////////�L�����̕K�v�ȏ��///////////////////

    static const float PLAYER_ANIM_SPEED = 2.0f;   //�A�j���[�V�����̍Đ����x
    static const int ANIM_START_FRAME = 1;         //�A�j���[�V�����̊J�n�t���[��
    static const int ANIM_END_FRAME = 60;		   //�A�j���[�V�����̏I���t���[��
}

//�R���X�g���N�^
PlayerBase::PlayerBase(GameObject* parent, std::string modelFilePath_, std::string name)
    :NormalObject(parent, modelFilePath_, name),

    ///////////////�L�����̕K�v�ȏ��///////////////////

    //���̑�
    pState_(new PlayerStateManager),

    ///////////////////�J����///////////////////////

    camMat_(XMMatrixIdentity()),
    vCam_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
    camVec_(XMVectorSet(ZERO,ZERO,ZERO,ZERO))

{
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void PlayerBase::ChildInitialize()
{
    ///////////////////������///////////////////////

    //���
    ARGUMENT_INITIALIZE(PlayerStateManager::playerState_ ,PlayerStateManager::playerStanding_);

    ///////////////�A�j���[�V�����ݒ�///////////////////

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, PLAYER_ANIM_SPEED);

    ///////////////���P�b�g����///////////////////

    ARGUMENT_INITIALIZE(pRacket_,Instantiate<Racket>(this));
}


//�X�V
void PlayerBase::ChildUpdate()
{
    //�X�V
    pState_->Update3D(this);

    //�J�����̋���
    CameraBehavior();
}

//�J�����̏���
void PlayerBase::CameraBehavior()
{
}


//�����蔻��
void PlayerBase::OnCollision(GameObject* pTarget)
{
}
