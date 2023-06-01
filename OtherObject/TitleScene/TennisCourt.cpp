#include "TennisCourt.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"

//�R���X�g���N�^
TennisCourt::TennisCourt(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent,modelPath,name)
{}

//������
void TennisCourt::ChildInitialize()
{
	SetShadow(false);
}

//��ڂ̃E�B���h�E�̕`��
void TennisCourt::TwoWindowDraw()
{
	//�`��
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}
