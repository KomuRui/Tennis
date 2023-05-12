#pragma once
#include "../../Base/NormalObject.h"
#include  "../../Engine/GameObject/PolyLine.h"

/// <summary>
/// テニスボール
/// </summary>
class Ball : public NormalObject
{
	int hTime_;                  //タイマーハンドル
	float ratio;			     //割合(始点から終点のどこの割合にいるか)
	float strengthY_;			 //上方向の強さY
	float strengthX_;			 //上方向の強さX
	float moveTime_;			 //始点から終点まで動く時間
	float vY0_;					 //初速度Y
	float vX0_;					 //初速度X
	XMVECTOR endPointDirection_; //終点までのベクトル

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
	
	//////////////////////////////////関数///////////////////////////////////////

	/// <summary>
	/// リセット(始点終点すべて再設定)
	/// </summary>
	void Reset();

};

