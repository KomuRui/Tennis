#pragma once
#include "../../Base/NormalObject.h"
#include  "../../Engine/GameObject/PolyLine.h"

/// <summary>
/// �e�j�X�{�[��
/// </summary>
class Ball : public NormalObject
{
	//�{�[���̏��
	enum class BallStatus
	{
		PURPOSE_MOVE, //�ړI�n�܂ňړ�
		BOUND_MOVE,   //�o�E���h�ړ�
	};

	BallStatus ballStatus_;      //�{�[���̏��

	int hTime_;                  //�^�C�}�[�n���h��
	int hEffect_;                //�G�t�F�N�g�n���h��
	float ratio_;			     //����(�n�_����I�_�̂ǂ��̊����ɂ��邩)
	float moveTime_;			 //�n�_����I�_�܂œ�������
	bool flag;

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
	void Reset();

};

