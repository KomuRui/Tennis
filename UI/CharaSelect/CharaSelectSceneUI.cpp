#include "CharaSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"

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
}

//�X�V
void CharaSelectSceneUI::Update()
{
}

