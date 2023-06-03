#include "BoxCollider.h"
#include "SphereCollider.h"
#include "../../GameObject/GameObject.h"
#include "../../ResourceManager/ModelManager.h"

//コンストラクタ
Collider::Collider()
{
}

//デストラクタ
Collider::~Collider()
{
}

//描画
void Collider::Draw()
{
	//フレームだけ描画にする
	Direct3D::SetShader(Direct3D::SHADER_UNLIT);

	//位置格納用
	XMFLOAT3 position = parent->GetComponent<Transform>()->GetWorldPosition();

	//コライダーのトランスフォーム
	Transform transform;
	transform.position_ = XMFLOAT3(position.x + center_.x, position.y + center_.y, position.z + center_.z);
	transform.scale_ = size_;
	transform.rotate_ = parent->GetComponent<Transform>()->GetWorldRotate();

	//描画
	ModelManager::SetShederType(hDebugModel_, Direct3D::SHADER_UNLIT);
	ModelManager::SetTransform(hDebugModel_, &transform);
	ModelManager::Draw(hDebugModel_);

	//元に戻す
	Direct3D::SetShader(Direct3D::SHADER_3D);
}

//衝突判定
//引数：pTarget	衝突してるか調べる相手
void Collider::Collision(GameObject* pTarget)
{
	//自分同士の当たり判定はしない
	if (pTarget == nullptr || this->parent == pTarget)
	{
		return;
	}

	//リストを取得
	list<Collider*> my = parent->GetComponentList<Collider>();
	list<Collider*> tar = pTarget->GetComponentList<Collider>();

	//自分とpTargetのコリジョン情報を使って当たり判定
	//1つのオブジェクトが複数のコリジョン情報を持ってる場合もあるので二重ループ
	for (auto i = my.begin(); i != my.end(); i++)
	{
		for (auto j = tar.begin(); j != tar.end(); j++)
		{
			//当たったなら
			if ((*i)->IsHit(*j))
			{
				//当たった
				(*parent.*OnCollision)(pTarget);
			}
		}
	}

	//子供がいないなら終わり
	if (pTarget->GetChildList()->empty())
		return;

	//子供も当たり判定
	for (auto i = pTarget->GetChildList()->begin(); i != pTarget->GetChildList()->end(); i++)
	{
		//コライダーがあるのならば
		if((*i)->GetComponent<Collider>())
			Collision((*i));
	}
}

//箱型同士の衝突判定
//引数：boxA	１つ目の箱型判定
//引数：boxB	２つ目の箱型判定
//戻値：接触していればtrue
bool Collider::IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB)
{

	XMFLOAT3 boxPosA = Float3Add(boxA->parent->GetComponent<Transform>()->GetWorldPosition(), boxA->center_);
	XMFLOAT3 boxPosB = Float3Add(boxB->parent->GetComponent<Transform>()->GetWorldPosition(), boxB->center_);


	if ((boxPosA.x + boxA->size_.x / 2) > (boxPosB.x - boxB->size_.x / 2) &&
		(boxPosA.x - boxA->size_.x / 2) < (boxPosB.x + boxB->size_.x / 2) &&
		(boxPosA.y + boxA->size_.y / 2) > (boxPosB.y - boxB->size_.y / 2) &&
		(boxPosA.y - boxA->size_.y / 2) < (boxPosB.y + boxB->size_.y / 2) &&
		(boxPosA.z + boxA->size_.z / 2) > (boxPosB.z - boxB->size_.z / 2) &&
		(boxPosA.z - boxA->size_.z / 2) < (boxPosB.z + boxB->size_.z / 2))
	{
		return true;
	}
	return false;
}

//箱型と球体の衝突判定
//引数：box	箱型判定
//引数：sphere	２つ目の箱型判定
//戻値：接触していればtrue
bool Collider::IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere)
{
	XMFLOAT3 circlePos = Float3Add(sphere->parent->GetComponent<Transform>()->GetWorldPosition(), sphere->center_);
	XMFLOAT3 boxPos = Float3Add(box->parent->GetComponent<Transform>()->GetWorldPosition(), box->center_);

	//回転行列
	XMFLOAT3 rotateB_ = (box->parent->GetComponent<Transform>()->GetWorldRotate());
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotateB_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotateB_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotateB_.z));
	XMMATRIX matRotate_ = rotateZ * rotateX * rotateY;

	boxPos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&boxPos), matRotate_));

	XMFLOAT3 rotateS_ = (sphere->parent->GetComponent<Transform>()->GetWorldRotate());
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotateB_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotateB_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotateB_.z));
	matRotate_ = rotateZ * rotateX * rotateY;

	circlePos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&circlePos), matRotate_));

	if (circlePos.x > boxPos.x - box->size_.x / 2 - sphere->size_.x &&
		circlePos.x < boxPos.x + box->size_.x / 2 + sphere->size_.x &&
		circlePos.y > boxPos.y - box->size_.y / 2 - sphere->size_.x &&
		circlePos.y < boxPos.y + box->size_.y / 2 + sphere->size_.x &&
		circlePos.z > boxPos.z - box->size_.z / 2 - sphere->size_.x &&
		circlePos.z < boxPos.z + box->size_.z / 2 + sphere->size_.x)
	{
		return true;
	}

	return false;
}

//球体同士の衝突判定
//引数：circleA	１つ目の球体判定
//引数：circleB	２つ目の球体判定
//戻値：接触していればtrue
bool Collider::IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB)
{
	XMFLOAT3 centerA = circleA->center_;
	XMFLOAT3 positionA = circleA->parent->GetComponent<Transform>()->GetWorldPosition();
	XMFLOAT3 centerB = circleB->center_;
	XMFLOAT3 positionB = circleB->parent->GetComponent<Transform>()->GetWorldPosition();

	XMVECTOR v = (XMLoadFloat3(&centerA) + XMLoadFloat3(&positionA))
		- (XMLoadFloat3(&centerB) + XMLoadFloat3(&positionB));

	if (XMVector3Length(v).m128_f32[0] <= circleA->size_.x + circleB->size_.x)
	{
		return true;
	}

	return false;
}

//テスト表示用の枠を描画
//引数：position	オブジェクトの位置
void Collider::Draw(XMFLOAT3 position, XMFLOAT3 rotate)
{
	Transform transform;
	transform.position_ = XMFLOAT3(position.x + center_.x, position.y + center_.y, position.z + center_.z);
	transform.scale_ = size_;
	transform.rotate_ = rotate;

	//描画
	ModelManager::SetShederType(hDebugModel_, Direct3D::SHADER_UNLIT);
	ModelManager::SetTransform(hDebugModel_, &transform);
	ModelManager::Draw(hDebugModel_);
}
