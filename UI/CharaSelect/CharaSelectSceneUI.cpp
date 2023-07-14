#include "CharaSelectSceneUI.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/ImageManager.h"
#include "../../Manager/ButtonManager/ButtonManager.h"

//定数
namespace
{
	static const XMFLOAT3 CHARA_IMAGE_DRAW_POS[2] = { {-0.645f, -0.15f, ZERO},{ 0.645f, -0.15f, ZERO} };//キャラ画像の表示位置
	static const float EASING_TIME = 0.12f;                                //イージングにかける時間
}

//コンストラクタ
CharaSelectSceneUI::CharaSelectSceneUI(GameObject* parent)
	: GameObject(parent, "CharaSelectSceneUI"), isDrawConfirmationUI_(false)
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

//確認UiでNoが選ばれた時
void CharaSelectSceneUI::ConfirmationUINo()
{
	//UI描画していないに変更
	SetDrawConfirmationUI(false);

	//削除
	pCreateConfirmationImage_->AllCreateStageDelete();

	//OK状態じゃなくする
	ARGUMENT_INITIALIZE(selectPict_[0].isOK_, false);
	ARGUMENT_INITIALIZE(selectPict_[1].isOK_, false);

	//保存ボタンを現在使われているボタンに変更
	ButtonManager::KeepButtonChangeNowUseButton();
}

//トランスフォーム設定
void CharaSelectSceneUI::SetSelectPictTransform(const Transform& t, int numController)
{
	selectPict_[numController].transform_.get()->SetPosition(t.position_);
	selectPict_[numController].transform_.get()->SetRotate(t.rotate_);
	selectPict_[numController].transform_.get()->SetScale(t.scale_);
}

//イージングリセット
void CharaSelectSceneUI::ResetEasing(const XMFLOAT3& t,int numController)
{
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

//OKしたかどうか設定する
void CharaSelectSceneUI::SetIsOK(bool flag, int numController)
{ 
	//確認用UIが表示されているのならこの先は処理しない
	if (isDrawConfirmationUI_) return;

	//flag設定
	ARGUMENT_INITIALIZE(selectPict_[numController].isOK_,flag);

	//どちらもOK状態になったら確認用Uiを表示
	if (selectPict_[0].isOK_ && selectPict_[1].isOK_)
	{
		ARGUMENT_INITIALIZE(isDrawConfirmationUI_, true);
		ButtonManager::NowUseButtonKeepAndButtonListEmpty();
		pCreateConfirmationImage_->LoadFileCreateStage(this, "Data/StageData/CharaSelect/CharaSelectConfirmation.json");
	}
}

