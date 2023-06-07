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

    //���邳�ő��
    ModelManager::SetBrightness(hModel_, 1.0f);

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
        ARGUMENT_INITIALIZE(camVec2_, (Camera::GetTarget() - Camera::GetPosition()));
    }
    else
    {
        ARGUMENT_INITIALIZE(camVec_, (transform_->position_ - Camera::GetPositionTwo()));
        ARGUMENT_INITIALIZE(camVec2_, (Camera::GetTarget() - Camera::GetPositionTwo()));
    }
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
    vector<float> zPos; //Z�̈ʒu���i�[����p
    vector<float> xPos; //X�̈ʒu���i�[����p

    //�{�[�����擾
    Ball* pBall = ((Ball*)FindObject("Ball"));
    if (pBall)
    {
        zPos.push_back(pBall->GetComponent<Transform>()->GetPosition().z);
        xPos.push_back(pBall->GetComponent<Transform>()->GetPosition().x);
    }

    //�����ȊO�̃v���C���[���擾
    PlayerBase* pPlayer = GameManager::GetNotMyPlayer(this);
    if (pPlayer)
    {
        zPos.push_back(pPlayer->GetComponent<Transform>()->GetPosition().z);
        xPos.push_back(pPlayer->GetComponent<Transform>()->GetPosition().x);
    }

    //�������g���i�[
    zPos.push_back(transform_->position_.z);
    xPos.push_back(transform_->position_.x);

    //�ŏ��l�ő�l���擾
    pair<vector<float>::iterator, vector<float>::iterator> minmax;
    minmax = minmax_element(zPos.begin(), zPos.end());
    float MaxZ = *minmax.second;
    float MinZ = *minmax.first;
    float sum = abs(MaxZ + MinZ);

    //�d�S���߂�
    float centerX = 0;
    for (auto i = xPos.begin(); i != xPos.end(); i++)
    {
        centerX += (*i);
    }
    centerX /= xPos.size();
   
    //1�l�ڂ̃v���C���[�Ȃ�
    if (pState_->GetPlayerNum() == 0)
    {
        XMFLOAT3 pos = Camera::GetPosition();
        XMFLOAT3 tar = Camera::GetTarget();
        XMFLOAT3 nextPos = { centerX, (transform_->position_.y - XMVectorGetY(camVec_)) * 1.0f + (sum * 0.25f), (MaxZ - XMVectorGetZ(camVec_)) * 1.0f + (sum * 0.25f) };
        nextPos = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&pos), XMLoadFloat3(&nextPos), 0.1f));
        XMFLOAT3 nextTar = VectorToFloat3((nextPos + camVec2_));
        nextTar = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&tar), XMLoadFloat3(&nextTar), 0.1f));
        Camera::SetPosition(nextPos);
        Camera::SetTarget(nextTar);
    }
    //2�l�ڂ̃v���C���[�Ȃ�
    else
    {
        XMFLOAT3 pos = Camera::GetPositionTwo();
        XMFLOAT3 tar = Camera::GetTargetTwo();
        XMFLOAT3 nextPos = { centerX, (transform_->position_.y - XMVectorGetY(camVec_)) * 1.0f + (sum * 0.25f), (MinZ - XMVectorGetZ(camVec_)) * 1.0f + (sum * 0.25f) };
        nextPos = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&pos), XMLoadFloat3(&nextPos), 0.1f));
        XMFLOAT3 nextTar = VectorToFloat3((nextPos + camVec2_));
        nextTar = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&tar), XMLoadFloat3(&nextTar), 0.1f));
        Camera::SetPositionTwo(nextPos);
        Camera::SetTargetTwo(nextTar);
    }
}

