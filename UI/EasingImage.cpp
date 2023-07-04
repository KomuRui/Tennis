#include "EasingImage.h"
#include "../Engine/ResourceManager/ImageManager.h"


//�R���X�g���N�^
EasingImage::EasingImage(GameObject* parent, std::string modelPath, std::string name)
	: ImageBase(parent, modelPath, name)
{
	ARGUMENT_INITIALIZE(easing_, std::make_unique<EasingMove>());
}

//�X�V
void EasingImage::ChildUpdate()
{
	//�C�[�W���O
	easing_->Move();

	//�p���p��
	EasingImageChileUpdate();
}