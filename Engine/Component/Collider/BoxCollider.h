#pragma once
#include "Collider.h"

/// <summary>
/// ���^�R���C�_�[
/// </summary>
class BoxCollider : public Collider
{
	//Collider�N���X��private�����o�ɃA�N�Z�X�ł���悤�ɂ���
	friend class Collider;

public:

	//�R���X�g���N�^�i�����蔻��̍쐬�j
	BoxCollider();

private:

	//�ڐG����
	//�����Ftarget	����̓����蔻��
	//�ߒl�F�ڐG���Ă��true
	bool IsHit(Collider* target) override;
};

