#include "Water.h"
#include "../../Engine/ResourceManager/ModelManager.h"

//�R���X�g���N�^
Water::Water(GameObject* parent, std::string modelFilePath_, std::string name)
	:NormalObject(parent,modelFilePath_,name), scroll(ZERO)
{}

//������
void Water::ChildInitialize()
{
	//�m�[�}���}�b�v���g��
	ModelManager::SetShederType(hModel_, Direct3D::SHADER_NORMALMAP);

	SetShadow(false);
}

//�X�V
void Water::ChildUpdate()
{
	//UV�X�N���[��
	scroll += 0.008f;
	ModelManager::SetUvScroll(hModel_, scroll);
}

//��ڂ̃E�B���h�E�̕`��
void Water::TwoWindowDraw()
{
	//�`��
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}