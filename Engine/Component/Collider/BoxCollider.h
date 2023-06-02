#pragma once
#include "Collider.h"

/// <summary>
/// 箱型コライダー
/// </summary>
class BoxCollider : public Collider
{
	//Colliderクラスのprivateメンバにアクセスできるようにする
	friend class Collider;

public:

	//コンストラクタ（当たり判定の作成）
	BoxCollider();

private:

	//接触判定
	//引数：target	相手の当たり判定
	//戻値：接触してればtrue
	bool IsHit(Collider* target) override;
};

