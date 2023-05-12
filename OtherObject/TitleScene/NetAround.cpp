#include "NetAround.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"

//�R���X�g���N�^
NetAround::NetAround(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}

//�����`��
void NetAround::TransparentDraw()
{
	//�`��
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}