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
	//選択するときのコントローラ0,1の画像準備
	selectPict_[0] = { ImageManager::Load("Image/CharaSelect/Controller0Select.png"), std::make_shared<Transform>() };
	selectPict_[1] = { ImageManager::Load("Image/CharaSelect/Controller1Select.png"), std::make_shared<Transform>() };

	//ロード
	pCreateImage_->LoadFileCreateStage(GetParent(), "Data/StageData/CharaSelect/CharaSelect.json");

	//親のリストの最後に位置替え
	MyObjectParentListEndPush();
}

//描画
void CharaSelectSceneUI::Draw()
{
	ImageManager::SetTransform(selectPict_[0].first, selectPict_[0].second.get());
	ImageManager::SetTransform(selectPict_[1].first, selectPict_[1].second.get());

	ImageManager::SetUi(selectPict_[0].first);
	ImageManager::SetUi(selectPict_[1].first);
}

//トランスフォーム設定
void CharaSelectSceneUI::SetSelectPictTransform(const Transform& t, int numController)
{
	selectPict_[numController].second.get()->SetPosition(t.position_);
	selectPict_[numController].second.get()->SetRotate(t.rotate_);
	selectPict_[numController].second.get()->SetScale(t.scale_);
}

