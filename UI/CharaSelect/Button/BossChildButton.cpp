#include "BossChildButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"

//定数
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 0.8f, ZERO, ZERO }; //ポジションに対しての加算値
	static const float EASING_TIME = 0.6f;                      //イージング時間
	static const float SELECT_PICT_EASING_TIME = 0.5f;          //選択画像のイージング時間
}

//コンストラクタ
BossChildButton::BossChildButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name)
{
}

//初期化
void BossChildButton::ChildInitialize()
{
	//イージング設定
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));
}

//更新
void BossChildButton::EasingButtonChileUpdate()
{
}

//描画
void BossChildButton::ChildDraw()
{
}

//ボタンが押されたら何するか
void BossChildButton::IsButtonPush()
{
	//リセットする
	ButtonManager::Reset();
}

//ボタンが選択された瞬間に何をするか
void BossChildButton::IsButtonSelect()
{
}

//ボタンが選択解除された瞬間に何をするか
void BossChildButton::IsButtonSelectRelease()
{
}
