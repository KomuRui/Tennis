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
		//ˆÚ“®s—ñ
		matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

		//‰ñ“]s—ñ
		XMMATRIX rotateX, rotateY, rotateZ;
		rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
		rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
		rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
		matRotate_ = rotateZ * rotateX * rotateY;

		//Šg‘åk¬
		matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	}
	else
	{
		//ˆÚ“®s—ñ
		matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

		//Šg‘åk¬
		matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	}


}

XMMATRIX Transform::GetWorldMatrix()
{
	if (!isAxisRotate_)
	{
		Calclation();

		if (parent != nullptr && parent->GetComponent<Transform>() != nullptr)
		{
			return  matScale_ * matRotate_ * matTranslate_ * parent->GetComponent<Transform>()->GetWorldMatrix();
		}

		return  matScale_ * matRotate_ * matTranslate_;
	}
	else
	{

		Calclation();

		if (parent != nullptr && parent->GetComponent<Transform>() != nullptr)
		{
			return  matScale_ * matAxisRotate_ * matTranslate_ * parent->GetComponent<Transform>()->GetWorldMatrix();
		}

		return matScale_ * matAxisRotate_ * matTranslate_;
	}

}


//e‚Ìƒ[ƒ‹ƒhs—ñ‚ðŽæ“¾
XMMATRIX Transform::GetParentWorldMatrix()
{
	if (parent == nullptr || !parent->GetComponent<Transform>()) return XMMatrixIdentity();

	return parent->GetComponent<Transform>()->GetWorldMatrix();
}

XMFLOAT3 Transform::GetWorldPosition() {
	if (parent && parent->GetComponent<Transform>())
		return Float3Add(parent->GetComponent<Transform>()->position_, position_);
	else
		return position_;
}
XMFLOAT3 Transform::GetWorldRotate() {
	if (parent && parent->GetComponent<Transform>())
		return Float3Add(parent->GetComponent<Transform>()->rotate_, rotate_);
	else
		return rotate_;
}
XMFLOAT3 Transform::GetWorldScale() {
	if (parent && parent->GetComponent<Transform>())
		return Float3Add(parent->GetComponent<Transform>()->scale_, scale_);
	else
		return scale_;
}