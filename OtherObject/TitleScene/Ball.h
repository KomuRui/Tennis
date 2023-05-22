#pragma once
#include "../../Base/NormalObject.h"
#include  "../../Engine/GameObject/PolyLine.h"
#include <map>

//放物線の計算
//https://juken-philo.com/hobutsuundo/

//ボールの状態
enum class BallStatus
{
	PURPOSE_MOVE, //目的地まで移動
	BOUND_MOVE,   //バウンド移動
};

/// <summary>
/// テニスボール
/// </summary>
class Ball : public NormalObject
{

	BallStatus ballStatus_;      //ボールの状態

	int hTime_;                  //タイマーハンドル
	int hEffect_;                //エフェクトハンドル
	int boundCount_;             //バウンドの回数
	float ratio_;			     //割合(始点から終点のどこの割合にいるか)
	float moveTime_;			 //始点から終点まで動く時間
	float firstAngle_;           //放物線の最初の角度
	bool isGoToBasePoint_;       //プレイヤーの基準点に向かうか

	XMVECTOR endPointDirection_; //終点までのベクトル
	XMVECTOR progressVector_;    //進行ベクトル

	XMFLOAT2 strength_;   //強さ(XとY方向の)
	XMFLOAT2 v0_;		  //初速度(XとY方向の)

	XMFLOAT3 startPoint_; //ボールの始点
	XMFLOAT3 endPoint_;   //ボールの終点

	PolyLine* pLine_; //ボールの軌跡描画用

public:

	//コンストラクタ
	Ball(GameObject* parent, std::string modelPath, std::string name);
	Ball(GameObject* parent);

	//デストラクタ
	~Ball() {};

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	//描画
	void ChildDraw() override;

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;
	
	//////////////////////////////////関数///////////////////////////////////////

	/// <summary>
	/// 目的地まで移動
	/// </summary>
	void MoveToPurpose();

	/// <summary>
	/// バウンド移動
	/// </summary>
	void BoundMove();

	/// <summary>
	/// リセット(始点終点すべて再設定)
	/// </summary>
	void Reset(float strengthX, float strengthY,float moveTime,bool isGotoPlayer,string basePpointName);

	/// <summary>
	/// 終点のポジションを取得
	/// </summary>
	/// <returns>終点のポジション</returns>
	XMFLOAT3 GetEndPosition() { return endPoint_; }

	/// <summary>
	/// ボールの軌跡色を設定
	/// </summary>
	/// <param name="color">設定したい軌跡色</param>
	void SetBallLineColor(XMFLOAT4 color) { pLine_->SetColor(color); }

	/// <summary>
	/// プレイヤーの基準点に向かっているか
	/// </summary>
	bool isGoToPlayerBasePoint() { return isGoToBasePoint_; }

	/// <summary>
	/// ボールの状態を取得
	/// </summary>
	/// <returns>ボールの状態</returns>
	BallStatus GetBallStatus() { return ballStatus_; }
};

