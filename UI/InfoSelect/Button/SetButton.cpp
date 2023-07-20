#include "SetButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../../../OtherObject/PlayScene/Referee.h"

//定数
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 0.8f, ZERO, ZERO }; //ポジションに対しての加算値
	static const XMFLOAT2 TEXT_SIZE = { 0.8f,0.8f };            //テキストサイズ
	static const float EASING_TIME = 0.6f;                      //イージング時間
	static const float SELECT_PICT_EASING_TIME = 0.5f;          //選択画像のイージング時間
	static const int MIN_SET_NUM = 1;							//最小セット数
	static const int MAX_SET_NUM = 3;							//最大セット数
}

//コンストラクタ
SetButton::SetButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hTextPict_(-1), hSelectPict_(-1), setNum_(MIN_SET_NUM)
{
	ARGUMENT_INITIALIZE(easingSelectPict_, std::make_unique<EasingMove>());
	ARGUMENT_INITIALIZE(setNumText_, std::make_unique<Text>());
}

//初期化
void SetButton::ChildInitialize()
{
	//トランスフォームコピーしておく
	ARGUMENT_INITIALIZE(tSelectPict_, *transform_);
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));

	//テキスト設定
	setNumText_->Initialize("Text/NumberFont.png", 128, 256, 10);

	//イージング設定
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	////////////////////////////////画像の初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(hTextPict_, ImageManager::Load("Image/InfoSelect/Set_Text.png"));
	ARGUMENT_INITIALIZE(hSelectPict_, ImageManager::Load("Image/InfoSelect/Select.png"));

	//選択状態に
	ButtonManager::SetSelect(this);
}

//更新
void SetButton::EasingButtonChileUpdate()
{
	//左に傾けたのなら
	if (Input::IsPadStickLeftL() && isSelect_)
	{
		setNum_--;
		ARGUMENT_INITIALIZE(setNum_,Clamp(setNum_, MAX_SET_NUM, MIN_SET_NUM));
	}

	//右に傾けたのなら
	if (Input::IsPadStickRightL() && isSelect_)
	{
		setNum_++;
		ARGUMENT_INITIALIZE(setNum_, Clamp(setNum_, MAX_SET_NUM, MIN_SET_NUM));
	}

	//イージング移動
	easingSelectPict_->Move();
}

//描画
void SetButton::ChildDraw()
{
	//選択されているかまだ動いているのなら
	if (isSelect_)
	{
		ARGUMENT_INITIALIZE(tSelectPict_.position_, transform_->position_);

		//選択画像描画
		ImageManager::SetTransform(hSelectPict_, &tSelectPict_);
		ImageManager::SetUi(hSelectPict_);
	}

	//文字描画
	ImageManager::SetTransform(hTextPict_, transform_);
	ImageManager::SetUi(hTextPict_);

	//テキスト描画
	setNumText_->NumberDraw(0.17f,-0.24f, setNum_, TEXT_SIZE);
}

//ボタンが押されたら何するか
void SetButton::IsButtonPush()
{
	//ボタンリセット
	ButtonManager::Reset();

	//スクリーンショット
	Direct3D::ScreenShoot();

	//ゲーム数を設定
	GameManager::GetReferee()->SetnumSetFirstToGet(setNum_);

	//ゲーム情報選択シーンに変更
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_PLAY);
}

//ボタンが選択された瞬間に何をするか
void SetButton::IsButtonSelect()
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 1, ZERO), SELECT_PICT_EASING_TIME, Easing::OutBack);
}

//ボタンが選択解除された瞬間に何をするか
void SetButton::IsButtonSelectRelease()
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(1, 1, ZERO), XMFLOAT3(ZERO, 1, ZERO), 0.2f, Easing::OutCubic);
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));
}
