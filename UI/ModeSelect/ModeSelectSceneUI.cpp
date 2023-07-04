#include "ModeSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"

//�R���X�g���N�^
ModeSelectSceneUI::ModeSelectSceneUI(GameObject* parent)
	: GameObject(parent, "ModeSelectSceneUI")
{
}

//������
void ModeSelectSceneUI::Initialize()
{
	//���[�h
	pCreateImage_->LoadFileCreateStage(this, "Data/StageData/ModeSelect/ModeSelectImage.json");
	pCreateButton_->LoadFileCreateStage(this, "Data/StageData/ModeSelect/ModeSelectButton.json");
}

//�X�V
void ModeSelectSceneUI::Update()
{
}

