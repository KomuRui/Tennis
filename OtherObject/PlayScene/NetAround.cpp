#include "NetAround.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/DirectX/Direct3D.h"

//�R���X�g���N�^
NetAround::NetAround(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}

//������
void NetAround::ChildInitialize()
{
	SetShadow(false);
}

//�����`��
void NetAround::TransparentDraw()
{
	//�`��
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}