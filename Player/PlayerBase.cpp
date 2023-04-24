#include "PlayerBase.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/GameObject/Light.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../Engine/ResourceManager/Audio.h"
#include "../OtherObject/TitleScene/Racket.h"

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

    //その他
    pState_(new PlayerStateManager),

    ///////////////////カメラ///////////////////////

    camMat_(XMMatrixIdentity()),
    vCam_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
    camVec_(XMVectorSet(ZERO,ZERO,ZERO,ZERO))

{
}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void PlayerBase::ChildInitialize()
{
    ///////////////////初期化///////////////////////

    //状態
    ARGUMENT_INITIALIZE(PlayerStateManager::playerState_ ,PlayerStateManager::playerStanding_);

    ///////////////アニメーション設定///////////////////

    //アニメーション
    Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, PLAYER_ANIM_SPEED);

    ///////////////ラケット生成///////////////////

    ARGUMENT_INITIALIZE(pRacket_,Instantiate<Racket>(this));
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
}


//当たり判定
void PlayerBase::OnCollision(GameObject* pTarget)
{
}
