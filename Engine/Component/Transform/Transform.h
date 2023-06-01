#pragma once
#include "../Component.h"
#include <DirectXMath.h>

using namespace DirectX;

class GameObject;

/// <summary>
/// �g�����X�t�H�[���R���|�[�l���g
/// </summary>
class Transform : public Component
{

public:

	XMMATRIX matTranslate_;	//�ړ��s��
	XMMATRIX matRotate_;	//��]�s��	
	XMMATRIX matScale_;		//�g��s��
	XMFLOAT3 position_;		//�ʒu
	XMFLOAT3 rotate_;		//����
	XMFLOAT3 scale_;		//�g�嗦
	XMMATRIX matAxisRotate_;//����]�s��	
	bool     isAxisRotate_; //����]���g�����ǂ���

	//�R���X�g���N�^
	Transform();

	//�f�X�g���N�^
	~Transform();

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

