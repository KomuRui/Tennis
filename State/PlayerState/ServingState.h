#pragma once
#include "PlayerState.h"

class PlayerBase;

/// <summary>
/// �T�[�u���
/// </summary>
class ServingState : public PlayerState
{
	bool isCharge_ = false; //�\���Ă邩�ǂ���
	int hTime_;		        //�^�C�}�[�n���h��

public:

	//2D�p�X�V
	void Update2D(PlayerBase* player) override;

	//3D�p�X�V
	void Update3D(PlayerBase* player) override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput(PlayerBase* player) override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter(PlayerBase* player) override;

	//�`���[�W���Ă��邩�ǂ���
	bool IsCharge() { return isCharge_; }
};

