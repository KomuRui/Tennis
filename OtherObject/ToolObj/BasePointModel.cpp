#include "BasePointModel.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/DirectX/Direct3D.h"

//�R���X�g���N�^
BasePointModel::BasePointModel(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), basePointName_(""), isPlayer1CourtType_(false)
{}

BasePointModel::BasePointModel(GameObject* parent)
	:NormalObject(parent, "Tool/ToolModel/BasePosModel.fbx", "BasePointModel"), basePointName_(""), isPlayer1CourtType_(false)
{}

//������
void BasePointModel::ChildInitialize()
{
	//��_�Ƃ��Ēǉ�
	ModelManager::SetBasePointObj(hModel_,this);

	//�e
	SetShadow(false);

	//���C�̔���Ɋ܂܂��悤�ɐݒ�
	ModelManager::SetRayFlag(hModel_, true);
}

//��ڂ̃E�B���h�E�̕`��
void BasePointModel::TwoWindowDraw()
{
	if (isServeReceiveBasePoint_)
	{
		//�`��
		ModelManager::SetTransform(hModel_, transform_);
		ModelManager::Draw(hModel_);
	}
}

//�`��
void BasePointModel::Draw()
{
	if (isServeReceiveBasePoint_)
	{
		//�`��
		ModelManager::SetTransform(hModel_, transform_);
		ModelManager::Draw(hModel_);
	}
}
