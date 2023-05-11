#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// �e�j�X�{�[��
/// </summary>
class Ball : public NormalObject
{
	int hTime_;                  //�^�C�}�[�n���h��
	float ratio;			     //����(�n�_����I�_�̂ǂ��̊����ɂ��邩)
	float upStrength_;			 //������̋���
	float moveTime_;			 //�n�_����I�_�܂œ�������
	float v0_;					 //�����x
	XMVECTOR endPointDirection_; //�I�_�܂ł̃x�N�g��

	XMFLOAT3 startPoint_; //�{�[���̎n�_
	XMFLOAT3 endPoint_;   //�{�[���̏I�_

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
	
	//////////////////////////////////�֐�///////////////////////////////////////

	/// <summary>
	/// ���Z�b�g(�n�_�I�_���ׂčĐݒ�)
	/// </summary>
	void Reset();

};

