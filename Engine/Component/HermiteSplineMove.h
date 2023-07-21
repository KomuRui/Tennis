#pragma once
#include "../ResourceManager/Global.h"
#include <vector>

/// <summary>
/// �G���~�[�g�X�v���C���Ȑ����g�������� 
/// </summary>
class HermiteSplineMove
{

	vector<pair<XMFLOAT3, XMFLOAT3>> pathData_; //�ړ����鎞�Ɏg���p�X�f�[�^
	XMFLOAT3 endPosition_; //�I���|�W�V����

	int timerhNum_;        //�^�C�}�[�̃n���h���ԍ�
	float moveTime_;       //�ړ�����
	float nowTime_;        //���݂̎���
						   
	int nowLookValue_;	   //���݌��Ă���l
						   
	bool isMove_;		   //�������ǂ���
	bool isFinish_;        //�I��������ǂ���
	bool isLoop_;          //���[�v���邩�ǂ���

public:

	//�R���X�g���N�^
	HermiteSplineMove();

	//�f�X�g���N�^
	~HermiteSplineMove();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns>���ݒn</returns>
	XMFLOAT3 Updata();

	/// <summary>
	/// �f�[�^�ǉ�
	/// </summary>
	/// <param name="pos">�p�X�̈ʒu</param>
	/// <param name="tangent">���ڃx�N�g��(�J�n�p�X�̍ۂ����K�v)</param>
	void AddPath(XMFLOAT3 pos, XMFLOAT3 tangent = { ZERO,ZERO,ZERO }) { pathData_.push_back({ pos,tangent }); }

	//�ŏ�����J�n
	void ReStart();

	//�J�n
	void Start() { isMove_ = true; }

	//��~
	void Stop() { isMove_ = false; }

	//�f�[�^���Z�b�g
	void ResetData() { pathData_.clear(); }

	//�I��������ǂ����擾
	bool IsFinish() { return isFinish_; }

	/// <summary>
	/// ���[�v���ǂ����ݒ�
	/// </summary>
	/// <param name="flag">true�Ȃ烋�[�v�ɐݒ�</param>
	void SetLoop(bool flag) { isLoop_ = flag; }

	/// <summary>
	/// ���[�v���ǂ����擾
	/// </summary>
	/// <returns>true�Ȃ烋�[�v</returns>
	bool IsLoop() { return isLoop_; }
};

