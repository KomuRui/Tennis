#pragma once
#include "ColliderA.h"


//-----------------------------------------------------------
//���^�̓����蔻��
//-----------------------------------------------------------
class BoxColliderA :	public ColliderA
{
	//Collider�N���X��private�����o�ɃA�N�Z�X�ł���悤�ɂ���
	friend class Collider;

public:
	//�R���X�g���N�^�i�����蔻��̍쐬�j
	//�����FbasePos	�����蔻��̒��S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
	//�����Fsize	�����蔻��̃T�C�Y�i���A�����A���s���j
	BoxColliderA(XMFLOAT3 basePos, XMFLOAT3 size, bool rotateflag = false);

private:
	//�ڐG����
	//�����Ftarget	����̓����蔻��
	//�ߒl�F�ڐG���Ă��true
	bool IsHit(ColliderA* target) override;
};

