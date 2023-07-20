#include "GameButton.h"
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
	static const int MIN_GAME_NUM = 2;							//最小ゲーム数
	static const int MAX_GAME_NUM = 5;							//最大ゲーム数
}

//コンストラクタ
GameButton::GameButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hTextPict_(-1), hSelectPict_(-1), gameNum_(MIN_GAME_NUM)
{
	ARGUMENT_INITIALIZE(easingSelectPict_, std::make_unique<EasingMove>());
	ARGUMENT_INITIALIZE(gameNumText_, std::make_unique<Text>());
}

//初期化
void GameButton::ChildInitialize()
{
	//トランスフォームコピーしておく
	ARGUMENT_INITIALIZE(tSelectPict_, *transform_);
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));

	//テキスト設定
	gameNumText_->Initialize("Text/NumberFont.png", 128, 256, 10);

	//イージング設定
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	////////////////////////////////画像の初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(hTextPict_, ImageManager::Load("Image/InfoSelect/Game_Text.png"));
	ARGUMENT_INITIALIZE(hSelectPict_, ImageManager::Load("Image/InfoSelect/Select.png"));

	//選択状態に
	ButtonManager::SetSelect(this);
}

//更新
void GameButton::EasingButtonChileUpdate()
{
	//左に傾けたのなら
	if (Input::IsPadStickLeftL() && isSelect_)
	{
		gameNum_--;
		ARGUMENT_INITIALIZE(gameNum_,Clamp(gameNum_, MAX_GAME_NUM, MIN_GAME_NUM));
	}

	//右に傾けたのなら
	if (Input::IsPadStickRightL() && isSelect_)
	{
		gameNum_++;
		ARGUMENT_INITIALIZE(gameNum_, Clamp(gameNum_, MAX_GAME_NUM, MIN_GAME_NUM));
	}

	//イージング移動
	easingSelectPict_->Move();
}

//描画
void GameButton::ChildDraw()
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
	gameNumText_->NumberDraw(0.17f, 0.16f, gameNum_, TEXT_SIZE);
}

//ボタンが押されたら何するか
void GameButton::IsButtonPush()
{
	//ボタンリセット
	ButtonManager::Reset();

	//スクリーンショット
	Direct3D::ScreenShoot();

	//ゲーム数を設定
	GameManager::GetReferee()->SetnumGameFirstToGet(gameNum_);

	//ゲーム情報選択シーンに変更
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_PLAY);
}

//ボタンが選択された瞬間に何をするか
void GameButton::IsButtonSelect()
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 1, ZERO), SELECT_PICT_EASING_TIME, Easing::OutBack);
}

//ボタンが選択解除された瞬間に何をするか
void GameButton::IsButtonSelectRelease()
{
	easingSelectPict_->Reset(&tSelectPict_.scale_, XMFLOAT3(1, 1, ZERO), XMFLOAT3(ZERO, 1, ZERO), 0.2f, Easing::OutCubic);
	ARGUMENT_INITIALIZE(tSelectPict_.scale_, XMFLOAT3(ZERO, 1, ZERO));
}
