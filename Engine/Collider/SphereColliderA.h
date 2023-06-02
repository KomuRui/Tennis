//#pragma once
//#include "ColliderA.h"
//
//
////-----------------------------------------------------------
////球体の当たり判定
////-----------------------------------------------------------
//class SphereColliderA : public ColliderA
//{
//	//Colliderクラスのprivateメンバにアクセスできるようにする
//	friend class ColliderA;
//
//public:
//	//コンストラクタ（当たり判定の作成）
//	//引数：basePos	当たり判定の中心位置（ゲームオブジェクトの原点から見た位置）
//	//引数：radius	当たり判定のサイズ（半径）
//	SphereColliderA(XMFLOAT3 center, float radius, bool rotateflag = false);
//
//	//セット関数
//	void SetColliderPos(XMFLOAT3 pos) { center_ = pos; }
//
//	//ゲット関数
//	XMFLOAT3 GetColliderPos() { return center_; }
//
//private:
//	//接触判定
//	//引数：target	相手の当たり判定
//	//戻値：接触してればtrue
//	bool IsHit(ColliderA* target) override;
//};
//
