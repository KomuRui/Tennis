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

	
	XMVECTOR front_;			//�L�����̑O�����̃x�N�g��       
	int hTime_;					//�^�C�}�[�n���h��
	string hChargeEffectName_;  //�`���[�W�G�t�F�N�g�ԍ�

	bool isRestorePosture_; //���̎p���ɖ߂����ǂ���
	bool isHitMove_;		//�ł��������Ă��邩

	int buttonCode_;		//�ł��̃{�^���R�[�h�i�[�p
	float chargeTime_;      //�`���[�W����             

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

	//���̎p���ɖ߂����ǂ����ݒ�
	void SetRestorePosture(bool flag) { isRestorePosture_ = flag; }

	//�ł��삩�ǂ����ݒ�
	void SetHitMove(bool flag) { isHitMove_ = flag; }

	//�ł�������Ă��邩�擾
	bool IsHitMove() { return isHitMove_; }

	//�O�x�N�g�����擾
	XMVECTOR GetFrontVec() { return front_; }

	//�{�^���R�[�h���擾
	int GetNowButtonCode() { return buttonCode_; }

	//�{�^���R�[�h���Z�b�g
	void SetNowButtonCode(int code) { buttonCode_ = code; }

	//�G�t�F�N�g�ԍ��擾
	string GetChargeEffectNum() { return hChargeEffectName_; }

	//�G�t�F�N�g�ԍ��Z�b�g
	void SetChargeEffectNum(string s) { hChargeEffectName_ = s; }

	//�`���[�W���Ԃ��擾
	float GetChargeTime() { return chargeTime_; }

	//�`���[�W���Ԃ�ݒ�
	void SetChargeTime(float t) { chargeTime_ = t; }
};



