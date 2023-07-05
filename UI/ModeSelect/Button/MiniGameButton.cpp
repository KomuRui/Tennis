#include "MiniGameButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"

//�萔
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 0.4, ZERO, ZERO }; //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const float EASING_TIME = 1.0f;                      //�C�[�W���O����
}

//�R���X�g���N�^
MiniGameButton::MiniGameButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hTextPict_(-1), hSelectPict_(-1)
{}

//������
void MiniGameButton::ChildInitialize()
{

	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBounce);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	////////////////////////////////�摜�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(hTextPict_, ImageManager::Load("Image/ModeSelect/MiniGame_Text.png"));
	ARGUMENT_INITIALIZE(hSelectPict_, ImageManager::Load("Image/ModeSelect/MiniGame_Select.png"));
}

//�`��
void MiniGameButton::ChildDraw()
{
	//�I������Ă���̂Ȃ�
	if (isSelect_)
	{
		//�I���摜�`��
		ImageManager::SetTransform(hSelectPict_, transform_);
		ImageManager::SetUi(hSelectPict_);
	}

	//�����`��
	ImageManager::SetTransform(hTextPict_, transform_);
	ImageManager::SetUi(hTextPict_);
}

//�{�^���������ꂽ�牽���邩
void MiniGameButton::IsButtonPush()
{

}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void MiniGameButton::IsButtonSelect()
{
	//if (hSelectPict_ < ZERO) return;
	//ARGUMENT_INITIALIZE(hPict_, hSelectPict_);
}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void MiniGameButton::IsButtonSelectRelease()
{
	//if (hNotSelectPict_ < ZERO) return;
	//ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_);
}
