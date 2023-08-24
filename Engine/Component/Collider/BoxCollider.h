#pragma once
#include "Collider.h"

/// <summary>
/// 箱型コライダー
/// </summary>
class BoxCollider : public Collider
{
	//Colliderクラスのprivateメンバにアクセスできるようにする
	friend class Collider;

	//方向ベクトル
	XMVECTOR nX;
	XMVECTOR nY;
	XMVECTOR nZ;

	//各軸方向の長さ
	XMVECTOR OBB_X;
	XMVECTOR OBB_Y;
	XMVECTOR OBB_Z;

public:

	//コンストラクタ（当たり判定の作成）
	BoxCollider();

	//オブジェクトA,Bの距離を計算
	XMVECTOR calcDistance(XMFLOAT3 posA, XMFLOAT3 posB);

	//分離軸に投影された軸成分から投影線分長を算出
	//sep : 分離軸
	//e1  : 軸1
	//e2  : 軸2
	//e3  : 軸3(軸3は割愛できる場合がある)
	float prjLine(XMVECTOR* sep, XMVECTOR* e1, XMVECTOR* e2, XMVECTOR* e3 = nullptr);

	//各軸ベクトルを回転
	void CalcAxisVec();

private:

	//接触判定
	//引数：target	相手の当たり判定
	//戻値：接触してればtrue
	bool IsHit(Collider* target) override;
};

