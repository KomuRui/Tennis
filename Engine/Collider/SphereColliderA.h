//#pragma once
//#include "ColliderA.h"
//
//
////-----------------------------------------------------------
////���̂̓����蔻��
////-----------------------------------------------------------
//class SphereColliderA : public ColliderA
//{
//	//Collider�N���X��private�����o�ɃA�N�Z�X�ł���悤�ɂ���
//	friend class ColliderA;
//
//public:
//	//�R���X�g���N�^�i�����蔻��̍쐬�j
//	//�����FbasePos	�����蔻��̒��S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
//	//�����Fradius	�����蔻��̃T�C�Y�i���a�j
//	SphereColliderA(XMFLOAT3 center, float radius, bool rotateflag = false);
//
//	//�Z�b�g�֐�
//	void SetColliderPos(XMFLOAT3 pos) { center_ = pos; }
//
//	//�Q�b�g�֐�
//	XMFLOAT3 GetColliderPos() { return center_; }
//
//private:
//	//�ڐG����
//	//�����Ftarget	����̓����蔻��
//	//�ߒl�F�ڐG���Ă��true
//	bool IsHit(ColliderA* target) override;
//};
//
