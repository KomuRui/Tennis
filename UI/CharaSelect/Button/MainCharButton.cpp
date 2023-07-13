#include "MainCharButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"

//定数
namespace
{
	static const XMFLOAT3 CHARA_IMAGE_POS_ADD_VALUE = { ZERO,2.0f,ZERO };  //キャラ画像の対しての加算値
	static const XMFLOAT3 POS_ADD_VALUE = { 0.75f, -0.75f, ZERO };         //ポジションに対しての加算値
	static const float EASING_TIME = 0.6f;                                 //イージング時間
	static const float SELECT_PICT_EASING_TIME = 0.75f;                    //選択画像のイージング時間
}

//コンストラクタ
MainCharButton::MainCharButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hCharaPict_(-1)
{
	ARGUMENT_INITIALIZE(tCharaPict_, std::make_unique<Transform>());
	ARGUMENT_INITIALIZE(easingCharaPict_, std::make_unique<EasingMove>());
}

//初期化
void MainCharButton::ChildInitialize()
{
	//コントローラーの選択画像のトランスフォームを変更
	ARGUMENT_INITIALIZE(charaSelectSceneUI, ((CharaSelectSceneUI*)FindObject("CharaSelectSceneUI")));

	//選択状態に
	ButtonManager::SetSelect(this);

	//コントローラーの選択画像のトランスフォームを変更
	charaSelectSceneUI->SetSelectPictTransform(*transform_, numController_);

	//イージング設定
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBack);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	//画像ロード
	ARGUMENT_INITIALIZE(hCharaPict_, ImageManager::Load("Image/CharaSelect/MainChar.png"));
	tCharaPict_.get()->SetPosition(charaSelectSceneUI->GetCharaPictPos(numController_));
}

//更新
void MainCharButton::EasingButtonChileUpdate()
{
	//もし動いているかつイージング処理が最後まで終了しているのなら
	if (isMove_ && charaSelectSceneUI->GetEasing(numController_).IsFinish())
		ARGUMENT_INITIALIZE(isMove_, false);

	easingCharaPict_->Move();
}

//描画
void MainCharButton::ChildDraw()
{
	//選択されているのなら
	if (isSelect_)
	{
		ImageManager::SetTransform(hCharaPict_, tCharaPict_.get());
		ImageManager::SetUi(hCharaPict_);
	}
}

//ボタンが押されたら何するか
void MainCharButton::IsButtonPush()
{
	charaSelectSceneUI->SetIsOK(true, numController_);
	SetSelectNoChange(true);
}

//ボタンが選択された瞬間に何をするか
void MainCharButton::IsButtonSelect()
{
	ARGUMENT_INITIALIZE(isMove_, true);
	easingCharaPict_->Reset(&tCharaPict_.get()->position_, VectorToFloat3(charaSelectSceneUI->GetCharaPictPos(numController_) + CHARA_IMAGE_POS_ADD_VALUE), charaSelectSceneUI->GetCharaPictPos(numController_), EASING_TIME, Easing::InCubic);
	tCharaPict_.get()->SetPosition(VectorToFloat3(charaSelectSceneUI->GetCharaPictPos(numController_) + CHARA_IMAGE_POS_ADD_VALUE));
	charaSelectSceneUI->ResetEasing(transform_->position_, numController_);
}

//ボタンが選択解除された瞬間に何をするか
void MainCharButton::IsButtonSelectRelease()
{
}
