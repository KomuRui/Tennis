#include "PlayerBase.h"
#include "../Engine/System.h"
#include "../OtherObject/PlayScene/Racket.h"
#include "../OtherObject/PlayScene/Ball.h"
#include "../OtherObject/PlayScene/Referee.h"

////�萔
namespace
{
    ///////////////�L�����̕K�v�ȏ��///////////////////

    static const XMFLOAT3 PLAYER_SERVE_ROTATION_ANGLE = { 0,240,0 };   //�v���C���[�̊J�n�p�x
    static const XMFLOAT3 CAM_TAR_ADD_VALUE = { 0,1,0 };               //�J�����̏œ_�ɉ��Z����l
    static const float PLAYER_ANIM_SPEED = 2.0f;   //�A�j���[�V�����̍Đ����x
    static const int ANIM_START_FRAME = 1;         //�A�j���[�V�����̊J�n�t���[��
    static const int ANIM_END_FRAME = 60;		   //�A�j���[�V�����̏I���t���[��

    ///////////////////�J����///////////////////////

    static const XMFLOAT3 CAM_POS_SERVE_RECEIVE = { -2, 3.67f, 20.17f };     //�T�[�u���V�[�u���̃J�����̈ʒu
    static const XMFLOAT3 CAM_TAR_SERVE_RECEIVE = { 0, -2.27f, 0 };          //�T�[�u���V�[�u���̃J�����̏œ_

    static const XMFLOAT3 CAM_POS_NORMAL = { 0, 10.67f, 24.17f };   //�ʏ펞�̃J�����̈ʒu
    static const XMFLOAT3 CAM_TAR_NORMAL = { 0, -2.27f, 0 };        //�ʏ펞�̃J�����̏œ_
}

//�R���X�g���N�^
PlayerBase::PlayerBase(GameObject* parent, std::string modelFilePath_, std::string name)
    :NormalObject(parent, modelFilePath_, name),

    ///////////////�L�����̕K�v�ȏ��///////////////////

    pRacket_(nullptr),
    pState_(new PlayerStateManager),

    ///////////////////�J����///////////////////////

    camVec_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
    camVec2_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
    nowLookNum_(ZERO)

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

    //�T�[�o�[�����p�x�C��
    if (GameManager::GetReferee()->GetServer() == this)
        ARGUMENT_INITIALIZE(transform_->rotate_, PLAYER_SERVE_ROTATION_ANGLE);

    //���邳�ő��
    //ModelManager::SetBrightness(hModel_, 1.0f);

    //���g�ɉe��`�悵�Ȃ��悤��
    ModelManager::SetMyShadowApply(hModel_, false);

    //�����ʒu�ݒ�
    ARGUMENT_INITIALIZE(initialPosition_, transform_->position_);

    ///////////////�A�j���[�V�����ݒ�///////////////////

    //�A�j���[�V����
    ModelManager::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, PLAYER_ANIM_SPEED);

    /////////////////�t�@�C���ǂݍ���Ńp�X���Ƃ̈ʒu�擾///////////////////

    //1�l�ڂ̃v���C���[�Ȃ�
    if (pState_->GetPlayerNum() == 0)
        SetData("Data/PathData/GameStartCamera/CamPos1.json");
    else
        SetData("Data/PathData/GameStartCamera/CamPos2.json");

    //�J�n
    hermiteMoveTable_[nowLookNum_]->Start();

    ///////////////���P�b�g����///////////////////

    ARGUMENT_INITIALIZE(pRacket_,Instantiate<Racket>(this));
}


//�X�V
void PlayerBase::ChildUpdate()
{
    //�X�V
    pState_->Update3D(this);

    //�J�����̏���
    CameraBehavior();
}

//�J�����̏���
void PlayerBase::CameraBehavior()
{
    //�X�^�[�g���Ă��Ȃ��̂Ȃ�(�X�^�[�g�J�n�O�̃J�������[�N������)
    if (!GameManager::GetReferee()->IsGameStart())
    {
        GameStartCamera();
        return;
    }

    //�J�����̋���(�T�[�u���V�[�u�̎��ƃ����[���̎��̃J�����𕪂���)
    if (GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_SERVE_RECEIVE)
    {
        ServeReceiveCameraBehavior();
        return;
    }

    vector<float> zPos; //Z�̈ʒu���i�[����p
    vector<float> xPos; //X�̈ʒu���i�[����p

    //�{�[�����擾
    Ball* pBall = GameManager::GetpBall();
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
        //�J�����̃x�N�g���ϊ�
        ARGUMENT_INITIALIZE(camVec_, (initialPosition_ - CAM_POS_NORMAL));
        ARGUMENT_INITIALIZE(camVec2_, (CAM_TAR_NORMAL - CAM_POS_NORMAL));

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
        //�J�����̃x�N�g���ϊ�(2�l�ڂ̓J�������t�Ȃ̂�X,Z���t�ɂ���)
        ARGUMENT_INITIALIZE(camVec_, (initialPosition_ - XMFLOAT3(-CAM_POS_NORMAL.x, CAM_POS_NORMAL.y, -CAM_POS_NORMAL.z)));
        ARGUMENT_INITIALIZE(camVec2_, (XMFLOAT3(-CAM_TAR_NORMAL.x, CAM_TAR_NORMAL.y, -CAM_TAR_NORMAL.z) - XMFLOAT3(-CAM_POS_NORMAL.x, CAM_POS_NORMAL.y, -CAM_POS_NORMAL.z)));

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

//�Q�[���X�^�[�g���̃J���� 
void PlayerBase::GameStartCamera()
{
    //1�l�ڂ̃v���C���[�Ȃ�
    if (pState_->GetPlayerNum() == 0)
    {
        Camera::SetPosition(hermiteMoveTable_[nowLookNum_]->Updata());
        Camera::SetTarget(VectorToFloat3(GetComponent<Transform>()->GetPosition() + CAM_TAR_ADD_VALUE));
    }
    else
    {
        Camera::SetPositionTwo(hermiteMoveTable_[nowLookNum_]->Updata());
        Camera::SetTargetTwo(VectorToFloat3(GetComponent<Transform>()->GetPosition() + CAM_TAR_ADD_VALUE));
    }

    //�������I������̂Ȃ�
    if (hermiteMoveTable_[nowLookNum_]->IsFinish())
    {
        nowLookNum_++;

        //�T�C�Y�I�[�o�[���Ă����Ȃ�
        if (hermiteMoveTable_.size() == nowLookNum_)
            ARGUMENT_INITIALIZE(nowLookNum_, ZERO);

        //�J�n
        hermiteMoveTable_[nowLookNum_]->ReStart();
    }
}


//�T�[�u���V�[�u���̃J�����̏���
void PlayerBase::ServeReceiveCameraBehavior()
{
    //1�l�ڂ̃v���C���[�Ȃ�
    if (pState_->GetPlayerNum() == 0)
    {
        ARGUMENT_INITIALIZE(camVec_, (initialPosition_ - XMFLOAT3(transform_->position_.x / 2, CAM_POS_SERVE_RECEIVE.y, CAM_POS_SERVE_RECEIVE.z)));
        XMFLOAT3 pos = Camera::GetPosition();
        XMFLOAT3 nextPos = { (transform_->position_.x - XMVectorGetX(camVec_)), (transform_->position_.y - XMVectorGetY(camVec_)), (transform_->position_.z - XMVectorGetZ(camVec_)) };
        nextPos = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&pos), XMLoadFloat3(&nextPos), 0.05f));
        Camera::SetPosition(nextPos);

        if (GameManager::GetReferee()->GetServer() == this)
            Camera::SetTarget(GameManager::GetReferee()->GetReceiverPosition());
        else
            Camera::SetTarget(GameManager::GetReferee()->GetServerPosition());
    }
    else
    {
        ARGUMENT_INITIALIZE(camVec_, (initialPosition_ - XMFLOAT3(transform_->position_.x / 2, CAM_POS_SERVE_RECEIVE.y, -CAM_POS_SERVE_RECEIVE.z)));
        XMFLOAT3 pos = Camera::GetPositionTwo();
        XMFLOAT3 nextPos = { (transform_->position_.x - XMVectorGetX(camVec_)), (transform_->position_.y - XMVectorGetY(camVec_)), (transform_->position_.z - XMVectorGetZ(camVec_)) };
        nextPos = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&pos), XMLoadFloat3(&nextPos), 0.05f));
        Camera::SetPositionTwo(nextPos);

        if (GameManager::GetReferee()->GetServer() == this)
            Camera::SetTargetTwo(GameManager::GetReferee()->GetReceiverPosition());
        else
            Camera::SetTargetTwo(GameManager::GetReferee()->GetServerPosition());
    }
        
}

//�f�[�^�Z�b�g
void PlayerBase::SetData(string posFileName)
{
    //�V�����ǉ�
    hermiteMoveTable_.push_back(std::make_unique<HermiteSplineMove>());

    //�ǂݍ���
    ifstream ifsPos(posFileName);
    json json_object_Pos;
    ifsPos >> json_object_Pos;

    //�e�l�擾
    for (auto it = json_object_Pos.begin(); it != json_object_Pos.end(); it++) {

        hermiteMoveTable_[hermiteMoveTable_.size() - 1]->AddPath(XMFLOAT3(json_object_Pos[it.key()]["Position"][0], json_object_Pos[it.key()]["Position"][1], json_object_Pos[it.key()]["Position"][2]), XMFLOAT3(50, ZERO, ZERO));
    }
}