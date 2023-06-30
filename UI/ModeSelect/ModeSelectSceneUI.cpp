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
	pCreateUI_->LoadFileCreateStage(this, "Data/StageData/ModeSelect/ModeSelect.json");
}

//更新
void ModeSelectSceneUI::Update()
{
}

//描画
void ModeSelectSceneUI::Draw()
{
}
