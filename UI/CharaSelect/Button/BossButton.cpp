#include "BossButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../CharaSelectSceneUI.h"

//�萔
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { -0.75f, -0.75f, ZERO };        //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const XMFLOAT3 CHARA_IMAGE_DRAW_POS = { -0.4f, ZERO, ZERO };    //�L�����摜�̕\���ʒu
	static const float EASING_TIME = 0.6f;                                 //�C�[�W���O����
	static const float SELECT_PICT_EASING_TIME = 0.75f;                    //�I���摜�̃C�[�W���O����
}

//�R���X�g���N�^
BossButton::BossButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hCharaPict_(-1)
{
	ARGUMENT_INITIALIZE(tCharaPict_, std::make_unique<Transform>());
}

//������
void BossButton::ChildInitialize()
{
	//�C�[�W���O�ݒ�
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBack);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	//�摜���[�h
	ARGUMENT_INITIALIZE(hCharaPict_, ImageManager::Load("Image/CharaSelect/Boss.png"));
	tCharaPict_.get()->SetPosition(CHARA_IMAGE_DRAW_POS);
}

//�X�V
void BossButton::EasingButtonChileUpdate()
{
	//���������Ă��邩�C�[�W���O�������Ō�܂ŏI�����Ă���̂Ȃ�
	if (isMove_ && ((CharaSelectSceneUI*)FindObject("CharaSelectSceneUI"))->GetEasing(numController_).IsFinish())
		ARGUMENT_INITIALIZE(isMove_, false);
}

//�`��
void BossButton::ChildDraw()
{
	//�I������Ă���̂Ȃ�
	if (isSelect_)
	{
		ImageManager::SetTransform(hCharaPict_, tCharaPict_.get());
		ImageManager::SetUi(hCharaPict_);
	}
}

//�{�^���������ꂽ�牽���邩
void BossButton::IsButtonPush()
{
	//���Z�b�g����
	ButtonManager::Reset();
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void BossButton::IsButtonSelect()
{
	ARGUMENT_INITIALIZE(isMove_, true);
	((CharaSelectSceneUI*)FindObject("CharaSelectSceneUI"))->ResetEasing(transform_->position_, numController_);
}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void BossButton::IsButtonSelectRelease()
{
}
