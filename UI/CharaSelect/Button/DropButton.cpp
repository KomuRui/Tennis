#include "DropButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../CharaSelectSceneUI.h"

//�萔
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { -1.5f, ZERO, ZERO };//�|�W�V�����ɑ΂��Ẳ��Z�l
	static const float EASING_TIME = 0.6f;                      //�C�[�W���O����
	static const float SELECT_PICT_EASING_TIME = 0.75f;          //�I���摜�̃C�[�W���O����
}

//�R���X�g���N�^
DropButton::DropButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name)
{
}

//������
void DropButton::ChildInitialize()
{
	//�C�[�W���O�ݒ�
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBack);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));
}

//�X�V
void DropButton::EasingButtonChileUpdate()
{
}

//�`��
void DropButton::ChildDraw()
{
}

//�{�^���������ꂽ�牽���邩
void DropButton::IsButtonPush()
{
	//���Z�b�g����
	ButtonManager::Reset();
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void DropButton::IsButtonSelect()
{
	((CharaSelectSceneUI*)FindObject("CharaSelectSceneUI"))->ResetEasing(transform_->position_, numController_);
}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void DropButton::IsButtonSelectRelease()
{
}
