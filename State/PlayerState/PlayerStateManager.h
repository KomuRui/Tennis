#pragma once
#include "../../Engine/DirectX/Input.h"
#include "PlayerState.h"
#include "../../Engine/ResourceManager/Global.h"
#include "StandingState.h"
#include "ForehandingState.h"
#include "BackhandingState.h"
#include "ServingState.h"

//��`
class PlayerBase;

/// <summary>
/// Player�̏�Ԃ��Ǘ����Ă���N���X
/// </summary>
class PlayerStateManager : public PlayerState
{
private:

	//�L�����̑O�����̃x�N�g��
	XMVECTOR front_;        

public:

	//��Ԃ������ϐ�
	static PlayerState* playerState_;

	//�e��ԕϐ�
	static StandingState* playerStanding_;		 //�����Ă�
	static ForehandingState* playerForehanding_; //�t�H�A�n���h
	static BackhandingState* playerBackhanding_; //�o�b�N�n���h
	static ServingState* playerServing_;         //�T�[�u

    //�R���X�g���N�^
	PlayerStateManager();

	//2D�p�X�V
	virtual void Update2D(PlayerBase* player)override;

	//3D�p�X�V
	virtual void Update3D(PlayerBase* player)override;

	//���͂ɂ���ď�ԕω�����
	virtual void HandleInput(PlayerBase* player)override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	virtual void Enter(PlayerBase* player)override;

	//��ԃ`�F���W�p
	void ChangeState(PlayerState* change, PlayerBase* player);

	//�O�x�N�g�����擾
	XMVECTOR GetFrontVec() { return front_; }

};



