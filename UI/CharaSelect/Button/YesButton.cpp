#include "YesButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"

//�萔
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { ZERO,-0.8f, ZERO }; //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const float EASING_TIME = 0.6f;                      //�C�[�W���O����
	static const float SELECT_PICT_EASING_TIME = 0.5f;          //�I���摜�̃C�[�W���O����
}

//�R���X�g���N�^
YesButton::YesButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hTextPict_(-1), hSelectPict_(-1)
{
	ARGUMENT_INITIALIZE(easingSelectPict_, std::make_unique<EasingMove>());
}

//������
void YesButton::ChildInitialize()
{
	//�g�����X�t�H�[���R�s�[���Ă���
	ARGUMENT_INITIALIZE(tSelectPict_, *transform_);
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));

	//�C�[�W���O�ݒ�
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	////////////////////////////////�摜�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(hTextPict_, ImageManager::Load("Image/CharaSelect/Yes_Text.png"));
	ARGUMENT_INITIALIZE(hSelectPict_, ImageManager::Load("Image/CharaSelect/Yes_Select.png"));

	//�I����Ԃ�
	//ButtonManager::SetSelect(this);
}

//�X�V
void YesButton::EasingButtonChileUpdate()
{
	easingSelectPict_->Move();
}

//�`��
void YesButton::ChildDraw()
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
void YesButton::IsButtonPush()
{
	//�{�^�����Z�b�g
	ButtonManager::Reset();

	//�X�N���[���V���b�g
	Direct3D::ScreenShoot();

	//�L�����I���V�[���ɕύX
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_COURT_SELECT);
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void YesButton::IsButtonSelect()
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 1, ZERO), SELECT_PICT_EASING_TIME, Easing::OutBack);
}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void YesButton::IsButtonSelectRelease()
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(1, 1, ZERO), XMFLOAT3(ZERO, 1, ZERO), 0.2f, Easing::OutCubic);
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));
}
