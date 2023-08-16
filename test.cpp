#include "test.h"

//コンストラクタ
test::test(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}

//初期化
void test::ChildInitialize()
{
	SetShadow(false);

	//当たり判定
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