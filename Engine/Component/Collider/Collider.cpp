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
	XMFLOAT3 rotate = parent->GetComponent<Transform>()->GetWorldRotate();

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

	//まだ情報が入っていないのなら
	if (IsMatch(nowRotate_, XMFLOAT3(99999, 99999, 99999)))
	{
		ARGUMENT_INITIALIZE(nowRotate_, rotate);
		ARGUMENT_INITIALIZE(beforePosition_, nowRotate_);
	}
	else
	{
		ARGUMENT_INITIALIZE(beforeRotate_, nowRotate_);
		ARGUMENT_INITIALIZE(nowRotate_, rotate);
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

	//回転行列
	XMFLOAT3 rotateA_ = (boxA->parent->GetComponent<Transform>()->GetWorldRotate());
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotateA_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotateA_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotateA_.z));
	XMMATRIX matRotateBoxA_ = rotateZ * rotateX * rotateY;

	//回転行列
	XMFLOAT3 rotateB_ = (boxB->parent->GetComponent<Transform>()->GetWorldRotate());
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotateB_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotateB_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotateB_.z));
	XMMATRIX matRotateBoxB_ = rotateZ * rotateX * rotateY;

	//各頂点
	XMFLOAT3 boxVerticesA[] = {
			{ boxPosA.x - boxA->size_.x / 2, boxPosA.y - boxA->size_.y / 2, boxPosA.z - boxA->size_.z / 2 },
			{ boxPosA.x + boxA->size_.x / 2, boxPosA.y - boxA->size_.y / 2, boxPosA.z - boxA->size_.z / 2 },
			{ boxPosA.x + boxA->size_.x / 2, boxPosA.y + boxA->size_.y / 2, boxPosA.z - boxA->size_.z / 2 },
			{ boxPosA.x - boxA->size_.x / 2, boxPosA.y + boxA->size_.y / 2, boxPosA.z - boxA->size_.z / 2 },
			{ boxPosA.x - boxA->size_.x / 2, boxPosA.y - boxA->size_.y / 2, boxPosA.z + boxA->size_.z / 2 },
			{ boxPosA.x + boxA->size_.x / 2, boxPosA.y - boxA->size_.y / 2, boxPosA.z + boxA->size_.z / 2 },
			{ boxPosA.x + boxA->size_.x / 2, boxPosA.y + boxA->size_.y / 2, boxPosA.z + boxA->size_.z / 2 },
			{ boxPosA.x - boxA->size_.x / 2, boxPosA.y + boxA->size_.y / 2, boxPosA.z + boxA->size_.z / 2 }
	};

	//辺の集合
	vector<pair<XMFLOAT3, XMFLOAT3>> sideA;
	sideA.push_back({ boxVerticesA[0],boxVerticesA[1] });
	sideA.push_back({ boxVerticesA[1],boxVerticesA[2] });
	sideA.push_back({ boxVerticesA[2],boxVerticesA[3] });
	sideA.push_back({ boxVerticesA[3],boxVerticesA[0] });
	sideA.push_back({ boxVerticesA[4],boxVerticesA[5] });
	sideA.push_back({ boxVerticesA[5],boxVerticesA[6] });
	sideA.push_back({ boxVerticesA[6],boxVerticesA[7] });
	sideA.push_back({ boxVerticesA[7],boxVerticesA[4] });
	sideA.push_back({ boxVerticesA[0],boxVerticesA[4] });
	sideA.push_back({ boxVerticesA[5],boxVerticesA[1] });
	sideA.push_back({ boxVerticesA[6],boxVerticesA[2] });
	sideA.push_back({ boxVerticesA[3],boxVerticesA[7] });

	//各頂点
	XMFLOAT3 boxVerticesB[] = {
			{ boxPosB.x - boxB->size_.x / 2, boxPosB.y - boxB->size_.y / 2, boxPosB.z - boxB->size_.z / 2 },
			{ boxPosB.x + boxB->size_.x / 2, boxPosB.y - boxB->size_.y / 2, boxPosB.z - boxB->size_.z / 2 },
			{ boxPosB.x + boxB->size_.x / 2, boxPosB.y + boxB->size_.y / 2, boxPosB.z - boxB->size_.z / 2 },
			{ boxPosB.x - boxB->size_.x / 2, boxPosB.y + boxB->size_.y / 2, boxPosB.z - boxB->size_.z / 2 },
			{ boxPosB.x - boxB->size_.x / 2, boxPosB.y - boxB->size_.y / 2, boxPosB.z + boxB->size_.z / 2 },
			{ boxPosB.x + boxB->size_.x / 2, boxPosB.y - boxB->size_.y / 2, boxPosB.z + boxB->size_.z / 2 },
			{ boxPosB.x + boxB->size_.x / 2, boxPosB.y + boxB->size_.y / 2, boxPosB.z + boxB->size_.z / 2 },
			{ boxPosB.x - boxB->size_.x / 2, boxPosB.y + boxB->size_.y / 2, boxPosB.z + boxB->size_.z / 2 }
	};

	//辺の集合
	vector<pair<XMFLOAT3, XMFLOAT3>> sideB;
	sideB.push_back({ boxVerticesB[0],boxVerticesB[1] });
	sideB.push_back({ boxVerticesB[1],boxVerticesB[2] });
	sideB.push_back({ boxVerticesB[2],boxVerticesB[3] });
	sideB.push_back({ boxVerticesB[3],boxVerticesB[0] });
	sideB.push_back({ boxVerticesB[4],boxVerticesB[5] });
	sideB.push_back({ boxVerticesB[5],boxVerticesB[6] });
	sideB.push_back({ boxVerticesB[6],boxVerticesB[7] });
	sideB.push_back({ boxVerticesB[7],boxVerticesB[4] });
	sideB.push_back({ boxVerticesB[0],boxVerticesB[4] });
	sideB.push_back({ boxVerticesB[1],boxVerticesB[5] });
	sideB.push_back({ boxVerticesB[2],boxVerticesB[6] });
	sideB.push_back({ boxVerticesB[3],boxVerticesB[7] });

	int count = 0;
	bool isHit = false;										//当たっているか
	float len = 99999;										//めり込み距離
	XMVECTOR dir = XMVector3Normalize(boxPosA - boxPosB);   //めり込み除去する方向									

	//8頂点分回す(回転した後の頂点にする)
	for (int i = 0; i < 8; i++)
	{
		boxVerticesA[i] = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&boxVerticesA[i]), XMMatrixInverse(nullptr, XMMatrixTranslation(boxPosA.x, boxPosA.y, boxPosA.z)) * matRotateBoxA_));
		boxVerticesA[i] = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&boxVerticesA[i]), XMMatrixTranslation(boxPosA.x, boxPosA.y, boxPosA.z)));
		boxVerticesB[i] = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&boxVerticesB[i]), XMMatrixInverse(nullptr, XMMatrixTranslation(boxPosB.x, boxPosB.y, boxPosB.z)) * matRotateBoxB_));
		boxVerticesB[i] = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&boxVerticesB[i]), XMMatrixTranslation(boxPosB.x, boxPosB.y, boxPosB.z)));
	}

	for (int i = 0; i < 8; i++)
	{
		//辺分回す
		for (int j = 0; j < 12; j++)
		{
			//マイナスなら四角の中に入っている
			if (XMVectorGetX(XMVector3Cross(sideB[j].second - sideB[j].first, boxVerticesA[i] - sideB[j].first)) >= 0)
			{
				float d = PointToLineSegmentDistance(boxVerticesA[i], sideB[j].first, sideB[j].second);
				if (d < len)
				{
					ARGUMENT_INITIALIZE(len, d);
				}
			}
			else
				count++;
		}

		if (count == 0)
		{
			ARGUMENT_INITIALIZE(isHit, true);
			break;
		}
		else
		{
			ARGUMENT_INITIALIZE(len, 99999);
			ARGUMENT_INITIALIZE(count,0);
		}

		//辺分回す
		for (int j = 0; j < 12; j++)
		{
			//マイナスなら四角の中に入っている
			if (XMVectorGetZ(XMVector3Cross(sideA[j].second - sideA[j].first, boxVerticesB[i] - sideA[j].first)) >= 0)
			{
				float d = PointToLineSegmentDistance(boxVerticesB[i], sideA[j].first, sideA[j].second);
				if (d < len)
				{
					ARGUMENT_INITIALIZE(len, d);
				}
			}
			else
				count++;
		}

		if (count == 0)
		{
			ARGUMENT_INITIALIZE(isHit, true);
			break;
		}
		else
		{
			ARGUMENT_INITIALIZE(len, 99999);
			ARGUMENT_INITIALIZE(count, 0);
		}
	}

	//当たっているのなら
	if (isHit)
	{
		//Aが動いていたなら
		if (!IsMatch(boxA->GetNowPos(), boxA->GetBeforePos()) || !IsMatch(boxA->GetNowRotate(), boxA->GetBeforeRotate()))
		{
			Transform* p = boxB->parent->GetComponent<Transform>();

			p->SetPosition(VectorToFloat3(p->GetPosition() + -dir * len));

			ARGUMENT_INITIALIZE(boxB->beforePosition_, boxB->nowPosition_);
			ARGUMENT_INITIALIZE(boxB->nowPosition_, p->GetPosition());
		}
		else if (!IsMatch(boxB->GetNowPos(), boxB->GetBeforePos()) || !IsMatch(boxB->GetNowRotate(), boxB->GetBeforeRotate()))
		{

			Transform* p = boxA->parent->GetComponent<Transform>();
			p->SetPosition(VectorToFloat3(p->GetPosition() + dir * len));

			ARGUMENT_INITIALIZE(boxA->beforePosition_, boxA->nowPosition_);
			ARGUMENT_INITIALIZE(boxA->nowPosition_, p->GetPosition());
		}

	}

	return isHit;
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

	//0じゃなければ
	if (!VectorNotZero(XMLoadFloat3(&box->center_)))
	{
		boxPos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&boxPos), XMMatrixInverse(nullptr, XMMatrixTranslation(box->center_.x, box->center_.y, box->center_.z)) * matRotateBox_));
		boxPos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&boxPos), XMMatrixTranslation(box->center_.x, box->center_.y, box->center_.z)));
	}

	XMFLOAT3 rotateS_ = (sphere->parent->GetComponent<Transform>()->GetWorldRotate());
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotateS_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotateS_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotateS_.z));
	XMMATRIX matRotateCircle_ = rotateZ * rotateX * rotateY;

	//0じゃなければ
	if (!VectorNotZero(XMLoadFloat3(&sphere->center_)))
	{
		circlePos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&circlePos), XMMatrixInverse(nullptr, XMMatrixTranslation(sphere->center_.x, sphere->center_.y, sphere->center_.z)) * matRotateCircle_));
		circlePos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&circlePos), XMMatrixTranslation(sphere->center_.x, sphere->center_.y, sphere->center_.z)));
	}

	//各頂点
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

	//辺の集合
	vector<pair<XMFLOAT3, XMFLOAT3>> side;
	side.push_back({ boxVertices[0],boxVertices[1]});
	side.push_back({ boxVertices[1],boxVertices[2]});
	side.push_back({ boxVertices[2],boxVertices[3]});
	side.push_back({ boxVertices[3],boxVertices[0]});
	side.push_back({ boxVertices[4],boxVertices[5]});
	side.push_back({ boxVertices[5],boxVertices[6]});
	side.push_back({ boxVertices[6],boxVertices[7]});
	side.push_back({ boxVertices[7],boxVertices[4]});
	side.push_back({ boxVertices[0],boxVertices[4]});
	side.push_back({ boxVertices[1],boxVertices[5]});
	side.push_back({ boxVertices[2],boxVertices[6]});
	side.push_back({ boxVertices[3],boxVertices[7]});

	float len = -99999;										//めり込み距離
	XMVECTOR dir = XMVector3Normalize(boxPos - circlePos);  //めり込み除去する方向
	bool isHit = false;										//当たっているか

	//辺分回す
	for (auto& e : side)
	{
		e.first = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&e.first), XMMatrixInverse(nullptr, XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z)) * matRotateBox_));
		e.first = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&e.first), XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z)));

		e.second = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&e.second), XMMatrixInverse(nullptr, XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z)) * matRotateBox_));
		e.second = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&e.second), XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z)));

		float d = PointToLineSegmentDistance(circlePos, e.first, e.second);

		//半径より内側にあるならば
		if (d <= sphere->size_.x && len < (sphere->size_.x - d))
		{
			ARGUMENT_INITIALIZE(len, (sphere->size_.x - d));
			ARGUMENT_INITIALIZE(isHit, true);
		}
	}

	if (len == -99999) ARGUMENT_INITIALIZE(len, 0);

	//当たっているのなら
	if (isHit)
	{

		//Aが動いていたなら
		if (!IsMatch(box->GetNowPos(), box->GetBeforePos()) || !IsMatch(box->GetNowRotate(), box->GetBeforeRotate()))
		{
			Transform* p = sphere->parent->GetComponent<Transform>();

			p->SetPosition(VectorToFloat3(p->GetPosition() + -dir * len));

			ARGUMENT_INITIALIZE(sphere->beforePosition_, sphere->nowPosition_);
			ARGUMENT_INITIALIZE(sphere->nowPosition_, p->GetPosition());
		}
		else if (!IsMatch(sphere->GetNowPos(), sphere->GetBeforePos()))
		{
			
			Transform* p = box->parent->GetComponent<Transform>();
			p->SetPosition(VectorToFloat3(p->GetPosition() + dir * len));

			ARGUMENT_INITIALIZE(box->beforePosition_, box->nowPosition_);
			ARGUMENT_INITIALIZE(box->nowPosition_, p->GetPosition());
		}
	}

	return isHit;
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

			ARGUMENT_INITIALIZE(circleA->beforePosition_, circleA->nowPosition_);
			ARGUMENT_INITIALIZE(circleA->nowPosition_, p->GetPosition());
		}
		else if(!IsMatch(circleB->GetNowPos(), circleB->GetBeforePos()))
		{
			Transform* p = circleB->parent->GetComponent<Transform>();
			XMVECTOR dir = XMVector3Normalize(circleB->GetBeforePos() - circleB->GetNowPos());
			p->SetPosition(VectorToFloat3(p->GetPosition() + dir * len));

			ARGUMENT_INITIALIZE(circleB->beforePosition_, circleB->nowPosition_);
			ARGUMENT_INITIALIZE(circleB->nowPosition_, p->GetPosition());
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
