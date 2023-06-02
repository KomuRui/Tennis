#pragma once
#include "Collider.h"


/// <summary>
/// ���̂̓����蔻��
/// </summary>
class SphereCollider : public Collider
{
	//Collider�N���X��private�����o�ɃA�N�Z�X�ł���悤�ɂ���
	friend class Collider;

public:

	//�R���X�g���N�^�i�����蔻��̍쐬�j
	SphereCollider();

	//�Z�b�g�֐�
	void SetColliderPos(XMFLOAT3 pos) { center_ = pos; }

	//�Q�b�g�֐�
	XMFLOAT3 GetColliderPos() { return center_; }

private:

	//�ڐG����
	//�����Ftarget	����̓����蔻��
	//�ߒl�F�ڐG���Ă��true
	bool IsHit(Collider* target) override;
};

