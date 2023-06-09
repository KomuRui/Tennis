#pragma once
#include "Score.h"
#include "../../Player/PlayerBase.h"

//試合状態
enum class GameStatus
{
	NOW_RALLY,         //ラリー中
	NOW_SERVE_RECEIVE  //サーブレシーブ
};

/// <summary>
/// 審判
/// </summary>
class Referee
{
	Score* score_;	       //スコア
	GameStatus status_;    //試合状態

	PlayerBase* server_;   //サーバー
	PlayerBase* receiver_; //レシーバー

	bool isPlayer1Server_; //Player1がサーバーかどうか

public:

	//コンストラクタ
	Referee();
	
	//デストラクタ
	~Referee() {};

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 試合状態を取得
	/// </summary>
	/// <returns>試合状態</returns>
	GameStatus GetGameStatus() { return status_; }

	/// <summary>
	/// 試合状態を設定
	/// </summary>
	/// <param name="s">設定したい試合状態</param>
	void SetGameStatus(GameStatus s) { status_ = s; }

	/// <summary>
	/// プレイヤー1がサーバーかどうか設定
	/// </summary>
	/// <param name="flag"></param>
	void SetPlayer1Server(bool flag) { isPlayer1Server_ = flag; }

	/// <summary>
	/// プレイヤー1がサーバーかどうか
	/// </summary>
	/// <returns>trueならサーバー</returns>
	bool IsPlayer1Server() { return isPlayer1Server_; }

	/// <summary>
	/// プレイヤー2がサーバーかどうか
	/// </summary>
	/// <returns>trueならサーバー</returns>
	bool IsPlayer2Server() { return !isPlayer1Server_; }

	/// <summary>
	/// サーバーのプレイヤーを取得
	/// </summary>
	/// <returns>サーバーのプレイヤー</returns>
	PlayerBase* GetServer() { return server_; }

	/// <summary>
	/// レシーバーのプレイヤーを取得
	/// </summary>
	/// <returns>レシーバーのプレイヤー</returns>
	PlayerBase* GetReceiver() { return receiver_; }

	/// <summary>
	/// サーバーをセット
	/// </summary>
	/// <param name="p">プレイヤー</param>
	void SetServer(PlayerBase* p) { server_ = p; }
	
	/// <summary>
	/// レシーバーをセット
	/// </summary>
	/// <param name="p">プレイヤー</param>
	void SetReceiver(PlayerBase* p) { receiver_ = p; }
};

