#include "BoxCollider.h"
#include "SphereCollider.h"
#include "../../GameObject/GameObject.h"
#include "../../ResourceManager/ModelManager.h"
#include "../../GUI/ImGuiSet.h"

//�R���X�g���N�^
Collider::Collider()
	:nowPosition_(99999, 99999, 99999),beforePosition_(99999, 99999, 99999), nowRotate_(99999, 99999, 99999), beforeRotate_(99999, 99999, 99999)
{
}

//�f�X�g���N�^
Collider::~Collider()
{
}

//�`��
void Collider::Draw()
{

//�f�o�b�O�̎�����
#ifdef _DEBUG

	//�t���[�������`��ɂ���
	Direct3D::SetShader(Direct3D::SHADER_UNLIT);

	//�ʒu�i�[�p
	XMFLOAT3 position = parent->GetComponent<Transform>()->GetWorldPosition();

	//�R���C�_�[�̃g�����X�t�H�[��
	Transform transform;
	transform.position_ = XMFLOAT3(position.x + center_.x, position.y + center_.y, position.z + center_.z);
	transform.scale_ = size_;
	transform.rotate_ = parent->GetComponent<Transform>()->GetWorldRotate();

	//�`��
	ModelManager::SetShederType(hDebugModel_, Direct3D::SHADER_UNLIT);
	ModelManager::SetTransform(hDebugModel_, &transform);
	ModelManager::Draw(hDebugModel_);

	//���ɖ߂�
	Direct3D::SetShader(Direct3D::SHADER_3D);

#endif

}

void Collider::Update()
{
	//�ʒu�i�[�p
	XMFLOAT3 position = parent->GetComponent<Transform>()->GetWorldPosition();
	XMFLOAT3 rotate = parent->GetComponent<Transform>()->GetWorldRotate();

	//�܂���񂪓����Ă��Ȃ��̂Ȃ�
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

	//�܂���񂪓����Ă��Ȃ��̂Ȃ�
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

//�Փ˔���
//�����FpTarget	�Փ˂��Ă邩���ׂ鑊��
void Collider::Collision(GameObject* pTarget)
{
	//�������m�̓����蔻��͂��Ȃ�
	if (pTarget == nullptr || this->parent == pTarget)
	{
		return;
	}

	//���X�g���擾
	list<Collider*> my = parent->GetComponentList<Collider>();
	list<Collider*> tar = pTarget->GetComponentList<Collider>();

	//������pTarget�̃R���W���������g���ē����蔻��
	//1�̃I�u�W�F�N�g�������̃R���W�������������Ă�ꍇ������̂œ�d���[�v
	for (auto i = my.begin(); i != my.end(); i++)
	{
		for (auto j = tar.begin(); j != tar.end(); j++)
		{
			//���������Ȃ�
			if ((*i)->IsHit(*j))
			{
				//�֐��̏�񂪂���̂Ȃ瓖�������֐����Ă�
				if(OnCollision)
					(*parent.*OnCollision)(pTarget);
			}
		}
	}

	//�q�������Ȃ��Ȃ�I���
	if (pTarget->GetChildList()->empty())
		return;

	//�q���������蔻��
	for (auto i = pTarget->GetChildList()->begin(); i != pTarget->GetChildList()->end(); i++)
	{
		for (auto j = (*i)->GetChildList()->begin(); j != (*i)->GetChildList()->end(); j++)
		{

			//�R���C�_�[������̂Ȃ��
			if ((*j)->GetComponent<Collider>() && this != (*j)->GetComponent<Collider>())
				Collision((*j));

		}
	}
}

//���^���m�̏Փ˔���
//�����FboxA	�P�ڂ̔��^����
//�����FboxB	�Q�ڂ̔��^����
//�ߒl�F�ڐG���Ă����true
bool Collider::IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB)
{

	/*XMFLOAT3 boxAPos = Float3Add(boxA->parent->GetComponent<Transform>()->GetWorldPosition(), boxA->center_);
	XMFLOAT3 boxBPos = Float3Add(boxB->parent->GetComponent<Transform>()->GetWorldPosition(), boxB->center_);

	XMVECTOR betweenCenterPoint = XMLoadFloat3(&boxBPos) - XMLoadFloat3(&boxAPos);*/

	boxA->CalcAxisVec();
	boxB->CalcAxisVec();

	//float rA = XMVectorGetX(XMVector3Length(boxA->OBB_X));								    //boxA�̒��S�_����̒���
	//float rB = boxA->prjLine(&boxA->OBB_X, &boxB->OBB_X, &boxB->OBB_Y, &boxB->OBB_Z);		//boxB�̒��S�_����̒���
	//float  L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(boxA->OBB_X))));//���S�_�Ԃ̒���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	//rA = XMVectorGetX(XMVector3Length(boxA->OBB_Y));								    //boxA�̒��S�_����̒���
	//rB = boxA->prjLine(&boxA->OBB_Y, &boxB->OBB_X, &boxB->OBB_Y, &boxB->OBB_Z);			//boxB�̒��S�_����̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(boxA->OBB_Y))));//���S�_�Ԃ̒���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	//rA = XMVectorGetX(XMVector3Length(boxA->OBB_Z));								    //boxA�̒��S�_����̒���
	//rB = boxA->prjLine(&boxA->OBB_Z, &boxB->OBB_X, &boxB->OBB_Y, &boxB->OBB_Z);			//boxB�̒��S�_����̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(boxA->OBB_Z))));//���S�_�Ԃ̒���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	//rA = XMVectorGetX(XMVector3Length(boxB->OBB_X));								    //boxA�̒��S�_����̒���
	//rB = boxA->prjLine(&boxB->OBB_X, &boxA->OBB_X, &boxA->OBB_Y, &boxA->OBB_Z);			//boxB�̒��S�_����̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(boxB->OBB_X))));//���S�_�Ԃ̒���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	//rA = XMVectorGetX(XMVector3Length(boxB->OBB_Y));								    //boxA�̒��S�_����̒���
	//rB = boxA->prjLine(&boxB->OBB_Y, &boxA->OBB_X, &boxA->OBB_Y, &boxA->OBB_Z);			//boxB�̒��S�_����̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(boxB->OBB_Y))));//���S�_�Ԃ̒���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	//rA = XMVectorGetX(XMVector3Length(boxB->OBB_Z));								    //boxA�̒��S�_����̒���
	//rB = boxA->prjLine(&boxB->OBB_Z, &boxA->OBB_X, &boxA->OBB_Y, &boxA->OBB_Z);			//boxB�̒��S�_����̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, XMVector3Normalize(boxB->OBB_Z))));//���S�_�Ԃ̒���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	/////////////////////////////////��������O�ώ��ɂ��Փ˔���//////////////////////////////////////

	//XMVECTOR cross;
	////boxA��X����boxB��X���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nX, boxB->nX));
	//rA = boxA->prjLine(&cross, &boxA->OBB_Y, &boxA->OBB_Z);				//boxA�̒���
	//rB = boxA->prjLine(&cross, &boxB->OBB_Y, &boxB->OBB_Z);				//boxB�̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxA��X����boxB��Y���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nX, boxB->nY));
	//rA = boxA->prjLine(&cross, &boxA->OBB_Y, &boxA->OBB_Z);				//boxA�̒���
	//rB = boxA->prjLine(&cross, &boxB->OBB_X, &boxB->OBB_Z);				//boxB�̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxA��X����boxB��Z���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nX, boxB->nZ));
	//rA = boxA->prjLine(&cross, &boxA->OBB_Y, &boxA->OBB_Z);				//boxA�̒���
	//rB = boxA->prjLine(&cross, &boxB->OBB_X, &boxB->OBB_Y);				//boxB�̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));//�������ɓ��e�������S�_�Ԃ̋���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxA��Y����boxB��X���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nY, boxB->nX));
	//rA = boxA->prjLine(&cross, &boxA->OBB_X, &boxA->OBB_Z);				//boxA�̒���
	//rB = boxA->prjLine(&cross, &boxB->OBB_Y, &boxB->OBB_Z);				//boxB�̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));//�������ɓ��e�������S�_�Ԃ̋���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxA��Y����boxB��Y���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nY, boxB->nY));
	//rA = boxA->prjLine(&cross, &boxA->OBB_X, &boxA->OBB_Z);				//boxA�̒���
	//rB = boxA->prjLine(&cross, &boxB->OBB_X, &boxB->OBB_Z);				//boxB�̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxA��Y����boxB��Z���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nY, boxB->nZ));
	//rA = boxA->prjLine(&cross, &boxA->OBB_X, &boxA->OBB_Z);				//boxA�̒���
	//rB = boxA->prjLine(&cross, &boxB->OBB_X, &boxB->OBB_Y);				//boxB�̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxA��Z����boxB��X���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nZ, boxB->nX));
	//rA = boxA->prjLine(&cross, &boxA->OBB_X, &boxA->OBB_Y);				//boxA�̒���
	//rB = boxA->prjLine(&cross, &boxB->OBB_Y, &boxB->OBB_Z);				//boxB�̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxA��Z����boxB��Y���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nZ, boxB->nY));
	//rA = boxA->prjLine(&cross, &boxA->OBB_X, &boxA->OBB_Y);				//boxA�̒���
	//rB = boxA->prjLine(&cross, &boxB->OBB_X, &boxB->OBB_Z);				//boxB�̒���
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));	//�������ɓ��e�������S�_�Ԃ̋���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	////boxA��Z����boxB��Z���̊O�� : ���̊O�ς𕪗����Ƃ��Čv�Z���s��
	//cross = XMVector3Normalize(XMVector3Cross(boxA->nZ, boxB->nZ));
	//rA = boxA->prjLine(&cross, &boxA->OBB_X, &boxA->OBB_Y);
	//rB = boxA->prjLine(&cross, &boxB->OBB_X, &boxB->OBB_Y);
	//L = fabsf(XMVectorGetX(XMVector3Dot(betweenCenterPoint, cross)));//�������ɓ��e�������S�_�Ԃ̋���
	//if (L > rA + rB)
	//{
	//	ImGuiSet::DebugLog("isHit", false);
	//	return false;
	//}

	ImGuiSet::DebugLog("isHit", true);
	//���S�_�Ԃ̋���������rA + rB�ȏ�ɂȂ�Ȃ������̂œ������Ă���
	return true;

}

//���^�Ƌ��̂̏Փ˔���
//�����Fbox	���^����
//�����Fsphere	�Q�ڂ̔��^����
//�ߒl�F�ڐG���Ă����true
bool Collider::IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere)
{
	XMFLOAT3 circlePos = Float3Add(sphere->parent->GetComponent<Transform>()->GetWorldPosition(), sphere->center_);
	XMFLOAT3 boxPos = Float3Add(box->parent->GetComponent<Transform>()->GetWorldPosition(), box->center_);

	//��]�s��
	XMFLOAT3 rotateB_ = (box->parent->GetComponent<Transform>()->GetWorldRotate());
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotateB_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotateB_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotateB_.z));

	XMMATRIX matRotateBox_ = rotateZ * rotateX * rotateY;

	//0����Ȃ����
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

	//0����Ȃ����
	if (!VectorNotZero(XMLoadFloat3(&sphere->center_)))
	{
		circlePos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&circlePos), XMMatrixInverse(nullptr, XMMatrixTranslation(sphere->center_.x, sphere->center_.y, sphere->center_.z)) * matRotateCircle_));
		circlePos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&circlePos), XMMatrixTranslation(sphere->center_.x, sphere->center_.y, sphere->center_.z)));
	}

	//�e���_
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

	//�ӂ̏W��
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

	float len = -99999;										//�߂荞�݋���
	XMVECTOR dir = XMVector3Normalize(boxPos - circlePos);  //�߂荞�ݏ����������
	bool isHit = false;										//�������Ă��邩

	//�ӕ���
	for (auto& e : side)
	{
		e.first = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&e.first), XMMatrixInverse(nullptr, XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z)) * matRotateBox_));
		e.first = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&e.first), XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z)));

		e.second = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&e.second), XMMatrixInverse(nullptr, XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z)) * matRotateBox_));
		e.second = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&e.second), XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z)));

		float d = PointToLineSegmentDistance(circlePos, e.first, e.second);

		//���a�������ɂ���Ȃ��
		if (d <= sphere->size_.x && len < (sphere->size_.x - d))
		{
			ARGUMENT_INITIALIZE(len, (sphere->size_.x - d));
			ARGUMENT_INITIALIZE(isHit, true);
		}
	}

	if (len == -99999) ARGUMENT_INITIALIZE(len, 0);

	//�������Ă���̂Ȃ�
	if (isHit)
	{

		//A�������Ă����Ȃ�
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

//���̓��m�̏Փ˔���
//�����FcircleA	�P�ڂ̋��̔���
//�����FcircleB	�Q�ڂ̋��̔���
//�ߒl�F�ڐG���Ă����true
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
		
		//A�������Ă����Ȃ�
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

//�e�X�g�\���p�̘g��`��
//�����Fposition	�I�u�W�F�N�g�̈ʒu
void Collider::Draw(XMFLOAT3 position, XMFLOAT3 rotate)
{
	Transform transform;
	transform.position_ = XMFLOAT3(position.x + center_.x, position.y + center_.y, position.z + center_.z);
	transform.scale_ = size_;
	transform.rotate_ = rotate;

	//�`��
	ModelManager::SetShederType(hDebugModel_, Direct3D::SHADER_UNLIT);
	ModelManager::SetTransform(hDebugModel_, &transform);
	ModelManager::Draw(hDebugModel_);
}
