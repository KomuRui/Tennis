#include "Water.h"
#include "../../Engine/ResourceManager/Model.h"

//�R���X�g���N�^
Water::Water(GameObject* parent, std::string modelFilePath_, std::string name)
	:NormalObject(parent,modelFilePath_,name), scroll(ZERO)
{}

//������
void Water::ChildInitialize()
{
	//�m�[�}���}�b�v���g��
	Model::SetShederType(hModel_, Direct3D::SHADER_NORMALMAP);
}

//�X�V
void Water::ChildUpdate()
{
	//UV�X�N���[��
	scroll += 0.008f;
	Model::SetUvScroll(hModel_, scroll);
}