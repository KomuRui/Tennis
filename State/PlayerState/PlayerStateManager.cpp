#include "PlayerStateManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include <math.h>

//各static変数の初期化
StandingState* PlayerStateManager::playerStanding_ = new StandingState;
ForehandingState* PlayerStateManager::playerForehanding_ = new ForehandingState;
BackhandingState* PlayerStateManager::playerBackhanding_ = new BackhandingState;
ServingState* PlayerStateManager::playerServing_ = new ServingState;
PlayerState* PlayerStateManager::playerState_ = playerStanding_;

////定数
namespace
{
    const float RUN_SPEED = 1.5f;                 //走っているときのキャラのスピード
    const float PLAYER_WALK_ANIM_SPEED = 1.0f;    //アニメーションの再生速度
    const float ANIM_RUN_SPEED = 2.0f;            //アニメーションの再生速度(走ってるとき)
}

//コンストラクタ
PlayerStateManager::PlayerStateManager():front_(STRAIGHT_VECTOR)
{
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
    if (playerState_ != PlayerStateManager::playerStanding_)
    {
        //動いたのでアニメーション
        Model::SetAnimFlag(player->GetModelNum(), true);
        Model::SetAnimFlag(player->GetRacket()->GetModelNum(), true);

        //現在の状態の更新を呼ぶ
        playerState_->Update3D(player);
        return;
    }

    //Lスティックの傾きを取得
    float PadLx = Input::GetPadStickL().x;
    float PadLy = Input::GetPadStickL().y;

    //少しでも動いたのなら
    if (PadLx != ZERO || PadLy != ZERO)
    {
        //動いたのでアニメーション
        Model::SetAnimFlag(player->GetModelNum(), true);
        Model::SetAnimFlag(player->GetRacket()->GetModelNum(), true);

        //回転行列
        XMMATRIX rotateX, rotateY, rotateZ;
        rotateX = XMMatrixRotationX(XMConvertToRadians(ZERO));
        rotateY = XMMatrixRotationY(XMConvertToRadians(XMConvertToDegrees(atan2(-PadLx, -PadLy))));
        rotateZ = XMMatrixRotationZ(XMConvertToRadians(ZERO));
        XMMATRIX matRotate = rotateZ * rotateX * rotateY;

        //Playerの移動
        player->SetPosition(Float3Add(player->GetPosition(), VectorToFloat3(XMVector3TransformCoord(front_ / 10.0f, matRotate))));
    }
    //動いていないのならアニメーションを止める
    else
    {
        Model::SetAnimFlag(player->GetModelNum(), false);
        Model::SetAnimFlag(player->GetRacket()->GetModelNum(), false);
    }

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
    PlayerStateManager::playerState_ = change;
    PlayerStateManager::playerState_->Enter(player);
}