#include "testBox.h"

//�R���X�g���N�^
testBox::testBox(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}

//������
void testBox::ChildInitialize()
{
	SetShadow(false);

	//�����蔻��
	box_ = AddComponent<BoxCollider>();
	box_->SetPos({ ZERO,ZERO,ZERO });
	box_->SetSize({ 1.0f,1.5,1.0f });
}

void testBox::ChildUpdate()
{
	if (Input::IsKey(DIK_H) && objectName_ == "testBox")
	{
		transform_->position_.x -= 0.05f;
	}
	if (Input::IsKey(DIK_F) && objectName_ == "testBox")
	{
		transform_->position_.x += 0.05f;
	}
	if (Input::IsKey(DIK_T) && objectName_ == "testBox")
	{
		transform_->position_.y += 0.05f;
	}
	if (Input::IsKey(DIK_G) && objectName_ == "testBox")
	{
		transform_->position_.y -= 0.05f;
	}
	if (Input::IsKey(DIK_C) && objectName_ == "testBox")
	{
		transform_->position_.z -= 0.05f;
	}
	if (Input::IsKey(DIK_V) && objectName_ == "testBox")
	{
		transform_->position_.z += 0.05f;
	}
	if (Input::IsKey(DIK_Z) && objectName_ == "testBox")
	{
		transform_->rotate_.z += 0.5f;
	}
	if (Input::IsKey(DIK_X) && objectName_ == "testBox")
	{
		transform_->rotate_.z -= 0.5f;
	}
}