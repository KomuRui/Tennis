#include "InfoSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"

//コンストラクタ
InfoSelectSceneUI::InfoSelectSceneUI(GameObject* parent)
	: GameObject(parent, "InfoSelectSceneUI")
{
}

//初期化
void InfoSelectSceneUI::Initialize()
{
	//ロード
	pCreateImage_->LoadFileCreateStage(this, "Data/StageData/InfoSelect/InfoSelectImage.json");
	pCreateButton_->LoadFileCreateStage(this, "Data/StageData/InfoSelect/InfoSelectButton.json");
}