#include "CharaSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/ImageManager.h"

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

	//選択するときのコントローラ0,1の画像準備
	selectPict_[0] = { ImageManager::Load(""), std::make_shared<Transform>() };
	selectPict_[1] = { ImageManager::Load(""), std::make_shared<Transform>() };
}

//トランスフォーム設定
void CharaSelectSceneUI::SetTransform(const Transform& t, int numController)
{
	selectPict_[numController].second.get()->SetPosition(t.position_);
	selectPict_[numController].second.get()->SetRotate(t.rotate_);
	selectPict_[numController].second.get()->SetScale(t.scale_);
}

