#include "CharaSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/ImageManager.h"
#include "../../Manager/ButtonManager/ButtonManager.h"

//�萔
namespace
{
	static const XMFLOAT3 CHARA_IMAGE_DRAW_POS[2] = { {-0.645f, -0.15f, ZERO},{ 0.645f, -0.15f, ZERO} };//�L�����摜�̕\���ʒu
	static const float EASING_TIME = 0.12f;                                //�C�[�W���O�ɂ����鎞��
}

//�R���X�g���N�^
CharaSelectSceneUI::CharaSelectSceneUI(GameObject* parent)
	: GameObject(parent, "CharaSelectSceneUI"), isDrawConfirmationUI_(false)
{
}

//������
void CharaSelectSceneUI::Initialize()
{
	//�I������Ƃ��̃R���g���[��0,1�̉摜����
	ARGUMENT_INITIALIZE(selectPict_[0].hPict_, ImageManager::Load("Image/CharaSelect/Controller0Select.png"));
	ARGUMENT_INITIALIZE(selectPict_[0].hPictOK_, ImageManager::Load("Image/CharaSelect/Controller0Select_OK.png"));
	ARGUMENT_INITIALIZE(selectPict_[0].isOK_, false);
	ARGUMENT_INITIALIZE(selectPict_[0].transform_, std::make_shared<Transform>()); 
	ARGUMENT_INITIALIZE(selectPict_[0].easingSelectPict_,std::make_unique<EasingMove>());

	ARGUMENT_INITIALIZE(selectPict_[1].hPict_, ImageManager::Load("Image/CharaSelect/Controller1Select.png"));
	ARGUMENT_INITIALIZE(selectPict_[1].hPictOK_, ImageManager::Load("Image/CharaSelect/Controller1Select_OK.png"));
	ARGUMENT_INITIALIZE(selectPict_[1].isOK_, false);
	ARGUMENT_INITIALIZE(selectPict_[1].transform_, std::make_shared<Transform>());
	ARGUMENT_INITIALIZE(selectPict_[1].easingSelectPict_, std::make_unique<EasingMove>());
	
	//���[�h
	pCreateImage_->LoadFileCreateStage(GetParent(), "Data/StageData/CharaSelect/CharaSelect.json");

	//�e�̃��X�g�̍Ō�Ɉʒu�ւ�
	MyObjectParentListEndPush();
}

//�X�V
void CharaSelectSceneUI::Update()
{
	//�R���g���[���[�̐��������Ă�
	selectPict_[0].easingSelectPict_.get()->Move();
	selectPict_[1].easingSelectPict_.get()->Move();
}

//�`��
void CharaSelectSceneUI::Draw()
{

	if (selectPict_[0].isOK_)
	{
		ImageManager::SetTransform(selectPict_[0].hPictOK_, selectPict_[0].transform_.get());
		ImageManager::SetUi(selectPict_[0].hPictOK_);
	}
	else
	{
		ImageManager::SetTransform(selectPict_[0].hPict_, selectPict_[0].transform_.get());
		ImageManager::SetUi(selectPict_[0].hPict_);
	}

	if (selectPict_[1].isOK_)
	{
		ImageManager::SetTransform(selectPict_[1].hPictOK_, selectPict_[1].transform_.get());
		ImageManager::SetUi(selectPict_[1].hPictOK_);
	}
	else
	{
		ImageManager::SetTransform(selectPict_[1].hPict_, selectPict_[1].transform_.get());
		ImageManager::SetUi(selectPict_[1].hPict_);
	}

}

//�m�FUi��No���I�΂ꂽ��
void CharaSelectSceneUI::ConfirmationUINo()
{
	//UI�`�悵�Ă��Ȃ��ɕύX
	SetDrawConfirmationUI(false);

	//�폜
	pCreateConfirmationImage_->AllCreateStageDelete();

	//OK��Ԃ���Ȃ�����
	ARGUMENT_INITIALIZE(selectPict_[0].isOK_, false);
	ARGUMENT_INITIALIZE(selectPict_[1].isOK_, false);

	//�ۑ��{�^�������ݎg���Ă���{�^���ɕύX
	ButtonManager::KeepButtonChangeNowUseButton();
}

//�g�����X�t�H�[���ݒ�
void CharaSelectSceneUI::SetSelectPictTransform(const Transform& t, int numController)
{
	selectPict_[numController].transform_.get()->SetPosition(t.position_);
	selectPict_[numController].transform_.get()->SetRotate(t.rotate_);
	selectPict_[numController].transform_.get()->SetScale(t.scale_);
}

//�C�[�W���O���Z�b�g
void CharaSelectSceneUI::ResetEasing(const XMFLOAT3& t,int numController)
{
	selectPict_[numController].easingSelectPict_.get()->Reset(
		&selectPict_[numController].transform_.get()->position_,
		selectPict_[numController].transform_.get()->GetPosition(),
		t,
		EASING_TIME,
		Easing::InCubic
	);
}

//�L�����摜�̕\���ʒu�擾
XMFLOAT3 CharaSelectSceneUI::GetCharaPictPos(int numController)
{
	return CHARA_IMAGE_DRAW_POS[numController];
}

//OK�������ǂ����ݒ肷��
void CharaSelectSceneUI::SetIsOK(bool flag, int numController)
{ 
	//�m�F�pUI���\������Ă���̂Ȃ炱�̐�͏������Ȃ�
	if (isDrawConfirmationUI_) return;

	//flag�ݒ�
	ARGUMENT_INITIALIZE(selectPict_[numController].isOK_,flag);

	//�ǂ����OK��ԂɂȂ�����m�F�pUi��\��
	if (selectPict_[0].isOK_ && selectPict_[1].isOK_)
	{
		ARGUMENT_INITIALIZE(isDrawConfirmationUI_, true);
		ButtonManager::NowUseButtonKeepAndButtonListEmpty();
		pCreateConfirmationImage_->LoadFileCreateStage(this, "Data/StageData/CharaSelect/CharaSelectConfirmation.json");
	}
}

