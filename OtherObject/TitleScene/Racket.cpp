#include "Racket.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"

//�R���X�g���N�^
Racket::Racket(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{
}

Racket::Racket(GameObject* parent)
	:NormalObject(parent, "Racket/Normal.fbx", "Racket")
{}

//������
void Racket::ChildInitialize()
{
	Model::SetBrightness(hModel_, 1.0f);

	//�|�W�V��������
	transform_.position_.x += 0.85f;
	transform_.position_.y -= 0.80f;
}