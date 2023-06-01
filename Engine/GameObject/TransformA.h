#pragma once
#include <DirectXMath.h>
#include "windowsnumerics.h"

using namespace DirectX;


//-----------------------------------------------------------
//�ʒu�A�����A�g�嗦�Ȃǂ��Ǘ�����N���X
//-----------------------------------------------------------
class TransformA
{
public:
	XMMATRIX matTranslate_;	//�ړ��s��
	XMMATRIX matRotate_;	//��]�s��	
	XMMATRIX matScale_;		//�g��s��
	XMFLOAT3 position_;		//�ʒu
	XMFLOAT3 rotate_;		//����
	XMFLOAT3 scale_;		//�g�嗦
	XMMATRIX mmRotate_;	    //���R��]�s��	
	bool     mFlag_;        //�t���O
	TransformA* pParent_;	//�e�I�u�W�F�N�g�̏��

	//�R���X�g���N�^
	TransformA();

	//�f�X�g���N�^
	~TransformA();

	//�e�s��̌v�Z
	//�����F�Ȃ�
	//�ߒl�F�Ȃ�
	void Calclation();

	//���[���h�s����擾
	//�����F�Ȃ�
	//�ߒl�F���̎��_�ł̃��[���h�s��
	XMMATRIX GetWorldMatrix();

	/// <summary>
	/// �e�̃��[���h�s����擾
	/// </summary>
	/// <returns>�e�̃��[���h�s��</returns>
	XMMATRIX GetParentWorldMatrix();
};

