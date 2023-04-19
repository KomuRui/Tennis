#include "PlayerStateManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/GUI/ImGuiSet.h"

//各static変数の初期化
StandingState* PlayerStateManager::playerStanding_ = new StandingState;
PlayerState* PlayerStateManager::playerState_ = playerStanding_;

////定数
namespace
{
    const float RUN_SPEED = 1.5f;                 // GetPrivateProfilefloat("PLAYER", "RunSpeed", "0.02", ".\\/Parameter/Player/PlayerParameter.ini");//走っているときのキャラのスピード
    const float PLAYER_WALK_ANIM_SPEED = 1.0f;    //アニメーションの再生速度
    const float ANIM_RUN_SPEED = 2.0f;            //アニメーションの再生速度(走ってるとき)
}

//コンストラクタ
PlayerStateManager::PlayerStateManager():front_(XMVectorSet(0, 0, 1.0f, 0))
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