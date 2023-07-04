#include "OneVSOneButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"

//�萔
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 0.4, ZERO, ZERO }; //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const float EASING_TIME = 1.0f;                      //�C�[�W���O����
}

//�R���X�g���N�^
OneVSOneButton::OneVSOneButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//������
void OneVSOneButton::ChildInitialize()
{

	//�C�[�W���O�ݒ�
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBounce);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	////////////////////////////////�摜�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);
	ARGUMENT_INITIALIZE(hSelectPict_, ImageManager::Load("Image/ModeSelect/1VS1_Select.png"));

	//�I����Ԃ�
	ButtonManager::SetSelect(this);
}


//�{�^���������ꂽ�牽���邩
void OneVSOneButton::IsButtonPush()
{

}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void OneVSOneButton::IsButtonSelect() 
{
	if (hSelectPict_ < ZERO) return; 
	ARGUMENT_INITIALIZE(hPict_, hSelectPict_); 
}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void OneVSOneButton::IsButtonSelectRelease() 
{ 
	if (hNotSelectPict_ < ZERO) return;
	ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_);
}
