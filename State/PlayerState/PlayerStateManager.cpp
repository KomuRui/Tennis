#include "PlayerStateManager.h"
#include "../../Engine/System.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../OtherObject/TitleScene/Ball.h"
#include "../../OtherObject/TitleScene/Referee.h"
#include <math.h>


////定数
namespace
{
    static const XMFLOAT3 RACKET_END_ROTATION_ANGLE = { 0,-185,0 }; //ラケットの終了角度
    static const float RUN_SPEED = 1.5f;                            //走っているときのキャラのスピード
    static const float PLAYER_WALK_ANIM_SPEED = 1.0f;               //アニメーションの再生速度
    static const float ANIM_RUN_SPEED = 2.0f;                       //アニメーションの再生速度(走ってるとき)
    static const float POSSTURE_RESTORE_TIME = 5.0f;                //元の姿勢に戻す時間
}

//コンストラクタ
PlayerStateManager::PlayerStateManager():front_(STRAIGHT_VECTOR),hTime_(Time::Add()), 
    isRestorePosture_(false), isHitMove_(false),buttonCode_(XINPUT_GAMEPAD_A), hChargeEffectName_("chargeEffect"), chargeTime_(ZERO), playerNum_(ZERO)
{
    playerStanding_ = new StandingState;
    playerForehanding_ = new ForehandingState;
    playerBackhanding_ = new BackhandingState;
    playerServing_ = new ServingState;
    playerState_ = playerStanding_;
}

//更新
void PlayerStateManager::Update2D(PlayerBase* player)
{
	//現在の状態の更新を呼ぶ
	playerState_->Update2D(player);
}

//3D用更新
void PlayerStateManager::Update3D(PlayerBase* player)
{

    //立っている状態じゃないのなら
    if (playerState_ != playerStanding_)
    {
        //タイマー初期化
        Time::Reset(hTime_);
        Time::Lock(hTime_);
    }

    //元の姿勢に戻すのなら
    if (isRestorePosture_)
    {
        //ロックされているのなら解除
        if (Time::isLock(hTime_))Time::UnLock(hTime_);

        //割合を求める
        float ratio = Easing::OutQuart(Time::GetTimef(hTime_) / POSSTURE_RESTORE_TIME);

        //各角度を求める
        player->GetRacket()->GetComponent<Transform>()->SetRotate(VectorToFloat3(XMVectorLerp(XMLoadFloat3(new XMFLOAT3(player->GetRacket()->GetComponent<Transform>()->GetRotate())), XMLoadFloat3(&RACKET_END_ROTATION_ANGLE), ratio)));
        
        //もし回転が最後まで終わったのなら
        if (ratio >= 1)
        {
            //戻ったに設定
            ARGUMENT_INITIALIZE(isRestorePosture_, false);

            //タイマー初期化
            Time::Reset(hTime_);
            Time::Lock(hTime_);
        }
    }

    //Lスティックの傾きを取得
    float PadLx = Input::GetPadStickL(playerNum_).x;
    float PadLy = Input::GetPadStickL(playerNum_).y;

    //2人目のプレイヤーなら反転させる
    if (playerNum_ == 1)
    {
        PadLx *= -1;
        PadLy *= -1;
    }

    //サーブ状態かつサーバーなら
    if (GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_SERVE_RECEIVE &&
       (GameManager::GetReferee()->IsServer(player)))
    {
        //サーブの時の移動処理
        ServeMove(player, PadLx, PadLy);

        //現在の状態の更新を呼ぶ
        playerState_->Update3D(player);

        return;
    }
    
    //移動
    Move(player, PadLx, PadLy);

    //現在の状態の更新を呼ぶ
    playerState_->Update3D(player);
}

//入力によって状態変化する
void PlayerStateManager::HandleInput(PlayerBase* player)
{
}

//状態変化したとき一回だけ呼ばれる関数
void PlayerStateManager::Enter(PlayerBase* player)
{
}

//状態チェンジ用
void PlayerStateManager::ChangeState(PlayerState* change, PlayerBase* player)
{
    playerState_ = change;
    playerState_->Enter(player);
}

/// <summary>
/// 移動
/// </summary>
void PlayerStateManager::Move(PlayerBase* player, float padLx, float padLy)
{
    //少しでも動いたのなら
    if (padLx != ZERO || padLy != ZERO)
    {
        //動いたのでアニメーション
        ModelManager::SetAnimFlag(player->GetModelNum(), true);

        //回転行列
        XMMATRIX rotateX, rotateY, rotateZ;
        rotateX = XMMatrixRotationX(XMConvertToRadians(ZERO));
        rotateY = XMMatrixRotationY(XMConvertToRadians(XMConvertToDegrees(atan2(-padLx, -padLy))));
        rotateZ = XMMatrixRotationZ(XMConvertToRadians(ZERO));
        XMMATRIX matRotate = rotateZ * rotateX * rotateY;

        //Playerの移動
        //フォアかバックハンド状態なら
        if (playerState_ == PlayerStateManager::playerBackhanding_ || playerState_ == PlayerStateManager::playerForehanding_)
        {
            //アニメーション止める
            ModelManager::SetAnimFlag(player->GetModelNum(), false);

            //ボールのポインタ
            Ball* pBall = GameManager::GetpBall();

            //各ポジションを記憶用
            float ballEndX = ZERO;
            float playerX = ZERO;

            //nullptrじゃないのなら
            if (pBall != nullptr)
            {
                ballEndX = pBall->GetSpecifyPosZBallPosition(player->GetComponent<Transform>()->GetPosition().z).x;
                playerX = player->GetComponent<Transform>()->GetPosition().x;
            }

            //割合を取得
            float dis = abs(playerX - ballEndX);

            //距離が定数以下なら
            if (dis <= 3.0f)
            {
                player->GetComponent<Transform>()->SetPosition(Float3Add(player->GetComponent<Transform>()->GetPosition(), VectorToFloat3(XMVector3TransformCoord(((front_ / 10.0f) * RUN_SPEED) * (dis / 3.0f * 0.5f), matRotate))));
            }
            else
            {
                player->GetComponent<Transform>()->SetPosition(Float3Add(player->GetComponent<Transform>()->GetPosition(), VectorToFloat3(XMVector3TransformCoord(((front_ / 10.0f) * RUN_SPEED) * 0.5f, matRotate))));
            }
        }
        //サーブ状態じゃないのなら
        else if (playerState_ != PlayerStateManager::playerServing_)
            player->GetComponent<Transform>()->SetPosition(Float3Add(player->GetComponent<Transform>()->GetPosition(), VectorToFloat3(XMVector3TransformCoord((front_ / 10.0f) * RUN_SPEED, matRotate))));

        //回転
        player->GetComponent<Transform>()->SetRotateY(XMConvertToDegrees(atan2(-padLx, -padLy)));
    }
    //動いていないのならアニメーションを止める
    else
        ModelManager::SetAnimFlag(player->GetModelNum(), false);
}

/// <summary>
/// サーブの時の移動
/// </summary>
void PlayerStateManager::ServeMove(PlayerBase* player, float padLx, float padLy)
{
    //構えていないのなら
    if (!playerServing_->IsCharge())
    {
        //ボール位置を修正する
        XMFLOAT3 ballPos = ModelManager::GetBonePosition(player->GetModelNum(), "Left");
        GameManager::GetpBall()->GetComponent<Transform>()->SetPosition(ballPos);
    }

    //少しでも動いてるかつ構えていなければ
    if ((padLx != ZERO || padLy != ZERO) && !playerServing_->IsCharge())
    {
        //アニメーションはしない
        ModelManager::SetAnimFlag(player->GetModelNum(), false);

        //回転行列
        XMMATRIX rotateX, rotateY, rotateZ;
        rotateX = XMMatrixRotationX(XMConvertToRadians(ZERO));
        rotateY = XMMatrixRotationY(XMConvertToRadians(XMConvertToDegrees(atan2(-padLx,0))));
        rotateZ = XMMatrixRotationZ(XMConvertToRadians(ZERO));
        XMMATRIX matRotate = rotateZ * rotateX * rotateY;

        //移動
        XMFLOAT3 moveValue = VectorToFloat3(XMVector3TransformCoord(((front_ / 10.0f) * RUN_SPEED) * 0.5f, matRotate));
        ARGUMENT_INITIALIZE(moveValue.z, ZERO);
        player->GetComponent<Transform>()->SetPosition(Float3Add(player->GetComponent<Transform>()->GetPosition(), moveValue));
        player->GetComponent<Transform>()->SetPositionX(Clamp<float>(player->GetComponent<Transform>()->GetPosition().x, 0, -4));
    }
}