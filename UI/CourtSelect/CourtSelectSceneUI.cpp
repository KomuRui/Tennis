#include "CourtSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"

//コンストラクタ
CourtSelectSceneUI::CourtSelectSceneUI(GameObject* parent)
	: GameObject(parent, "CourtSelectSceneUI")
{
}

//初期化
void CourtSelectSceneUI::Initialize()
{
	//ロード
	pCreateImage_->LoadFileCreateStage(this, "Data/StageData/CourtSelect/CourtSelectImage.json");
}