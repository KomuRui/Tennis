#include "BoxCollider.h"
#include "SphereCollider.h"
#include "../../GameObject/GameObject.h"
#include "../../ResourceManager/ModelManager.h"

//コンストラクタ
Collider::Collider()
	:nowPosition_(99999, 99999, 99999),beforePosition_(99999, 99999, 99999), nowRotate_(99999, 99999, 99999), beforeRotate_(99999, 99999, 99999)
{
}

//デストラクタ
Collider::~Collider()
{
}

//描画
void Collider::Draw()
{

//デバッグの時だけ
#ifdef _DEBUG

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

#endif

}

void Collider::Update()
{
	//位置格納用
	XMFLOAT3 position = parent->GetComponent<Transform>()->GetWorldPosition();

	//まだ情報が入っていないのなら
	if (IsMatch(nowPosition_, XMFLOAT3(99999, 99999, 99999)))
	{
		ARGUMENT_INITIALIZE(nowPosition_, XMFLOAT3(position.x + center_.x, position.y + center_.y, position.z + center_.z));
		ARGUMENT_INITIALIZE(beforePosition_, nowPosition_);
	}
	else
	{
		ARGUMENT_INITIALIZE(beforePosition_, nowPosition_);
		ARGUMENT_INITIALIZE(nowPosition_, XMFLOAT3(position.x + center_.x, position.y + center_.y, position.z + center_.z));
	}
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
				//関数の情報があるのなら当たった関数を呼ぶ
				if(OnCollision)
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
		for (auto j = (*i)->GetChildList()->begin(); j != (*i)->GetChildList()->end(); j++)
		{

			//コライダーがあるのならば
			if ((*j)->GetComponent<Collider>() && this != (*j)->GetComponent<Collider>())
				Collision((*j));

		}
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
	XMMATRIX matRotateBox_ = rotateZ * rotateX * rotateY;

	boxPos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&boxPos), matRotateBox_));

	XMFLOAT3 rotateS_ = (sphere->parent->GetComponent<Transform>()->GetWorldRotate());
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotateB_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotateB_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotateB_.z));
	XMMATRIX matRotateCircle_ = rotateZ * rotateX * rotateY;

	circlePos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&circlePos), matRotateCircle_));

	if (circlePos.x > boxPos.x - box->size_.x / 2 - sphere->size_.x &&
		circlePos.x < boxPos.x + box->size_.x / 2 + sphere->size_.x &&
		circlePos.y > boxPos.y - box->size_.y / 2 - sphere->size_.x &&
		circlePos.y < boxPos.y + box->size_.y / 2 + sphere->size_.x &&
		circlePos.z > boxPos.z - box->size_.z / 2 - sphere->size_.x &&
		circlePos.z < boxPos.z + box->size_.z / 2 + sphere->size_.x)
	{

		XMFLOAT3 boxVertices[] = {
			{ boxPos.x - box->size_.x / 2, boxPos.y - box->size_.y / 2, boxPos.z - box->size_.z / 2 },
			{ boxPos.x + box->size_.x / 2, boxPos.y - box->size_.y / 2, boxPos.z - box->size_.z / 2 },
			{ boxPos.x + box->size_.x / 2, boxPos.y + box->size_.y / 2, boxPos.z - box->size_.z / 2 },
			{ boxPos.x - box->size_.x / 2, boxPos.y + box->size_.y / 2, boxPos.z - box->size_.z / 2 },
			{ boxPos.x - box->size_.x / 2, boxPos.y - box->size_.y / 2, boxPos.z + box->size_.z / 2 },
			{ boxPos.x + box->size_.x / 2, boxPos.y - box->size_.y / 2, boxPos.z + box->size_.z / 2 },
			{ boxPos.x + box->size_.x / 2, boxPos.y + box->size_.y / 2, boxPos.z + box->size_.z / 2 },
			{ boxPos.x - box->size_.x / 2, boxPos.y + box->size_.y / 2, boxPos.z + box->size_.z / 2 }
		};

		float len = -99999;

		for (int i = 0; i < 8; i++)
		{
			float d = -1;

			if(i == 7)
				d = PointToLineSegmentDistance(circlePos, VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&boxVertices[i]), matRotateBox_)), VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&boxVertices[0]), matRotateBox_)));
			else
				d = PointToLineSegmentDistance(circlePos, VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&boxVertices[i]), matRotateBox_)), VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&boxVertices[i + 1]), matRotateBox_)));

			//半径より内側にあるならば
			if (d <= sphere->size_.x && len < (sphere->size_.x - d))
			{
				ARGUMENT_INITIALIZE(len, (sphere->size_.x - d));
			}
		}

		if (len == -99999) ARGUMENT_INITIALIZE(len, 0);

		//Aが動いていたなら
		if (!IsMatch(box->GetNowPos(), box->GetBeforePos()))
		{
			Transform* p = box->parent->GetComponent<Transform>();
			XMVECTOR dir = XMVector3Normalize(box->GetBeforePos() - sphere->GetNowPos());

			p->SetPosition(VectorToFloat3(p->GetPosition() + dir * len));

			ARGUMENT_INITIALIZE(box->nowPosition_, p->GetPosition());
			ARGUMENT_INITIALIZE(box->beforePosition_, box->nowPosition_);
		}
		else if (!IsMatch(sphere->GetNowPos(), sphere->GetBeforePos()))
		{
			
			Transform* p = sphere->parent->GetComponent<Transform>();
			XMVECTOR dir = XMVector3Normalize(sphere->GetBeforePos() - sphere->GetNowPos());
			p->SetPosition(VectorToFloat3(p->GetPosition() + dir * len));

			ARGUMENT_INITIALIZE(sphere->nowPosition_, p->GetPosition());
			ARGUMENT_INITIALIZE(sphere->beforePosition_, sphere->nowPosition_);
		}

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
		float len = (circleA->size_.x + circleB->size_.x) - XMVector3Length(v).m128_f32[0];
		
		//Aが動いていたなら
		if (!IsMatch(circleA->GetNowPos(), circleA->GetBeforePos()))
		{
			Transform *p = circleA->parent->GetComponent<Transform>();
			XMVECTOR dir = XMVector3Normalize(circleA->GetBeforePos() - circleA->GetNowPos());
			p->SetPosition(VectorToFloat3(p->GetPosition() + dir * len));

			ARGUMENT_INITIALIZE(circleA->nowPosition_, p->GetPosition());
			ARGUMENT_INITIALIZE(circleA->beforePosition_, circleA->nowPosition_);
		}
		else if(!IsMatch(circleB->GetNowPos(), circleB->GetBeforePos()))
		{
			Transform* p = circleB->parent->GetComponent<Transform>();
			XMVECTOR dir = XMVector3Normalize(circleB->GetBeforePos() - circleB->GetNowPos());
			p->SetPosition(VectorToFloat3(p->GetPosition() + dir * len));

			ARGUMENT_INITIALIZE(circleB->nowPosition_, p->GetPosition());
			ARGUMENT_INITIALIZE(circleB->beforePosition_, circleB->nowPosition_);
		}

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
