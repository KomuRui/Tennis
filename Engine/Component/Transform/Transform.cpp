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

		if (parent && parent->GetParent() && parent->GetParent()->GetComponent<Transform>())
		{
			return  matScale_ * matRotate_ * matTranslate_ * parent->GetParent()->GetComponent<Transform>()->GetWorldMatrix();
		}

		return  matScale_ * matRotate_ * matTranslate_;
	}
	else
	{

		Calclation();

		if (parent && parent->GetParent() && parent->GetParent()->GetComponent<Transform>())
		{
			return  matScale_ * matAxisRotate_ * matTranslate_ * parent->GetParent()->GetComponent<Transform>()->GetWorldMatrix();
		}

		return matScale_ * matAxisRotate_ * matTranslate_;
	}

}

//�g�����X�t�H�[����ݒ�
void Transform::SetTransform(Transform* t) { *parent->GetComponent<Transform>() = *t; }


//�e�̃��[���h�s����擾
XMMATRIX Transform::GetParentWorldMatrix()
{
	if (!parent || !parent->GetParent() || !parent->GetParent()->GetComponent<Transform>()) return XMMatrixIdentity();

	return parent->GetParent()->GetComponent<Transform>()->GetWorldMatrix();
}

XMFLOAT3 Transform::GetWorldPosition() {
	if (parent && parent->GetParent() && parent->GetParent()->GetComponent<Transform>())
		return Float3Add(parent->GetParent()->GetComponent<Transform>()->position_, position_);
	else
		return position_;
}
XMFLOAT3 Transform::GetWorldRotate() {
	if (parent && parent->GetParent() && parent->GetParent()->GetComponent<Transform>())
		return Float3Add(parent->GetParent()->GetComponent<Transform>()->rotate_, rotate_);
	else
		return rotate_;
}
XMFLOAT3 Transform::GetWorldScale() {
	if (parent && parent->GetParent() && parent->GetParent()->GetComponent<Transform>())
		return Float3Add(parent->GetParent()->GetComponent<Transform>()->scale_, scale_);
	else
		return scale_;
}

XMMATRIX Transform::GetWorldRotateMatrix()
{
	Calclation();

	if (parent && parent->GetParent() && parent->GetParent()->GetComponent<Transform>())
	{
		return  matRotate_ * parent->GetParent()->GetComponent<Transform>()->GetWorldRotateMatrix();
	}

	return  matRotate_;
}