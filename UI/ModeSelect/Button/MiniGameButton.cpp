#include "MiniGameButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"

//定数
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 0.4, ZERO, ZERO }; //ポジションに対しての加算値
	static const float EASING_TIME = 1.0f;                      //イージング時間
}

//コンストラクタ
MiniGameButton::MiniGameButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hTextPict_(-1), hSelectPict_(-1)
{}

//初期化
void MiniGameButton::ChildInitialize()
{

	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBounce);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	////////////////////////////////画像の初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(hTextPict_, ImageManager::Load("Image/ModeSelect/MiniGame_Text.png"));
	ARGUMENT_INITIALIZE(hSelectPict_, ImageManager::Load("Image/ModeSelect/MiniGame_Select.png"));
}

//描画
void MiniGameButton::ChildDraw()
{
	//選択されているのなら
	if (isSelect_)
	{
		//選択画像描画
		ImageManager::SetTransform(hSelectPict_, transform_);
		ImageManager::SetUi(hSelectPict_);
	}

	//文字描画
	ImageManager::SetTransform(hTextPict_, transform_);
	ImageManager::SetUi(hTextPict_);
}

//ボタンが押されたら何するか
void MiniGameButton::IsButtonPush()
{

}

//ボタンが選択された瞬間に何をするか
void MiniGameButton::IsButtonSelect()
{
	//if (hSelectPict_ < ZERO) return;
	//ARGUMENT_INITIALIZE(hPict_, hSelectPict_);
}

//ボタンが選択解除された瞬間に何をするか
void MiniGameButton::IsButtonSelectRelease()
{
	//if (hNotSelectPict_ < ZERO) return;
	//ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_);
}
