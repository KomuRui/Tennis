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
	pCreateUI_->LoadFileCreateStage(this, "Data/StageData/ModeSelect/ModeSelect.json");
}

//�X�V
void ModeSelectSceneUI::Update()
{
}

//�`��
void ModeSelectSceneUI::Draw()
{
}
