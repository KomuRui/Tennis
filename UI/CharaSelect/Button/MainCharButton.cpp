#include "MainCharButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../CharaSelectSceneUI.h"

//定数
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 0.75f, -0.75f, ZERO };//ポジションに対しての加算値
	static const float EASING_TIME = 0.6f;                        //イージング時間
	static const float SELECT_PICT_EASING_TIME = 0.75f;            //選択画像のイージング時間
}

//コンストラクタ
MainCharButton::MainCharButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name)
{
}

//初期化
void MainCharButton::ChildInitialize()
{
	//選択状態に
	ButtonManager::SetSelect(this);

	//コントローラーの選択画像のトランスフォームを変更
	((CharaSelectSceneUI*)FindObject("CharaSelectSceneUI"))->SetSelectPictTransform(*transform_, numController_);

	//イージング設定
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBack);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));
}

//更新
void MainCharButton::EasingButtonChileUpdate()
{
}

//描画
void MainCharButton::ChildDraw()
{
}

//ボタンが押されたら何するか
void MainCharButton::IsButtonPush()
{
	//リセットする
	ButtonManager::Reset();
}

//ボタンが選択された瞬間に何をするか
void MainCharButton::IsButtonSelect()
{
	((CharaSelectSceneUI*)FindObject("CharaSelectSceneUI"))->ResetEasing(transform_->position_, numController_);
}

//ボタンが選択解除された瞬間に何をするか
void MainCharButton::IsButtonSelectRelease()
{
}
