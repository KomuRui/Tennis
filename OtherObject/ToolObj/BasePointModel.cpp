#include "BasePointModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"

//�R���X�g���N�^
BasePointModel::BasePointModel(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}

BasePointModel::BasePointModel(GameObject* parent)
	:NormalObject(parent, "Tool/ToolModel/BasePosModel.fbx", "BasePointModel")
{}

//������
void BasePointModel::ChildInitialize()
{
	Model::SetAmbient(hModel_, XMFLOAT4(1.0f, ZERO, ZERO, 1.0f));
}

//��ڂ̃E�B���h�E�̕`��
void BasePointModel::TwoWindowDraw()
{
	//�`��
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}