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

	/////////////////////////////////////�Z�b�^�[�E�Q�b�^�[//////////////////////////////////////////

	XMFLOAT3 GetPosition() { return position_; }
	XMFLOAT3 GetRotate() { return rotate_; }
	XMFLOAT3 GetScale() { return scale_; }
	XMFLOAT3 GetWorldPosition() { 
		if (parent && parent->GetComponent<Transform>())
			return Float3Add(parent->GetComponent<Transform>()->position_, position_);
		else
			return position_;
	}
	XMFLOAT3 GetWorldRotate() {
		if (parent && parent->GetComponent<Transform>())
			return Float3Add(parent->GetComponent<Transform>()->rotate_, rotate_);
		else
			return rotate_;
	}
	XMFLOAT3 GetWorldScale() { 
		if (parent && parent->GetComponent<Transform>())
			return Float3Add(parent->GetComponent<Transform>()->scale_, scale_);
		else
			return scale_;
	}
	Transform* GetTransform() { return this; }
	void SetPosition(XMFLOAT3 position) { position_ = position; }
	void SetPosition(float x, float y, float z) { SetPosition(XMFLOAT3(x, y, z)); }
	void SetPositionX(float x) { SetPosition(x, position_.y, position_.z); }
	void SetPositionY(float y) { SetPosition(position_.x, y, position_.z); }
	void SetPositionZ(float z) { SetPosition(position_.x, position_.y, z); }
	void SetRotate(XMFLOAT3 rotate) { rotate_ = rotate; }
	void SetRotate(float x, float y, float z) { SetRotate(XMFLOAT3(x, y, z)); }
	void SetRotateX(float x) { SetRotate(x, rotate_.y, rotate_.z); }
	void SetRotateY(float y) { SetRotate(rotate_.x, y, rotate_.z); }
	void SetRotateZ(float z) { SetRotate(rotate_.x, rotate_.y, z); }
	void SetScale(XMFLOAT3 scale) { scale_ = scale; }
	void SetScale(float x, float y, float z) { SetScale(XMFLOAT3(x, y, z)); }
};

