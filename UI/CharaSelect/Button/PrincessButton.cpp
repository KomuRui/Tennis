#include "PrincessButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../CharaSelectSceneUI.h"

//定数
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { -0.75f, -0.75f, ZERO };        //ポジションに対しての加算値
	static const XMFLOAT3 CHARA_IMAGE_DRAW_POS = { -0.4f, ZERO, ZERO };    //キャラ画像の表示位置
	static const float EASING_TIME = 0.6f;                                 //イージング時間
	static const float SELECT_PICT_EASING_TIME = 0.75f;                    //選択画像のイージング時間
}

//コンストラクタ
PrincessButton::PrincessButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hCharaPict_(-1)
{
	ARGUMENT_INITIALIZE(tCharaPict_, std::make_unique<Transform>());
}

//初期化
void PrincessButton::ChildInitialize()
{
	//選択状態に(コントローラー番号1にしておく)
	ButtonManager::SetSelect(this, 1);

	//コントローラーの選択画像のトランスフォームを変更
	((CharaSelectSceneUI*)FindObject("CharaSelectSceneUI"))->SetSelectPictTransform(*transform_, numController_);

	//イージング設定
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBack);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	//画像ロード
	ARGUMENT_INITIALIZE(hCharaPict_, ImageManager::Load("Image/CharaSelect/Princess.png"));
	tCharaPict_.get()->SetPosition(CHARA_IMAGE_DRAW_POS);
}

//更新
void PrincessButton::EasingButtonChileUpdate()
{
	//もし動いているかつイージング処理が最後まで終了しているのなら
	if (isMove_ && ((CharaSelectSceneUI*)FindObject("CharaSelectSceneUI"))->GetEasing(numController_).IsFinish())
		ARGUMENT_INITIALIZE(isMove_, false);
}

//描画
void PrincessButton::ChildDraw()
{
	//選択されているのなら
	if (isSelect_)
	{
		ImageManager::SetTransform(hCharaPict_, tCharaPict_.get());
		ImageManager::SetUi(hCharaPict_);
	}
}

//ボタンが押されたら何するか
void PrincessButton::IsButtonPush()
{
	//リセットする
	ButtonManager::Reset();
}

//ボタンが選択された瞬間に何をするか
void PrincessButton::IsButtonSelect()
{
	ARGUMENT_INITIALIZE(isMove_, true);
	((CharaSelectSceneUI*)FindObject("CharaSelectSceneUI"))->ResetEasing(transform_->position_, numController_);
}

//ボタンが選択解除された瞬間に何をするか
void PrincessButton::IsButtonSelectRelease()
{
}
