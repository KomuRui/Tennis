#pragma once
#include "../../Base/NormalObject.h"
#include  "../../Engine/GameObject/PolyLine.h"

/// <summary>
/// �e�j�X�{�[��
/// </summary>
class Ball : public NormalObject
{
	int hTime_;                  //�^�C�}�[�n���h��
	float ratio;			     //����(�n�_����I�_�̂ǂ��̊����ɂ��邩)
	float strengthY_;			 //������̋���Y
	float strengthX_;			 //������̋���X
	float moveTime_;			 //�n�_����I�_�܂œ�������
	float vY0_;					 //�����xY
	float vX0_;					 //�����xX
	XMVECTOR endPointDirection_; //�I�_�܂ł̃x�N�g��

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
	/// ���Z�b�g(�n�_�I�_���ׂčĐݒ�)
	/// </summary>
	void Reset();

};

