#include "BoxColliderA.h"
#include "SphereColliderA.h"
#include "../ResourceManager/ModelManager.h"


//�R���X�g���N�^�i�����蔻��̍쐬�j
//�����FbasePos	�����蔻��̒��S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
//�����Fsize	�����蔻��̃T�C�Y
BoxColliderA::BoxColliderA(XMFLOAT3 basePos, XMFLOAT3 size, bool rotateflag)
{
	center_ = basePos;
	size_ = size;
	type_ = COLLIDER_BOX;
	rotateflag_ = rotateflag;

	//�����[�X���͔���g�͕\�����Ȃ�
#ifdef _DEBUG
	//�e�X�g�\���p����g
	hDebugModel_ = ModelManager::Load("DebugCollision/boxCollider.fbx");
#endif
}

//�ڐG����
//�����Ftarget	����̓����蔻��
//�ߒl�F�ڐG���Ă��true
bool BoxColliderA::IsHit(Collider* target)
{
	if (target->type_ == COLLIDER_BOX)
		return IsHitBoxVsBox((BoxColliderA*)target, this);
	else
		return IsHitBoxVsCircle(this, (SphereColliderA*)target);
}