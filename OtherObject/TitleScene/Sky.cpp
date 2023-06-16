#include "Sky.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/DirectX/Direct3D.h"

//�R���X�g���N�^
Sky::Sky(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), scroll(ZERO)
{}

//������
void Sky::ChildInitialize()
{
	ModelManager::SetMyShadowApply(hModel_,false);
	ModelManager::SetBrightness(hModel_, 1.0f);
	SetShadow(false);
}

//�X�V
void Sky::ChildUpdate()
{
}

