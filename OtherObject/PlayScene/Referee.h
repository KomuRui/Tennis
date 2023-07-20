#pragma once
#include "Score.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/PlayScene/TennisCourt.h"

//試合状態
enum class GameStatus
{
	NOW_RALLY,         //ラリー中
	NOW_SERVE_RECEIVE  //サーブレシーブ
};

//各サイド
enum class Side {
	DEUCE_SIDE,        //デュースサイド
	AD_SIDE            //アドサイド
};

/// <summary>
/// 審判
/// </summary>
class Referee
{
	std::unique_ptr<Score> score_; //スコア
	GameStatus status_;            //試合状態
	Side side_;                    //サイド状況

	TennisCourtType tennisCourtType_; //テニスコートタイプ

	int numGameFirstToGet_;//何ゲーム先取か
	int numSetFirstToGet_; //何セット先取か

	PlayerBase* server_;   //サーバー
	PlayerBase* receiver_; //レシーバー

	//サーバーの動ける範囲
	map<pair<TennisCourtName, Side>, pair<float, float>> serverMoveRange_;

	//サーバー・レシーバーの初期位置
	map<pair<TennisCourtName, Side>, pair<XMFLOAT3,XMFLOAT3>> serverInitialPosition_;
	map<pair<TennisCourtName, Side>, pair<XMFLOAT3,XMFLOAT3>> receiverInitialPosition_;

public:

	//コンストラクタ
	Referee();
	
	//デストラクタ
	~Referee() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ポイント終了時
	/// </summary>
	/// <param name="n">点数を失うテニスコートの名前</param>
	void EndPoint(TennisCourtName n);

	/// <summary>
	/// どちらかがポイント取得時
	/// </summary>
	void GetPoint();

	/// <summary>
	/// どちらかがゲーム取得時
	/// </summary>
	void GetGame();

	/// <summary>
	/// 試合終了時
	/// </summary>
	void GameMatch();

	/// <summary>
	/// サイドチェンジ
	/// </summary>
	void ChangeSide();

	/// <summary>
	/// サイドリセット
	/// </summary>
	void SideReset() { side_ = Side::DEUCE_SIDE; }

	/// <summary>
	/// スコア生成
	/// </summary>
	void ScoreInstantiate() { score_ = std::make_unique<Score>(); }

	/////////////////////////////ゲッター・セッター////////////////////////////////////

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

	/// <summary>
	/// サイドを取得
	/// </summary>
	/// <returns>サイド</returns>
	Side GetSide() { return side_; }

	/// <summary>
	/// サーバーの動ける範囲を取得
	/// </summary>
	/// <returns>X軸での動ける最小値と最大値</returns>
	pair<float, float> GetServerMoveRange() { return serverMoveRange_[{server_->GetTennisCourtName(), side_}]; }

	/// <summary>
	/// レシーバーのポジションを取得
	/// </summary>
	/// <returns>レシーバーのポジション</returns>
	XMFLOAT3 GetReceiverPosition() { return receiverInitialPosition_[{receiver_->GetTennisCourtName(), side_}].first; }

	/// <summary>
	/// サーバーのポジションを取得
	/// </summary>
	/// <returns>サーバーのポジション</returns>
	XMFLOAT3 GetServerPosition() { return serverInitialPosition_[{server_->GetTennisCourtName(), side_}].first; }

	/// <summary>
	/// 何ゲーム先取か取得
	/// </summary>
	/// <returns>何ゲーム先取か</returns>
	int GetnumGameFirstToGet() { return numGameFirstToGet_; }

	/// <summary>
	/// 何ゲーム先取か設定
	/// </summary>
	/// <param name="num">設定したいゲーム数</param>
	void SetnumGameFirstToGet(int num) { numGameFirstToGet_ = num; }

	/// <summary>
	/// 何セット先取か取得
	/// </summary>
	/// <returns>何セット先取か</returns>
	int GetnumSetFirstToGet() { return numSetFirstToGet_; }

	/// <summary>
	/// 何セット先取か設定
	/// </summary>
	/// <param name="num">設定したいセット数</param>
	void SetnumSetFirstToGet(int num) { numSetFirstToGet_ = num; }

	/// <summary>
	/// テニスコートタイプ取得
	/// </summary>
	/// <returns>テニスコートタイプ</returns>
	TennisCourtType GetTennisCourtType() { return tennisCourtType_; }

	/// <summary>
	/// テニスコートタイプ設定
	/// </summary>
	/// <param name="num">設定したいテニスコートタイプ</param>
	void SetTennisCourtType(TennisCourtType type) { tennisCourtType_ = type; }
};

