#include "test.h"

//�R���X�g���N�^
test::test(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}

//������
void test::ChildInitialize()
{
	SetShadow(false);

	//�����蔻��
	sphere_ = AddComponent<SphereCollider>();
	sphere_->SetPos({ ZERO,ZERO,ZERO });
	sphere_->SetSize({ 1.5,1.5,1.5 });
}

void test::ChildUpdate()
{
	if (Input::IsKey(DIK_D) && objectName_ == "test2")
	{
		transform_->position_.x -= 0.05f;
	}
	if (Input::IsKey(DIK_A) && objectName_ == "test2")
	{
		transform_->position_.x += 0.05f;
	}
	if (Input::IsKey(DIK_W) && objectName_ == "test2")
	{
		transform_->position_.y += 0.05f;
	}
	if (Input::IsKey(DIK_S) && objectName_ == "test2")
	{
		transform_->position_.y -= 0.05f;
	}
}