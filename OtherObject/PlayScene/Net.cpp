#include "Net.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/DirectX/Direct3D.h"

//�R���X�g���N�^
Net::Net(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}

//�����`��
void Net::TransparentDraw()
{
	//�`��
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}