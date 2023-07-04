#include "ModeSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"

//コンストラクタ
ModeSelectSceneUI::ModeSelectSceneUI(GameObject* parent)
	: GameObject(parent, "ModeSelectSceneUI")
{
}

//初期化
void ModeSelectSceneUI::Initialize()
{
	//ロード
	pCreateImage_->LoadFileCreateStage(this, "Data/StageData/ModeSelect/ModeSelectImage.json");
	pCreateButton_->LoadFileCreateStage(this, "Data/StageData/ModeSelect/ModeSelectButton.json");
}

//更新
void ModeSelectSceneUI::Update()
{
}

