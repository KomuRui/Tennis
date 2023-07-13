#include "CharaSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//定数
namespace
{
	static const XMFLOAT3 CHARA_IMAGE_DRAW_POS[2] = { {-0.645f, -0.15f, ZERO},{ 0.645f, -0.15f, ZERO} };//キャラ画像の表示位置
	static const float EASING_TIME = 0.12f;                                //イージングにかける時間
}

//コンストラクタ
CharaSelectSceneUI::CharaSelectSceneUI(GameObject* parent)
	: GameObject(parent, "CharaSelectSceneUI")
{
}

//初期化
void CharaSelectSceneUI::Initialize()
{
	//選択するときのコントローラ0,1の画像準備
	ARGUMENT_INITIALIZE(selectPict_[0].hPict_, ImageManager::Load("Image/CharaSelect/Controller0Select.png"));
	ARGUMENT_INITIALIZE(selectPict_[0].hPictOK_, ImageManager::Load("Image/CharaSelect/Controller0Select_OK.png"));
	ARGUMENT_INITIALIZE(selectPict_[0].isOK_, false);
	ARGUMENT_INITIALIZE(selectPict_[0].transform_, std::make_shared<Transform>()); 
	ARGUMENT_INITIALIZE(selectPict_[0].easingSelectPict_,std::make_unique<EasingMove>());

	ARGUMENT_INITIALIZE(selectPict_[1].hPict_, ImageManager::Load("Image/CharaSelect/Controller1Select.png"));
	ARGUMENT_INITIALIZE(selectPict_[1].hPictOK_, ImageManager::Load("Image/CharaSelect/Controller1Select_OK.png"));
	ARGUMENT_INITIALIZE(selectPict_[1].isOK_, false);
	ARGUMENT_INITIALIZE(selectPict_[1].transform_, std::make_shared<Transform>());
	ARGUMENT_INITIALIZE(selectPict_[1].easingSelectPict_, std::make_unique<EasingMove>());
	
	//ロード
	pCreateImage_->LoadFileCreateStage(GetParent(), "Data/StageData/CharaSelect/CharaSelect.json");

	//親のリストの最後に位置替え
	MyObjectParentListEndPush();
}

//更新
void CharaSelectSceneUI::Update()
{
	//コントローラーの数分だけ呼ぶ
	selectPict_[0].easingSelectPict_.get()->Move();
	selectPict_[1].easingSelectPict_.get()->Move();
}

//描画
void CharaSelectSceneUI::Draw()
{

	if (selectPict_[0].isOK_)
	{
		ImageManager::SetTransform(selectPict_[0].hPictOK_, selectPict_[0].transform_.get());
		ImageManager::SetUi(selectPict_[0].hPictOK_);
	}
	else
	{
		ImageManager::SetTransform(selectPict_[0].hPict_, selectPict_[0].transform_.get());
		ImageManager::SetUi(selectPict_[0].hPict_);
	}

	if (selectPict_[1].isOK_)
	{
		ImageManager::SetTransform(selectPict_[1].hPictOK_, selectPict_[1].transform_.get());
		ImageManager::SetUi(selectPict_[1].hPictOK_);
	}
	else
	{
		ImageManager::SetTransform(selectPict_[1].hPict_, selectPict_[1].transform_.get());
		ImageManager::SetUi(selectPict_[1].hPict_);
	}

}

//トランスフォーム設定
void CharaSelectSceneUI::SetSelectPictTransform(const Transform& t, int numController)
{
	if (selectPict_[numController].isOK_) return;

	selectPict_[numController].transform_.get()->SetPosition(t.position_);
	selectPict_[numController].transform_.get()->SetRotate(t.rotate_);
	selectPict_[numController].transform_.get()->SetScale(t.scale_);
}

//イージングリセット
void CharaSelectSceneUI::ResetEasing(const XMFLOAT3& t,int numController)
{
	if (selectPict_[numController].isOK_) return;

	selectPict_[numController].easingSelectPict_.get()->Reset(
		&selectPict_[numController].transform_.get()->position_,
		selectPict_[numController].transform_.get()->GetPosition(),
		t,
		EASING_TIME,
		Easing::InCubic
	);
}

//キャラ画像の表示位置取得
XMFLOAT3 CharaSelectSceneUI::GetCharaPictPos(int numController)
{
	return CHARA_IMAGE_DRAW_POS[numController];
}

