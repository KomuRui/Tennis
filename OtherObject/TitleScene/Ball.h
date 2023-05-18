#pragma once
#include "../../Base/NormalObject.h"
#include  "../../Engine/GameObject/PolyLine.h"
#include <map>

//�{�[����ł��̋�
enum class Type {
	FLAT,      //�t���b�g
	TOP_SPIN,  //�g�b�v�X�s��
	SLICE,     //�X���C�X
	LOB,       //���u
	MAX
};

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

	map<Type, XMFLOAT4> lineColor_; //�{�[���̌^���Ƃ̃��C���F

	BallStatus ballStatus_;      //�{�[���̏��
	Type type_;					 //�{�[���̌^

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
	void Reset(bool isGotoPlayer);

	/// <summary>
	/// �I�_�̃|�W�V�������擾
	/// </summary>
	/// <returns>�I�_�̃|�W�V����</returns>
	XMFLOAT3 GetEndPosition() { return endPoint_; }

	/// <summary>
    /// �^��ݒ�
    /// </summary>
    /// <param name="t">�ݒ肵�����^</param>
	void SetType(Type t) { type_ = t; }
};

