#include "SphereColliderA.h"
#include "BoxColliderA.h"
#include "../ResourceManager/ModelManager.h"

//�R���X�g���N�^�i�����蔻��̍쐬�j
//�����FbasePos	�����蔻��̒��S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
//�����Fsize	�����蔻��̃T�C�Y
SphereColliderA::SphereColliderA(XMFLOAT3 center, float radius, bool rotateflag)
{
	center_ = center;
	size_ = XMFLOAT3(radius, radius, radius);
	type_ = COLLIDER_CIRCLE;
	rotateflag_ = rotateflag;

	//�����[�X���͔���g�͕\�����Ȃ�
#ifdef _DEBUG
	//�e�X�g�\���p����g
	hDebugModel_ = ModelManager::Load("DebugCollision/sphereCollider.fbx");
#endif
}

//�ڐG����
//�����Ftarget	����̓����蔻��
//�ߒl�F�ڐG���Ă��true
bool SphereColliderA::IsHit(ColliderA* target)
{
	if (target->type_ == COLLIDER_BOX)
		return IsHitBoxVsCircle((BoxColliderA*)target, this);
	else
		return IsHitCircleVsCircle((SphereColliderA*)target, this);
}