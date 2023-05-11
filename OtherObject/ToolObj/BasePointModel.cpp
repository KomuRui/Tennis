#include "BasePointModel.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"

//�R���X�g���N�^
BasePointModel::BasePointModel(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), basePointName_(""), isPlayerType_(false)
{}

BasePointModel::BasePointModel(GameObject* parent)
	:NormalObject(parent, "Tool/ToolModel/BasePosModel.fbx", "BasePointModel"), basePointName_(""), isPlayerType_(false)
{}

//������
void BasePointModel::ChildInitialize()
{
	//��_�Ƃ��Ēǉ�
	Model::SetBasePointObj(hModel_,this);

	//���C�̔���Ɋ܂܂��悤�ɐݒ�
	Model::SetRayFlag(hModel_, true);
}

//��ڂ̃E�B���h�E�̕`��
void BasePointModel::TwoWindowDraw()
{
	//�`��
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�`��
void BasePointModel::Draw()
{
	//�`��
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}
