#include "CourtSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"

//�R���X�g���N�^
CourtSelectSceneUI::CourtSelectSceneUI(GameObject* parent)
	: GameObject(parent, "CourtSelectSceneUI")
{
}

//������
void CourtSelectSceneUI::Initialize()
{
	//���[�h
	pCreateImage_->LoadFileCreateStage(this, "Data/StageData/CourtSelect/CourtSelectImage.json");
}