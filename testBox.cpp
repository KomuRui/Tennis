#include "testBox.h"

//コンストラクタ
testBox::testBox(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}

//初期化
void testBox::ChildInitialize()
{
	SetShadow(false);

	//当たり判定
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
}