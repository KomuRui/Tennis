#pragma once
#include "../ResourceManager/Global.h"
#include "../ResourceManager/Easing.h"

/// <summary>
/// �C�[�W���O�𗘗p���ėl�X�Ȉړ�������N���X
/// </summary>
class EasingMove
{
	int timerhNum_;             //�^�C�}�[�̃n���h���ԍ�
	int endEasingCount_;        //�C�[�W���O����I�����
	int beforeEndEasingCount_;  //�C�[�W���O����I�����before

	float moveTime_;            //�ړ�����
	float nowTime_;             //���݂̎���
						    
	XMFLOAT3* targetPos_;       //�ړ�������Ώۂ̃|�C���^
	XMFLOAT3 beforePos_;        //�ړ��O�̃|�W�V����
	XMFLOAT3 afterPos_;         //�ړ���̃|�W�V����

	float (*easingFunc)(float); //�g���C�[�W���O�̊֐�

	bool isSet_;                //�ݒ肵�Ă��邩�ǂ���

public:

	//�R���X�g���N�^
	EasingMove();

	//�R���X�g���N�^
	EasingMove(XMFLOAT3* targetPos, XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float));

	/// <summary>
	/// �C�[�W���O���Ȃ���ړ�
	/// </summary>
	/// <returns>�ړ����I����Ă�����true,�I����Ă��Ȃ�������false</returns>
	bool Move();

	/// <summary>
	/// ���Z�b�g����
	/// </summary>
	/// <param name="targetPos">�ړ�������Ώۂ̃|�C���^</param>
	/// <param name="beforePos">�ړ��O�̃|�W�V����</param>
	/// <param name="afterPos">�ړ���̃|�W�V����</param>
	/// <param name="moveTime">�ړ��ɂ����鎞��</param>
	/// <param name="Func">�g���C�[�W���O�֐�</param>
	void Reset(XMFLOAT3* targetPos, XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float));

	/// <summary>
	/// �C�[�W���O����I������擾
	/// </summary>
	/// <returns>�C�[�W���O�I�������</returns>
	int GetEndEasingCount() { return endEasingCount_; }

	/// <summary>
	/// �C�[�W���O�̏I������񐔂����Z�b�g
	/// </summary>
	void ResetEndEasingCount() { endEasingCount_ = 0; }
};

