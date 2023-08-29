#include "BoxCollider.h"
#include "SphereCollider.h"
#include "../../GameObject/GameObject.h"
#include "../../ResourceManager/ModelManager.h"
#include "../../GUI/ImGuiSet.h"

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

	/*XMFLOAT3 boxAPos = Float3Add(boxA->parent->GetComponent<Transform>()->GetWorldPosition(), boxA->center_);
	XMFLOAT3 boxBPos = Float3Add(boxB->parent->GetComponent<Transform>()->GetWorldPosition(), boxB->center_);

	XMVECTOR betweenCenterPoint = XMLoadFloat3(&boxBPos) - XMLoadFloat3(&boxAPos);*/

	boxA->CalcAxisVec();
	boxB->CalcAxisVec();

	//float rA = XMVectorGetX(XMVector3Length(boxA->OBB_X));								    //boxAの中心点からの長さ
	//float rB = boxA->prjLine(&boxA->OBB_X, &boxB->OBB_X, &boxB->OBB_Y, &boxB->OBB_Z);		//boxBの中心点からの長さ
	//float  L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(boxA->OBB_X))));//中心点間の長さ
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	//rA = XMVectorGetX(XMVector3Length(boxA->OBB_Y));								    //boxAの中心点からの長さ
	//rB = boxA->prjLine(&boxA->OBB_Y, &boxB->OBB_X, &boxB->OBB_Y, &boxB->OBB_Z);			//boxBの中心点からの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(boxA->OBB_Y))));//中心点間の長さ
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	//rA = XMVectorGetX(XMVector3Length(boxA->OBB_Z));								    //boxAの中心点からの長さ
	//rB = boxA->prjLine(&boxA->OBB_Z, &boxB->OBB_X, &boxB->OBB_Y, &boxB->OBB_Z);			//boxBの中心点からの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(boxA->OBB_Z))));//中心点間の長さ
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	//rA = XMVectorGetX(XMVector3Length(boxB->OBB_X));								    //boxAの中心点からの長さ
	//rB = boxA->prjLine(&boxB->OBB_X, &boxA->OBB_X, &boxA->OBB_Y, &boxA->OBB_Z);			//boxBの中心点からの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(boxB->OBB_X))));//中心点間の長さ
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	//rA = XMVectorGetX(XMVector3Length(boxB->OBB_Y));								    //boxAの中心点からの長さ
	//rB = boxA->prjLine(&boxB->OBB_Y, &boxA->OBB_X, &boxA->OBB_Y, &boxA->OBB_Z);			//boxBの中心点からの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(boxB->OBB_Y))));//中心点間の長さ
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	//rA = XMVectorGetX(XMVector3Length(boxB->OBB_Z));								    //boxAの中心点からの長さ
	//rB = boxA->prjLine(&boxB->OBB_Z, &boxA->OBB_X, &boxA->OBB_Y, &boxA->OBB_Z);			//boxBの中心点からの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(boxB->OBB_Z))));//中心点間の長さ
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	/////////////////////////////////ここから外積軸による衝突判定//////////////////////////////////////

	//XMVECTOR cross;
	////boxAのX軸とboxBのX軸の外積 : この外積を分離軸として計算を行う
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nX, boxB->nX));
	//rA = boxA->prjLine(&cross, &boxA->OBB_Y, &boxA->OBB_Z);				//boxAの長さ
	//rB = boxA->prjLine(&cross, &boxB->OBB_Y, &boxB->OBB_Z);				//boxBの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//分離軸に投影した中心点間の距離
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxAのX軸とboxBのY軸の外積 : この外積を分離軸として計算を行う
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nX, boxB->nY));
	//rA = boxA->prjLine(&cross, &boxA->OBB_Y, &boxA->OBB_Z);				//boxAの長さ
	//rB = boxA->prjLine(&cross, &boxB->OBB_X, &boxB->OBB_Z);				//boxBの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//分離軸に投影した中心点間の距離
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxAのX軸とboxBのZ軸の外積 : この外積を分離軸として計算を行う
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nX, boxB->nZ));
	//rA = boxA->prjLine(&cross, &boxA->OBB_Y, &boxA->OBB_Z);				//boxAの長さ
	//rB = boxA->prjLine(&cross, &boxB->OBB_X, &boxB->OBB_Y);				//boxBの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));//分離軸に投影した中心点間の距離
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxAのY軸とboxBのX軸の外積 : この外積を分離軸として計算を行う
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nY, boxB->nX));
	//rA = boxA->prjLine(&cross, &boxA->OBB_X, &boxA->OBB_Z);				//boxAの長さ
	//rB = boxA->prjLine(&cross, &boxB->OBB_Y, &boxB->OBB_Z);				//boxBの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));//分離軸に投影した中心点間の距離
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxAのY軸とboxBのY軸の外積 : この外積を分離軸として計算を行う
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nY, boxB->nY));
	//rA = boxA->prjLine(&cross, &boxA->OBB_X, &boxA->OBB_Z);				//boxAの長さ
	//rB = boxA->prjLine(&cross, &boxB->OBB_X, &boxB->OBB_Z);				//boxBの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//分離軸に投影した中心点間の距離
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxAのY軸とboxBのZ軸の外積 : この外積を分離軸として計算を行う
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nY, boxB->nZ));
	//rA = boxA->prjLine(&cross, &boxA->OBB_X, &boxA->OBB_Z);				//boxAの長さ
	//rB = boxA->prjLine(&cross, &boxB->OBB_X, &boxB->OBB_Y);				//boxBの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//分離軸に投影した中心点間の距離
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxAのZ軸とboxBのX軸の外積 : この外積を分離軸として計算を行う
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nZ, boxB->nX));
	//rA = boxA->prjLine(&cross, &boxA->OBB_X, &boxA->OBB_Y);				//boxAの長さ
	//rB = boxA->prjLine(&cross, &boxB->OBB_Y, &boxB->OBB_Z);				//boxBの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//分離軸に投影した中心点間の距離
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxAのZ軸とboxBのY軸の外積 : この外積を分離軸として計算を行う
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nZ, boxB->nY));
	//rA = boxA->prjLine(&cross, &boxA->OBB_X, &boxA->OBB_Y);				//boxAの長さ
	//rB = boxA->prjLine(&cross, &boxB->OBB_X, &boxB->OBB_Z);				//boxBの長さ
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//分離軸に投影した中心点間の距離
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxAのZ軸とboxBのZ軸の外積 : この外積を分離軸として計算を行う
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nZ, boxB->nZ));
	//rA = boxA->prjLine(&cross, &boxA->OBB_X, &boxA->OBB_Y);
	//rB = boxA->prjLine(&cross, &boxB->OBB_X, &boxB->OBB_Y);
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));//分離軸に投影した中心点間の距離
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	ImGuiSet::DebugLog("isHit", true);
	//中心点間の距離が一回もrA + rB以上にならなかったので当たっている
	return true;

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
