#include "PlayerBase.h"
#include "../Engine/System.h"
#include "../OtherObject/TitleScene/Racket.h"
#include "../OtherObject/TitleScene/Ball.h"

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

    pRacket_(nullptr),
    pState_(new PlayerStateManager),

    ///////////////////�J����///////////////////////

    camVec_(XMVectorSet(ZERO,ZERO,ZERO,ZERO))

{
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void PlayerBase::ChildInitialize()
{
    ///////////////////������///////////////////////

    //���
    ARGUMENT_INITIALIZE(pState_->playerState_ , pState_->playerStanding_);
    pState_->SetPlayerNum(GameManager::SetPlayer(this));

    //�e
    SetShadow(true);

    ///////////////�A�j���[�V�����ݒ�///////////////////

    //�A�j���[�V����
    ModelManager::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, PLAYER_ANIM_SPEED);

    ///////////////���P�b�g����///////////////////

    ARGUMENT_INITIALIZE(pRacket_,Instantiate<Racket>(this));

    ////////////////////�J����//////////////////////

    //1�l�ڂ̃v���C���[�Ȃ�
    if (pState_->GetPlayerNum() == 0)
    {
        ARGUMENT_INITIALIZE(camVec_, (transform_->position_ - Camera::GetPosition()));
    }
    else
        ARGUMENT_INITIALIZE(camVec_, (transform_->position_ - Camera::GetPositionTwo()));
    
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
    //Z�̈ʒu���i�[����p
    vector<float> zPos;

    //�{�[�����擾
    Ball* pBall = ((Ball*)FindObject("Ball"));
    if (pBall)
        zPos.push_back(pBall->GetComponent<Transform>()->GetPosition().z);

    //�����ȊO�̃v���C���[���擾
    PlayerBase* pPlayer = GameManager::GetNotMyPlayer(this);
    if (pPlayer)
        zPos.push_back(pPlayer->GetComponent<Transform>()->GetPosition().z);

    //�������g���i�[
    zPos.push_back(transform_->position_.z);

    //�ŏ��l�ő�l���擾
    pair<vector<float>::iterator, vector<float>::iterator> minmax;
    minmax = minmax_element(zPos.begin(), zPos.end());
    float MaxZ = *minmax.second;
    float MinZ = *minmax.first;

    float sum = abs(MaxZ + MinZ);
   
    //1�l�ڂ̃v���C���[�Ȃ�
    if (pState_->GetPlayerNum() == 0)
    {
        XMFLOAT3 pos = Camera::GetPosition();
        XMFLOAT3 tar = Camera::GetTarget();
        Camera::SetPosition(XMFLOAT3(pos.x,( transform_->position_.y - XMVectorGetY(camVec_)) * 1 + (sum * 0.2), (transform_->position_.z -  XMVectorGetZ(camVec_)) * 1 + (sum * 0.2)));
        Camera::SetTarget(XMFLOAT3(tar.x, tar.y,0));
    }
    //2�l�ڂ̃v���C���[�Ȃ�
    else
    {
        XMFLOAT3 pos = Camera::GetPositionTwo();
        XMFLOAT3 tar = Camera::GetTargetTwo();
        Camera::SetPositionTwo(XMFLOAT3(pos.x, (transform_->position_.y - XMVectorGetY(camVec_)) * 1 + (sum * 0.2), (transform_->position_.z - XMVectorGetZ(camVec_)) * 1 + (-sum * 0.2)));
        Camera::SetTargetTwo(XMFLOAT3(tar.x, tar.y, 0));
    }
}

