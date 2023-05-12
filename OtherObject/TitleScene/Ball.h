#pragma once
#include "../../Base/NormalObject.h"
#include  "../../Engine/GameObject/PolyLine.h"

/// <summary>
/// テニスボール
/// </summary>
class Ball : public NormalObject
{
	int hTime_;                  //タイマーハンドル
	int hEffect_;                //エフェクトハンドル
	float ratio;			     //割合(始点から終点のどこの割合にいるか)
	float moveTime_;			 //始点から終点まで動く時間
	bool flag;
	XMVECTOR endPointDirection_; //終点までのベクトル

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
	
	//////////////////////////////////関数///////////////////////////////////////

	/// <summary>
	/// リセット(始点終点すべて再設定)
	/// </summary>
	void Reset();

};

