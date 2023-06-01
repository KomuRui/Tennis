#include "Transform.h"
#include "../../GameObject/GameObject.h"

Transform::Transform()
{
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);
	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();
	matAxisRotate_ = XMMatrixIdentity();
	isAxisRotate_ = false;
}


Transform::~Transform()
{
}

void Transform::Calclation()
{

	if (!isAxisRotate_)
	{
		//�ړ��s��
		matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

		//��]�s��
		XMMATRIX rotateX, rotateY, rotateZ;
		rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
		rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
		rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
		matRotate_ = rotateZ * rotateX * rotateY;

		//�g��k��
		matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	}
	else
	{
		//�ړ��s��
		matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

		//�g��k��
		matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	}


}

XMMATRIX Transform::GetWorldMatrix()
{
	if (!isAxisRotate_)
	{
		Calclation();
		if (parent && parent->GetComponent<Transform>())
		{
			return  matScale_ * matRotate_ * matTranslate_ * parent->GetComponent<Transform>()->GetWorldMatrix();
		}

		return  matScale_ * matRotate_ * matTranslate_;
	}
	else
	{

		Calclation();

		if (parent && parent->GetComponent<Transform>())
		{
			return  matScale_ * matAxisRotate_ * matTranslate_ * parent->GetComponent<Transform>()->GetWorldMatrix();
		}

		return matScale_ * matAxisRotate_ * matTranslate_;
	}

}


//�e�̃��[���h�s����擾
XMMATRIX Transform::GetParentWorldMatrix()
{
	if (parent == nullptr) return XMMatrixIdentity();

	return parent->GetComponent<Transform>()->GetWorldMatrix();
}