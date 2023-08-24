#pragma once
#include "Collider.h"

/// <summary>
/// ���^�R���C�_�[
/// </summary>
class BoxCollider : public Collider
{
	//Collider�N���X��private�����o�ɃA�N�Z�X�ł���悤�ɂ���
	friend class Collider;

	//�����x�N�g��
	XMVECTOR nX;
	XMVECTOR nY;
	XMVECTOR nZ;

	//�e�������̒���
	XMVECTOR OBB_X;
	XMVECTOR OBB_Y;
	XMVECTOR OBB_Z;

public:

	//�R���X�g���N�^�i�����蔻��̍쐬�j
	BoxCollider();

	//�I�u�W�F�N�gA,B�̋������v�Z
	XMVECTOR calcDistance(XMFLOAT3 posA, XMFLOAT3 posB);

	//�������ɓ��e���ꂽ���������瓊�e���������Z�o
	//sep : ������
	//e1  : ��1
	//e2  : ��2
	//e3  : ��3(��3�͊����ł���ꍇ������)
	float prjLine(XMVECTOR* sep, XMVECTOR* e1, XMVECTOR* e2, XMVECTOR* e3 = nullptr);

	//�e���x�N�g������]
	void CalcAxisVec();

private:

	//�ڐG����
	//�����Ftarget	����̓����蔻��
	//�ߒl�F�ڐG���Ă��true
	bool IsHit(Collider* target) override;
};

