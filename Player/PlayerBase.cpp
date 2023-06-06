#include "PlayerBase.h"
#include "../Engine/System.h"
#include "../OtherObject/TitleScene/Racket.h"
#include "../OtherObject/TitleScene/Ball.h"

////定数
namespace
{
    ///////////////キャラの必要な情報///////////////////

    static const float PLAYER_ANIM_SPEED = 2.0f;   //アニメーションの再生速度
    static const int ANIM_START_FRAME = 1;         //アニメーションの開始フレーム
    static const int ANIM_END_FRAME = 60;		   //アニメーションの終了フレーム
}

//コンストラクタ
PlayerBase::PlayerBase(GameObject* parent, std::string modelFilePath_, std::string name)
    :NormalObject(parent, modelFilePath_, name),

    ///////////////キャラの必要な情報///////////////////

    pRacket_(nullptr),
    pState_(new PlayerStateManager),

    ///////////////////カメラ///////////////////////

    camVec_(XMVectorSet(ZERO,ZERO,ZERO,ZERO))

{
}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void PlayerBase::ChildInitialize()
{
    ///////////////////初期化///////////////////////

    //状態
    ARGUMENT_INITIALIZE(pState_->playerState_ , pState_->playerStanding_);
    pState_->SetPlayerNum(GameManager::SetPlayer(this));

    //影
    SetShadow(true);

    ///////////////アニメーション設定///////////////////

    //アニメーション
    ModelManager::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, PLAYER_ANIM_SPEED);

    ///////////////ラケット生成///////////////////

    ARGUMENT_INITIALIZE(pRacket_,Instantiate<Racket>(this));

    ////////////////////カメラ//////////////////////

    //1人目のプレイヤーなら
    if (pState_->GetPlayerNum() == 0)
    {
        ARGUMENT_INITIALIZE(camVec_, (transform_->position_ - Camera::GetPosition()));
    }
    else
        ARGUMENT_INITIALIZE(camVec_, (transform_->position_ - Camera::GetPositionTwo()));
    
}


//更新
void PlayerBase::ChildUpdate()
{
    //更新
    pState_->Update3D(this);

    //カメラの挙動
    CameraBehavior();
}

//カメラの処理
void PlayerBase::CameraBehavior()
{
    //Zの位置を格納する用
    vector<float> zPos;

    //ボールを取得
    Ball* pBall = ((Ball*)FindObject("Ball"));
    if (pBall)
        zPos.push_back(pBall->GetComponent<Transform>()->GetPosition().z);

    //自分以外のプレイヤーを取得
    PlayerBase* pPlayer = GameManager::GetNotMyPlayer(this);
    if (pPlayer)
        zPos.push_back(pPlayer->GetComponent<Transform>()->GetPosition().z);

    //自分自身も格納
    zPos.push_back(transform_->position_.z);

    //最小値最大値を取得
    pair<vector<float>::iterator, vector<float>::iterator> minmax;
    minmax = minmax_element(zPos.begin(), zPos.end());
    float MaxZ = *minmax.second;
    float MinZ = *minmax.first;

    float sum = abs(MaxZ + MinZ);
   
    //1人目のプレイヤーなら
    if (pState_->GetPlayerNum() == 0)
    {
        XMFLOAT3 pos = Camera::GetPosition();
        XMFLOAT3 tar = Camera::GetTarget();
        Camera::SetPosition(XMFLOAT3(pos.x,( transform_->position_.y - XMVectorGetY(camVec_)) * 1 + (sum * 0.2), (transform_->position_.z -  XMVectorGetZ(camVec_)) * 1 + (sum * 0.2)));
        Camera::SetTarget(XMFLOAT3(tar.x, tar.y,0));
    }
    //2人目のプレイヤーなら
    else
    {
        XMFLOAT3 pos = Camera::GetPositionTwo();
        XMFLOAT3 tar = Camera::GetTargetTwo();
        Camera::SetPositionTwo(XMFLOAT3(pos.x, (transform_->position_.y - XMVectorGetY(camVec_)) * 1 + (sum * 0.2), (transform_->position_.z - XMVectorGetZ(camVec_)) * 1 + (-sum * 0.2)));
        Camera::SetTargetTwo(XMFLOAT3(tar.x, tar.y, 0));
    }
}

