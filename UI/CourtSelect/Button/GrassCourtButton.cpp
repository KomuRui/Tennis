#include "GrassCourtButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../../../OtherObject/PlayScene/TennisCourt.h"
#include "../../../Scene/CourtSelectScene/CourtSelectScene.h"

//�萔
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { -0.8f, ZERO, ZERO }; //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const float EASING_TIME = 0.6f;                       //�C�[�W���O����
	static const float SELECT_PICT_EASING_TIME = 0.5f;           //�I���摜�̃C�[�W���O����
}

//�R���X�g���N�^
GrassCourtButton::GrassCourtButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hTextPict_(-1), hSelectPict_(-1), hCourtInfoPict_(-1)
{
	ARGUMENT_INITIALIZE(easingSelectPict_, std::make_unique<EasingMove>());
}

//������
void GrassCourtButton::ChildInitialize()
{
	//�g�����X�t�H�[���R�s�[���Ă���
	ARGUMENT_INITIALIZE(tSelectPict_, *transform_);
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));

	//�C�[�W���O�ݒ�
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	////////////////////////////////�摜�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(hTextPict_, ImageManager::Load("Image/CourtSelect/Grass_Text.png"));
	ARGUMENT_INITIALIZE(hSelectPict_, ImageManager::Load("Image/CourtSelect/Grass_Select.png"));
	ARGUMENT_INITIALIZE(hCourtInfoPict_, ImageManager::Load("Image/CourtSelect/Grass_Info.png"));
}

//�X�V
void GrassCourtButton::EasingButtonChileUpdate()
{
	easingSelectPict_->Move();
}

//�`��
void GrassCourtButton::ChildDraw()
{
	//�I������Ă��邩�܂������Ă���̂Ȃ�
	if (isSelect_)
	{
		ARGUMENT_INITIALIZE(tSelectPict_.position_, transform_->position_);

		//�I���摜�`��
		ImageManager::SetTransform(hSelectPict_, &tSelectPict_);
		ImageManager::SetUi(hSelectPict_);

		//�R�[�g���摜�`��
		ImageManager::SetTransform(hCourtInfoPict_, &tCourtInfoPict_);
		ImageManager::SetUi(hCourtInfoPict_);
	}

	//�����`��
	ImageManager::SetTransform(hTextPict_, transform_);
	ImageManager::SetUi(hTextPict_);
}

//�{�^���������ꂽ�牽���邩
void GrassCourtButton::IsButtonPush()
{
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void GrassCourtButton::IsButtonSelect()
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 1, ZERO), SELECT_PICT_EASING_TIME, Easing::OutBack);

	//�J�������X�^�[�g
	((CourtSelectScene*)FindObject("CourtSelectScene"))->CameraReStart();

	//�e�j�X�R�[�g�ύX
	((TennisCourt*)FindObject("TennisCourt"))->SetTennisCourtType(TennisCourtType::GRASS_COURT);
}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void GrassCourtButton::IsButtonSelectRelease()
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(1, 1, ZERO), XMFLOAT3(ZERO, 1, ZERO), 0.2f, Easing::OutCubic);
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));
}
