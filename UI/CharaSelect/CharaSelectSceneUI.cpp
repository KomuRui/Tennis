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
	//���[�h
	pCreateImage_->LoadFileCreateStage(this, "Data/StageData/CharaSelect/CharaSelect.json");

	//�I������Ƃ��̃R���g���[��0,1�̉摜����
	selectPict_[0] = { ImageManager::Load(""), std::make_shared<Transform>() };
	selectPict_[1] = { ImageManager::Load(""), std::make_shared<Transform>() };
}

//�g�����X�t�H�[���ݒ�
void CharaSelectSceneUI::SetTransform(const Transform& t, int numController)
{
	selectPict_[numController].second.get()->SetPosition(t.position_);
	selectPict_[numController].second.get()->SetRotate(t.rotate_);
	selectPict_[numController].second.get()->SetScale(t.scale_);
}

