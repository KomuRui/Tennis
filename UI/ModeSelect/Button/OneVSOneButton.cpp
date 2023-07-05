#include "OneVSOneButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"

//定数
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 0.8, ZERO, ZERO }; //ポジションに対しての加算値
	static const float EASING_TIME = 0.6f;                     //イージング時間
	static const float SELECT_PICT_EASING_TIME = 0.5f;         //選択画像のイージング時間
}

//コンストラクタ
OneVSOneButton::OneVSOneButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hTextPict_(-1), hSelectPict_(-1)
{
	ARGUMENT_INITIALIZE(easingSelectPict_, std::make_unique<EasingMove>());
}

//初期化
void OneVSOneButton::ChildInitialize()
{
	//トランスフォームコピーしておく
	ARGUMENT_INITIALIZE(tSelectPict_, *transform_);

	//イージング設定
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	////////////////////////////////画像の初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(hTextPict_, ImageManager::Load("Image/ModeSelect/1VS1_Text.png"));
	ARGUMENT_INITIALIZE(hSelectPict_, ImageManager::Load("Image/ModeSelect/1VS1_Select.png"));

	//選択状態に
	ButtonManager::SetSelect(this);
}

//更新
void OneVSOneButton::EasingButtonChileUpdate()
{
	easingSelectPict_->Move();
}

//描画
void OneVSOneButton::ChildDraw()
{
	//選択されているかまだ動いているのなら
	if (isSelect_)
	{
		//選択画像描画
		ImageManager::SetTransform(hSelectPict_, &tSelectPict_);
		ImageManager::SetUi(hSelectPict_);
	}

	//文字描画
	ImageManager::SetTransform(hTextPict_, transform_);
	ImageManager::SetUi(hTextPict_);
}

//ボタンが押されたら何するか
void OneVSOneButton::IsButtonPush()
{

}

//ボタンが選択された瞬間に何をするか
void OneVSOneButton::IsButtonSelect() 
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 1, ZERO), SELECT_PICT_EASING_TIME, Easing::OutBack);
}

//ボタンが選択解除された瞬間に何をするか
void OneVSOneButton::IsButtonSelectRelease() 
{ 
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));
}
