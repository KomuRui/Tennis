#include "PrincessButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../CharaSelectSceneUI.h"

//�萔
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { -0.75f, -0.75f, ZERO }; //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const float EASING_TIME = 0.6f;                          //�C�[�W���O����
	static const float SELECT_PICT_EASING_TIME = 0.75f;              //�I���摜�̃C�[�W���O����
}

//�R���X�g���N�^
PrincessButton::PrincessButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name)
{
	ARGUMENT_INITIALIZE(easingSelectPict_, std::make_unique<EasingMove>());
}

//������
void PrincessButton::ChildInitialize()
{
	//�I����Ԃ�(�R���g���[���[�ԍ�1�ɂ��Ă���)
	ButtonManager::SetSelect(this, 1);

	//�R���g���[���[�̑I���摜�̃g�����X�t�H�[����ύX
	((CharaSelectSceneUI*)FindObject("CharaSelectSceneUI"))->SetSelectPictTransform(*transform_, numController_);

	//�C�[�W���O�ݒ�
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBack);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));
}

//�X�V
void PrincessButton::EasingButtonChileUpdate()
{
	easingSelectPict_->Move();
}

//�`��
void PrincessButton::ChildDraw()
{
}

//�{�^���������ꂽ�牽���邩
void PrincessButton::IsButtonPush()
{
	//���Z�b�g����
	ButtonManager::Reset();
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void PrincessButton::IsButtonSelect()
{
}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void PrincessButton::IsButtonSelectRelease()
{
}
