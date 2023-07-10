#include "CharaSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"

//コンストラクタ
CharaSelectSceneUI::CharaSelectSceneUI(GameObject* parent)
	: GameObject(parent, "CharaSelectSceneUI")
{
}

//初期化
void CharaSelectSceneUI::Initialize()
{
	//ロード
	pCreateImage_->LoadFileCreateStage(this, "Data/StageData/CharaSelect/CharaSelect.json");
}

//更新
void CharaSelectSceneUI::Update()
{
}

