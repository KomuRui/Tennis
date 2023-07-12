#include "CharaSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//�R���X�g���N�^
CharaSelectSceneUI::CharaSelectSceneUI(GameObject* parent)
	: GameObject(parent, "CharaSelectSceneUI")
{
}

//������
void CharaSelectSceneUI::Initialize()
{
	//�I������Ƃ��̃R���g���[��0,1�̉摜����
	selectPict_[0] = { ImageManager::Load("Image/CharaSelect/Controller0Select.png"), std::make_shared<Transform>() };
	selectPict_[1] = { ImageManager::Load("Image/CharaSelect/Controller1Select.png"), std::make_shared<Transform>() };

	//���[�h
	pCreateImage_->LoadFileCreateStage(GetParent(), "Data/StageData/CharaSelect/CharaSelect.json");

	//�e�̃��X�g�̍Ō�Ɉʒu�ւ�
	MyObjectParentListEndPush();
}

//�`��
void CharaSelectSceneUI::Draw()
{
	ImageManager::SetTransform(selectPict_[0].first, selectPict_[0].second.get());
	ImageManager::SetTransform(selectPict_[1].first, selectPict_[1].second.get());

	ImageManager::SetUi(selectPict_[0].first);
	ImageManager::SetUi(selectPict_[1].first);
}

//�g�����X�t�H�[���ݒ�
void CharaSelectSceneUI::SetSelectPictTransform(const Transform& t, int numController)
{
	selectPict_[numController].second.get()->SetPosition(t.position_);
	selectPict_[numController].second.get()->SetRotate(t.rotate_);
	selectPict_[numController].second.get()->SetScale(t.scale_);
}

