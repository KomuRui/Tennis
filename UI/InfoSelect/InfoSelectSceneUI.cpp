#include "InfoSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"

//�R���X�g���N�^
InfoSelectSceneUI::InfoSelectSceneUI(GameObject* parent)
	: GameObject(parent, "InfoSelectSceneUI")
{
}

//������
void InfoSelectSceneUI::Initialize()
{
	//���[�h
	pCreateImage_->LoadFileCreateStage(this, "Data/StageData/InfoSelect/InfoSelectImage.json");
	pCreateButton_->LoadFileCreateStage(this, "Data/StageData/InfoSelect/InfoSelectButton.json");
}