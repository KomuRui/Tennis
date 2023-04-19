#include "Transform.h"

Transform::Transform(): pParent_(nullptr)
{
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);
	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();
	mmRotate_ = XMMatrixIdentity();
	mFlag_ = false;
}


Transform::~Transform()
{
}

void Transform::Calclation()
{

	if(!mFlag_)
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
	if (!mFlag_)
	{
		Calclation();
		if (pParent_)
		{
			return  matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
		}

		return  matScale_ * matRotate_ * matTranslate_;
	}
	else
	{

		Calclation();

		if (pParent_)
		{
			return  matScale_ * mmRotate_  *  matTranslate_  * pParent_->GetWorldMatrix();
		}
	
		return matScale_ * mmRotate_ * matTranslate_;
	}
		
}


//�e�̃��[���h�s����擾
XMMATRIX Transform::GetParentWorldMatrix()
{
	if (pParent_ == nullptr) return XMMatrixIdentity();

	return pParent_->GetWorldMatrix();
}