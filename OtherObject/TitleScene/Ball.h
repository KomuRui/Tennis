#pragma once
#include "../../Base/NormalObject.h"
#include  "../../Engine/GameObject/PolyLine.h"
#include <map>

//�������̌v�Z
//https://juken-philo.com/hobutsuundo/

//�{�[���̏��
enum class BallStatus
{
	PURPOSE_MOVE, //�ړI�n�܂ňړ�
	BOUND_MOVE,   //�o�E���h�ړ�
};

/// <summary>
/// �e�j�X�{�[��
/// </summary>
class Ball : public NormalObject
{

	BallStatus ballStatus_;      //�{�[���̏��

	int hTime_;                  //�^�C�}�[�n���h��
	int hEffect_;                //�G�t�F�N�g�n���h��
	int boundCount_;             //�o�E���h�̉�
	float ratio_;			     //����(�n�_����I�_�̂ǂ��̊����ɂ��邩)
	float moveTime_;			 //�n�_����I�_�܂œ�������
	float firstAngle_;           //�������̍ŏ��̊p�x
	bool isGoToBasePoint_;       //�v���C���[�̊�_�Ɍ�������

	XMVECTOR endPointDirection_; //�I�_�܂ł̃x�N�g��
	XMVECTOR progressVector_;    //�i�s�x�N�g��

	XMFLOAT2 strength_;   //����(X��Y������)
	XMFLOAT2 v0_;		  //�����x(X��Y������)

	XMFLOAT3 startPoint_; //�{�[���̎n�_
	XMFLOAT3 endPoint_;   //�{�[���̏I�_

	PolyLine* pLine_; //�{�[���̋O�Օ`��p

public:

	//�R���X�g���N�^
	Ball(GameObject* parent, std::string modelPath, std::string name);
	Ball(GameObject* parent);

	//�f�X�g���N�^
	~Ball() {};

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//�`��
	void ChildDraw() override;

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;
	
	//////////////////////////////////�֐�///////////////////////////////////////

	/// <summary>
	/// �ړI�n�܂ňړ�
	/// </summary>
	void MoveToPurpose();

	/// <summary>
	/// �o�E���h�ړ�
	/// </summary>
	void BoundMove();

	/// <summary>
	/// ���Z�b�g(�n�_�I�_���ׂčĐݒ�)
	/// </summary>
	void Reset(float strengthX, float strengthY,float moveTime,bool isGotoPlayer,string basePpointName);

	/// <summary>
	/// �I�_�̃|�W�V�������擾
	/// </summary>
	/// <returns>�I�_�̃|�W�V����</returns>
	XMFLOAT3 GetEndPosition() { return endPoint_; }

	/// <summary>
	/// �{�[���̋O�ՐF��ݒ�
	/// </summary>
	/// <param name="color">�ݒ肵�����O�ՐF</param>
	void SetBallLineColor(XMFLOAT4 color) { pLine_->SetColor(color); }

	/// <summary>
	/// �v���C���[�̊�_�Ɍ������Ă��邩
	/// </summary>
	bool isGoToPlayerBasePoint() { return isGoToBasePoint_; }

	/// <summary>
	/// �{�[���̏�Ԃ��擾
	/// </summary>
	/// <returns>�{�[���̏��</returns>
	BallStatus GetBallStatus() { return ballStatus_; }
};

