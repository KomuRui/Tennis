#include "MainCharButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"

//�萔
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 0.8f, ZERO, ZERO }; //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const float EASING_TIME = 0.6f;                      //�C�[�W���O����
	static const float SELECT_PICT_EASING_TIME = 0.5f;          //�I���摜�̃C�[�W���O����
}

//�R���X�g���N�^
MainCharButton::MainCharButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name)
{
}

//������
void MainCharButton::ChildInitialize()
{
	//�C�[�W���O�ݒ�
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	//�I����Ԃ�
	ButtonManager::SetSelect(this);
}

//�X�V
void MainCharButton::EasingButtonChileUpdate()
{
}

//�`��
void MainCharButton::ChildDraw()
{
}

//�{�^���������ꂽ�牽���邩
void MainCharButton::IsButtonPush()
{
	//���Z�b�g����
	ButtonManager::Reset();
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void MainCharButton::IsButtonSelect()
{
}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void MainCharButton::IsButtonSelectRelease()
{
}
