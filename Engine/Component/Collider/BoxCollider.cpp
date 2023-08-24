#include "BoxCollider.h"
#include "SphereCollider.h"
#include "../../ResourceManager/ModelManager.h"


//コンストラクタ（当たり判定の作成）
//引数：basePos	当たり判定の中心位置（ゲームオブジェクトの原点から見た位置）
//引数：size	当たり判定のサイズ
BoxCollider::BoxCollider()
{
	type_ = COLLIDER_BOX;

	//リリース時は判定枠は表示しない
#ifdef _DEBUG
	//テスト表示用判定枠
	hDebugModel_ = ModelManager::Load("DebugCollision/boxCollider.fbx");
#endif
}

//接触判定
//引数：target	相手の当たり判定
//戻値：接触してればtrue
bool BoxCollider::IsHit(Collider* target)
{
	if (target->type_ == COLLIDER_BOX)
		return IsHitBoxVsBox((BoxCollider*)target, this);
	else
		return IsHitBoxVsCircle(this, (SphereCollider*)target);
}

//オブジェクトA,Bの距離を計算
XMVECTOR BoxCollider::calcDistance(XMFLOAT3 posA, XMFLOAT3 posB)
{
	XMVECTOR distance = XMLoadFloat3(&posB) - XMLoadFloat3(&posA);
	return distance;
}

//分離軸に投影された軸成分から投影線分長を算出
float BoxCollider::prjLine(XMVECTOR* sep, XMVECTOR* e1, XMVECTOR* e2, XMVECTOR* e3)
{
	XMVECTOR sp = XMVectorZero();
	sp = XMVector3Normalize(*sep);
	float r1 = abs(XMVectorGetX(XMVector3Dot(sp, *e1)));
	float r2 = abs(XMVectorGetX(XMVector3Dot(sp, *e2)));
	float r3 = e3 ? abs(XMVectorGetX(XMVector3Dot(sp, *e3))) : 0;

	return r1 + r2 + r3;
}

//各軸ベクトルを回転
void BoxCollider::CalcAxisVec()
{
	XMVECTOR rotateQua = XMQuaternionRotationMatrix(parent->GetComponent<Transform>()->GetWorldRotateMatrix());
	OBB_X = XMVector3Rotate(OBB_X, rotateQua);
	OBB_Y = XMVector3Rotate(OBB_Y, rotateQua);
	OBB_Z = XMVector3Rotate(OBB_Z, rotateQua);
}