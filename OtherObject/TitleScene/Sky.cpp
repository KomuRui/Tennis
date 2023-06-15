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
	ModelManager::SetShederType(hModel_, Direct3D::SHADER_NORMALMAP);
	SetShadow(false);
}

//�X�V
void Sky::ChildUpdate()
{
	//UV�X�N���[��
	scroll += 0.003f;
	ModelManager::SetUvScroll(hModel_, scroll);
}

