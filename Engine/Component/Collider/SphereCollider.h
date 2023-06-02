#pragma once
#include "Collider.h"


/// <summary>
/// 球体の当たり判定
/// </summary>
class SphereCollider : public Collider
{
	//Colliderクラスのprivateメンバにアクセスできるようにする
	friend class Collider;

public:

	//コンストラクタ（当たり判定の作成）
	SphereCollider();

	//セット関数
	void SetColliderPos(XMFLOAT3 pos) { center_ = pos; }

	//ゲット関数
	XMFLOAT3 GetColliderPos() { return center_; }

private:

	//接触判定
	//引数：target	相手の当たり判定
	//戻値：接触してればtrue
	bool IsHit(Collider* target) override;
};

