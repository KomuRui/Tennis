#pragma once
#include "../../Engine/DirectX/Input.h"
#include "PlayerState.h"
#include "../../Engine/ResourceManager/Global.h"
#include "StandingState.h"
#include "ForehandingState.h"
#include "BackhandingState.h"
#include "ServingState.h"

//定義
class PlayerBase;

/// <summary>
/// Playerの状態を管理しているクラス
/// </summary>
class PlayerStateManager : public PlayerState
{
private:

	
	XMVECTOR front_; //キャラの前方向のベクトル       
	int hTime_;      //タイマーハンドル

	bool isRestorePosture_; //元の姿勢に戻すかどうか
	bool isHitMove_;		//打つ動きをしているか

	int buttonCode_; //打つ時のボタンコード格納用

public:

	//状態を示す変数
	static PlayerState* playerState_;

	//各状態変数
	static StandingState* playerStanding_;		 //立ってる
	static ForehandingState* playerForehanding_; //フォアハンド
	static BackhandingState* playerBackhanding_; //バックハンド
	static ServingState* playerServing_;         //サーブ

    //コンストラクタ
	PlayerStateManager();

	//2D用更新
	virtual void Update2D(PlayerBase* player)override;

	//3D用更新
	virtual void Update3D(PlayerBase* player)override;

	//入力によって状態変化する
	virtual void HandleInput(PlayerBase* player)override;

	//状態変化したとき一回だけ呼ばれる関数
	virtual void Enter(PlayerBase* player)override;

	//状態チェンジ用
	void ChangeState(PlayerState* change, PlayerBase* player);

	//元の姿勢に戻すかどうか設定
	void SetRestorePosture(bool flag) { isRestorePosture_ = flag; }

	//打つ動作かどうか設定
	void SetHitMove(bool flag) { isHitMove_ = flag; }

	//打つ動作をしているか取得
	bool IsHitMove() { return isHitMove_; }

	//前ベクトルを取得
	XMVECTOR GetFrontVec() { return front_; }

	//ボタンコードを取得
	int GetNowButtonCode() { return buttonCode_; }

	//ボタンコードをセット
	void SetNowButtonCode(int code) { buttonCode_ = code; }

};



