#include "SetButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../../../OtherObject/PlayScene/Referee.h"

//�萔
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 0.8f, ZERO, ZERO }; //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const XMFLOAT2 TEXT_SIZE = { 0.8f,0.8f };            //�e�L�X�g�T�C�Y
	static const float EASING_TIME = 0.6f;                      //�C�[�W���O����
	static const float SELECT_PICT_EASING_TIME = 0.5f;          //�I���摜�̃C�[�W���O����
	static const int MIN_SET_NUM = 1;							//�ŏ��Z�b�g��
	static const int MAX_SET_NUM = 3;							//�ő�Z�b�g��
}

//�R���X�g���N�^
SetButton::SetButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hTextPict_(-1), hSelectPict_(-1), setNum_(MIN_SET_NUM)
{
	ARGUMENT_INITIALIZE(easingSelectPict_, std::make_unique<EasingMove>());
	ARGUMENT_INITIALIZE(setNumText_, std::make_unique<Text>());
}

//������
void SetButton::ChildInitialize()
{
	//�g�����X�t�H�[���R�s�[���Ă���
	ARGUMENT_INITIALIZE(tSelectPict_, *transform_);
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));

	//�e�L�X�g�ݒ�
	setNumText_->Initialize("Text/NumberFont.png", 128, 256, 10);

	//�C�[�W���O�ݒ�
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	////////////////////////////////�摜�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(hTextPict_, ImageManager::Load("Image/InfoSelect/Set_Text.png"));
	ARGUMENT_INITIALIZE(hSelectPict_, ImageManager::Load("Image/InfoSelect/Select.png"));

	//�I����Ԃ�
	ButtonManager::SetSelect(this);
}

//�X�V
void SetButton::EasingButtonChileUpdate()
{
	//���ɌX�����̂Ȃ�
	if (Input::IsPadStickLeftL() && isSelect_)
	{
		setNum_--;
		ARGUMENT_INITIALIZE(setNum_,Clamp(setNum_, MAX_SET_NUM, MIN_SET_NUM));
	}

	//�E�ɌX�����̂Ȃ�
	if (Input::IsPadStickRightL() && isSelect_)
	{
		setNum_++;
		ARGUMENT_INITIALIZE(setNum_, Clamp(setNum_, MAX_SET_NUM, MIN_SET_NUM));
	}

	//�C�[�W���O�ړ�
	easingSelectPict_->Move();
}

//�`��
void SetButton::ChildDraw()
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

	//�e�L�X�g�`��
	setNumText_->NumberDraw(0.17f,-0.24f, setNum_, TEXT_SIZE);
}

//�{�^���������ꂽ�牽���邩
void SetButton::IsButtonPush()
{
	//�{�^�����Z�b�g
	ButtonManager::Reset();

	//�X�N���[���V���b�g
	Direct3D::ScreenShoot();

	//�Q�[������ݒ�
	GameManager::GetReferee()->SetnumSetFirstToGet(setNum_);

	//�Q�[�����I���V�[���ɕύX
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_PLAY);
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void SetButton::IsButtonSelect()
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 1, ZERO), SELECT_PICT_EASING_TIME, Easing::OutBack);
}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void SetButton::IsButtonSelectRelease()
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(1, 1, ZERO), XMFLOAT3(ZERO, 1, ZERO), 0.2f, Easing::OutCubic);
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));
}
