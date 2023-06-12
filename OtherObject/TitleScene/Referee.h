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
	/// プレイヤーがサーバーかどうか
	/// </summary>
	/// <returns>trueならサーバー</returns>
	bool IsServer(PlayerBase* p) { return (server_ == p); }

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

