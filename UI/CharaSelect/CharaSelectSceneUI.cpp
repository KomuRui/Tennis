#include "CharaSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//�萔
namespace
{
	static const float EASING_TIME = 0.5f; //�C�[�W���O�ɂ����鎞��
}

//�R���X�g���N�^
CharaSelectSceneUI::CharaSelectSceneUI(GameObject* parent)
	: GameObject(parent, "CharaSelectSceneUI")
{
}

//������
void CharaSelectSceneUI::Initialize()
{
	//�I������Ƃ��̃R���g���[��0,1�̉摜����
	ARGUMENT_INITIALIZE(selectPict_[0].hPict_, ImageManager::Load("Image/CharaSelect/Controller0Select.png"));
	ARGUMENT_INITIALIZE(selectPict_[0].transform_, std::make_shared<Transform>()); 
	ARGUMENT_INITIALIZE(selectPict_[0].easingSelectPict_,std::make_unique<EasingMove>());

	ARGUMENT_INITIALIZE(selectPict_[1].hPict_, ImageManager::Load("Image/CharaSelect/Controller1Select.png"));
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
	ImageManager::SetTransform(selectPict_[0].hPict_, selectPict_[0].transform_.get());
	ImageManager::SetTransform(selectPict_[1].hPict_, selectPict_[1].transform_.get());

	ImageManager::SetUi(selectPict_[0].hPict_);
	ImageManager::SetUi(selectPict_[1].hPict_);
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

