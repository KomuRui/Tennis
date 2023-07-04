#include "EasingButton.h"
#include "../../Engine/ResourceManager/ImageManager.h"


//�R���X�g���N�^
EasingButton::EasingButton(GameObject* parent, std::string modelPath, std::string name)
	: ButtonBase(parent, modelPath, name)
{
	ARGUMENT_INITIALIZE(easing_, std::make_unique<EasingMove>());
}

//�X�V
void EasingButton::ChildButtonUpdate()
{
	//�C�[�W���O
	easing_->Move();

	//�p���p��
	EasingButtonChileUpdate();
}