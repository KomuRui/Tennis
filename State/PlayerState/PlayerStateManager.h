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

	XMVECTOR front_;			//キャラの前方向のベクトル       
	string hChargeEffectName_;  //チャージエフェクト番号

	bool isRestorePosture_;     //元の姿勢に戻すかどうか
	bool isHitMove_;		    //打つ動きをしているか
							    
	int hTime_;				    //タイマーハンドル
	int buttonCode_;		    //打つ時のボタンコード格納用
	int playerNum_;             //プレイヤー番号
	float chargeTime_;          //チャージ時間             

public:

	//状態を示す変数
	PlayerState* playerState_;

	//各状態変数
    StandingState* playerStanding_;		  //立ってる
    ForehandingState* playerForehanding_; //フォアハンド
    BackhandingState* playerBackhanding_; //バックハンド
    ServingState* playerServing_;         //サーブ

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

	/// <summary>
	/// サーブの時の移動
	/// </summary>
	void ServeMove(PlayerBase* player,float padLx, float padLy);

	///////////////////////////////////セッター・ゲッター///////////////////////////////////////

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

	//エフェクト番号取得
	string GetChargeEffectNum() { return hChargeEffectName_; }

	//エフェクト番号セット
	void SetChargeEffectNum(string s) { hChargeEffectName_ = s; }

	//チャージ時間を取得
	float GetChargeTime() { return chargeTime_; }

	//チャージ時間を設定
	void SetChargeTime(float t) { chargeTime_ = t; }

	//プレイヤー番号を取得
	int GetPlayerNum() { return playerNum_; }

	//プレイヤー番号を設定
	void SetPlayerNum(int num) { 

		playerNum_ = num;
		if (playerNum_ == 1) hChargeEffectName_ = "chargeEffect1";
	}
};



