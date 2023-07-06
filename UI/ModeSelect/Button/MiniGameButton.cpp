#include "MiniGameButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"

//�萔
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 0.4, ZERO, ZERO }; //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const float EASING_TIME = 1.0f;                      //�C�[�W���O����
	static const float SELECT_PICT_EASING_TIME = 0.5f;          //�I���摜�̃C�[�W���O����
}

//�R���X�g���N�^
MiniGameButton::MiniGameButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hTextPict_(-1), hSelectPict_(-1)
{
	ARGUMENT_INITIALIZE(easingSelectPict_, std::make_unique<EasingMove>());
}

//������
void MiniGameButton::ChildInitialize()
{
	//�g�����X�t�H�[���R�s�[���Ă���
	ARGUMENT_INITIALIZE(tSelectPict_, *transform_);

	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBounce);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	////////////////////////////////�摜�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(hTextPict_, ImageManager::Load("Image/ModeSelect/MiniGame_Text.png"));
	ARGUMENT_INITIALIZE(hSelectPict_, ImageManager::Load("Image/ModeSelect/MiniGame_Select.png"));
}

//�X�V
void MiniGameButton::EasingButtonChileUpdate()
{
	easingSelectPict_->Move();
}

//�`��
void MiniGameButton::ChildDraw()
{
	//�I������Ă��邩�܂������Ă���̂Ȃ�
	if (isSelect_)
	{
		ARGUMENT_INITIALIZE(tSelectPict_.position_, transform_->position_);

		//�I���摜�`��
		ImageManager::SetTransform(hSelectPict_, &tSelectPict_);
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
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 1, ZERO), SELECT_PICT_EASING_TIME, Easing::OutBack);
}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void MiniGameButton::IsButtonSelectRelease()
{
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));
}
