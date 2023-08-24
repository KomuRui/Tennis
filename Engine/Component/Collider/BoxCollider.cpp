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
	XMVECTOR rotateQua = XMQuaternionRotationMatrix(parent->GetComponent<Transform>()->GetWorldRotateMatrix());
	OBB_X = XMVector3Rotate(OBB_X, rotateQua);
	OBB_Y = XMVector3Rotate(OBB_Y, rotateQua);
	OBB_Z = XMVector3Rotate(OBB_Z, rotateQua);
}