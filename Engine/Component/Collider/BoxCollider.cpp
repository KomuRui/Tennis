#include "BoxCollider.h"
#include "SphereCollider.h"
#include "../../ResourceManager/ModelManager.h"


//�R���X�g���N�^�i�����蔻��̍쐬�j
//�����FbasePos	�����蔻��̒��S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
//�����Fsize	�����蔻��̃T�C�Y
BoxCollider::BoxCollider()
{
	type_ = COLLIDER_BOX;

	//�����[�X���͔���g�͕\�����Ȃ�
#ifdef _DEBUG
	//�e�X�g�\���p����g
	hDebugModel_ = ModelManager::Load("DebugCollision/boxCollider.fbx");
#endif

	nX = RIGHT_VECTOR;
	nY = UP_VECTOR;
	nZ = STRAIGHT_VECTOR;
}

//�ڐG����
//�����Ftarget	����̓����蔻��
//�ߒl�F�ڐG���Ă��true
bool BoxCollider::IsHit(Collider* target)
{
	if (target->type_ == COLLIDER_BOX)
		return IsHitBoxVsBox((BoxCollider*)target, this);
	else
		return IsHitBoxVsCircle(this, (SphereCollider*)target);
}

//�I�u�W�F�N�gA,B�̋������v�Z
XMVECTOR BoxCollider::calcDistance(XMFLOAT3 posA, XMFLOAT3 posB)
{
	XMVECTOR distance = XMLoadFloat3(&posB) - XMLoadFloat3(&posA);
	return distance;
}

//�������ɓ��e���ꂽ���������瓊�e���������Z�o
float BoxCollider::prjLine(XMVECTOR* sep, XMVECTOR* e1, XMVECTOR* e2, XMVECTOR* e3)
{
	XMVECTOR sp = XMVectorZero();
	sp = XMVector3Normalize(*sep);
	float r1 = abs(XMVectorGetX(XMVector3Dot(sp, *e1)));
	float r2 = abs(XMVectorGetX(XMVector3Dot(sp, *e2)));
	float r3 = e3 ? abs(XMVectorGetX(XMVector3Dot(sp, *e3))) : 0;

	return r1 + r2 + r3;
}

//�e���x�N�g������]
void BoxCollider::CalcAxisVec()
{
	XMFLOAT3 boxPos = Float3Add(parent->GetComponent<Transform>()->GetWorldPosition(), center_);

	XMFLOAT3 rotate_ = (parent->GetComponent<Transform>()->GetWorldRotate());
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	XMMATRIX matRotateBox_ = rotateZ * rotateX * rotateY;

	OBB_X = nX * (size_.x / 2);
	OBB_Y = nY * (size_.y / 2);
	OBB_Z = nZ * (size_.z / 2);

	OBB_X = XMVector3TransformCoord(OBB_X, XMMatrixInverse(nullptr, XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z)) * matRotateBox_);
	OBB_X = XMVector3TransformCoord(OBB_X, XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z));
	OBB_Y = XMVector3TransformCoord(OBB_Y, XMMatrixInverse(nullptr, XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z)) * matRotateBox_);
	OBB_Y = XMVector3TransformCoord(OBB_Y, XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z));
	OBB_Z = XMVector3TransformCoord(OBB_Z, XMMatrixInverse(nullptr, XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z)) * matRotateBox_);
	OBB_Z = XMVector3TransformCoord(OBB_Z, XMMatrixTranslation(boxPos.x, boxPos.y, boxPos.z));

}