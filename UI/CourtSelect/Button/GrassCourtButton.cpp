#include "GrassCourtButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../../../OtherObject/PlayScene/TennisCourt.h"
#include "../../../Scene/CourtSelectScene/CourtSelectScene.h"

//定数
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { -0.8f, ZERO, ZERO }; //ポジションに対しての加算値
	static const float EASING_TIME = 0.6f;                       //イージング時間
	static const float SELECT_PICT_EASING_TIME = 0.5f;           //選択画像のイージング時間
}

//コンストラクタ
GrassCourtButton::GrassCourtButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hTextPict_(-1), hSelectPict_(-1), hCourtInfoPict_(-1)
{
	ARGUMENT_INITIALIZE(easingSelectPict_, std::make_unique<EasingMove>());
}

//初期化
void GrassCourtButton::ChildInitialize()
{
	//トランスフォームコピーしておく
	ARGUMENT_INITIALIZE(tSelectPict_, *transform_);
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));

	//イージング設定
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	////////////////////////////////画像の初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(hTextPict_, ImageManager::Load("Image/CourtSelect/Grass_Text.png"));
	ARGUMENT_INITIALIZE(hSelectPict_, ImageManager::Load("Image/CourtSelect/Grass_Select.png"));
	ARGUMENT_INITIALIZE(hCourtInfoPict_, ImageManager::Load("Image/CourtSelect/Grass_Info.png"));
}

//更新
void GrassCourtButton::EasingButtonChileUpdate()
{
	easingSelectPict_->Move();
}

//描画
void GrassCourtButton::ChildDraw()
{
	//選択されているかまだ動いているのなら
	if (isSelect_)
	{
		ARGUMENT_INITIALIZE(tSelectPict_.position_, transform_->position_);

		//選択画像描画
		ImageManager::SetTransform(hSelectPict_, &tSelectPict_);
		ImageManager::SetUi(hSelectPict_);

		//コート情報画像描画
		ImageManager::SetTransform(hCourtInfoPict_, &tCourtInfoPict_);
		ImageManager::SetUi(hCourtInfoPict_);
	}

	//文字描画
	ImageManager::SetTransform(hTextPict_, transform_);
	ImageManager::SetUi(hTextPict_);
}

//ボタンが押されたら何するか
void GrassCourtButton::IsButtonPush()
{
}

//ボタンが選択された瞬間に何をするか
void GrassCourtButton::IsButtonSelect()
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 1, ZERO), SELECT_PICT_EASING_TIME, Easing::OutBack);

	//カメラリスタート
	((CourtSelectScene*)FindObject("CourtSelectScene"))->CameraReStart();

	//テニスコート変更
	((TennisCourt*)FindObject("TennisCourt"))->SetTennisCourtType(TennisCourtType::GRASS_COURT);
}

//ボタンが選択解除された瞬間に何をするか
void GrassCourtButton::IsButtonSelectRelease()
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(1, 1, ZERO), XMFLOAT3(ZERO, 1, ZERO), 0.2f, Easing::OutCubic);
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));
}
