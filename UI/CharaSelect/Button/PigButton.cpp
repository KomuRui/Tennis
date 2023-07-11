#include "PigButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"

//定数
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 1.5f, ZERO, ZERO }; //ポジションに対しての加算値
	static const float EASING_TIME = 0.6f;                      //イージング時間
	static const float SELECT_PICT_EASING_TIME = 0.75f;          //選択画像のイージング時間
}

//コンストラクタ
PigButton::PigButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name)
{
	ARGUMENT_INITIALIZE(easingSelectPict_, std::make_unique<EasingMove>());
}

//初期化
void PigButton::ChildInitialize()
{
	//イージング設定
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBack);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));
}

//更新
void PigButton::EasingButtonChileUpdate()
{
	easingSelectPict_->Move();
}

//描画
void PigButton::ChildDraw()
{
}

//ボタンが押されたら何するか
void PigButton::IsButtonPush()
{
	//リセットする
	ButtonManager::Reset();
}

//ボタンが選択された瞬間に何をするか
void PigButton::IsButtonSelect()
{
}

//ボタンが選択解除された瞬間に何をするか
void PigButton::IsButtonSelectRelease()
{
}
