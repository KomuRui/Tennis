#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// テニスボール
/// </summary>
class Ball : public NormalObject
{
	int hTime_;                  //タイマーハンドル
	float ratio;			     //割合(始点から終点のどこの割合にいるか)
	float upStrength_;			 //上方向の強さ
	float moveTime_;			 //始点から終点まで動く時間
	float v0_;					 //初速度
	XMVECTOR endPointDirection_; //終点までのベクトル

	XMFLOAT3 startPoint_; //ボールの始点
	XMFLOAT3 endPoint_;   //ボールの終点

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
	
	//////////////////////////////////関数///////////////////////////////////////

	/// <summary>
	/// リセット(始点終点すべて再設定)
	/// </summary>
	void Reset();

};

