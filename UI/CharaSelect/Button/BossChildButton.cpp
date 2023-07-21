#include "BossChildButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"

//定数
namespace
{
	static const XMFLOAT3 CHARA_IMAGE_POS_ADD_VALUE = { ZERO,2.0f,ZERO };  //キャラ画像の対しての加算値
	static const XMFLOAT3 POS_ADD_VALUE = {  0.75f, 0.75f, ZERO };         //ポジションに対しての加算値
	static const float EASING_TIME = 0.6f;                                 //イージング時間
	static const float SELECT_PICT_EASING_TIME = 0.75f;                    //選択画像のイージング時間
}

//コンストラクタ
BossChildButton::BossChildButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hCharaPict_(-1)
{
	ARGUMENT_INITIALIZE(tCharaPict_, std::make_unique<Transform>());
	ARGUMENT_INITIALIZE(easingCharaPict_, std::make_unique<EasingMove>());
}

//初期化
void BossChildButton::ChildInitialize()
{
	//コントローラーの選択画像のトランスフォームを変更
	ARGUMENT_INITIALIZE(charaSelectSceneUI, ((CharaSelectSceneUI*)FindObject("CharaSelectSceneUI")));

	//イージング設定
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBack);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	//画像ロード
	ARGUMENT_INITIALIZE(hCharaPict_, ImageManager::Load("Image/CharaSelect/BossChild.png"));
	tCharaPict_.get()->SetPosition(charaSelectSceneUI->GetCharaPictPos(numController_));
}

//更新
void BossChildButton::EasingButtonChileUpdate()
{
	//もし動いているかつイージング処理が最後まで終了しているのなら
	if (isMove_ && charaSelectSceneUI->GetEasing(numController_).IsFinish() && easingCharaPict_->IsFinish())
		ARGUMENT_INITIALIZE(isMove_, false);

	easingCharaPict_->Move();

	//選択した状態でBボタンを押したなら
	if (!charaSelectSceneUI->IsDrawConfirmationUI() && isSelectNoChange_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_B, numController_))
	{
		charaSelectSceneUI->SetIsOK(false, numController_);
		SetSelectNoChange(false);
	}
}

//描画
void BossChildButton::ChildDraw()
{
	//選択されているのなら
	if (isSelect_ || !easingCharaPict_->IsFinish())
	{
		ImageManager::SetTransform(hCharaPict_, tCharaPict_.get());
		ImageManager::SetUi(hCharaPict_);
	}
}

//ボタンが押されたら何するか
void BossChildButton::IsButtonPush()
{
	charaSelectSceneUI->SetIsOK(true, numController_);

	//書き込み用
	json json_object;

	//既存のデータを読み込む
	std::ifstream input_file("Data/StageData/Play/PlayObject.json");
	input_file >> json_object;
	input_file.close();

	//ファイルネーム更新
	char fileName[50] = "MainCharacter/Player_BossChild.fbx";
	if (numController_)
		json_object["Player1"]["FileName"] = fileName;
	else
		json_object["Player"]["FileName"] = fileName;

	//書き込み
	std::ofstream output_file("Data/StageData/Play/PlayObject.json");
	output_file << json_object;
	output_file.close();

	SetSelectNoChange(true);
}

//ボタンが選択された瞬間に何をするか
void BossChildButton::IsButtonSelect()
{
	ARGUMENT_INITIALIZE(isMove_, true);
	easingCharaPict_->Reset(&tCharaPict_.get()->position_, VectorToFloat3(charaSelectSceneUI->GetCharaPictPos(numController_) + CHARA_IMAGE_POS_ADD_VALUE), charaSelectSceneUI->GetCharaPictPos(numController_), EASING_TIME, Easing::InCubic);
	tCharaPict_.get()->SetPosition(VectorToFloat3(charaSelectSceneUI->GetCharaPictPos(numController_) + CHARA_IMAGE_POS_ADD_VALUE));
	charaSelectSceneUI->ResetEasing(transform_->position_, numController_);
}

//ボタンが選択解除された瞬間に何をするか
void BossChildButton::IsButtonSelectRelease()
{
	ARGUMENT_INITIALIZE(isMove_, true);
	easingCharaPict_->Reset(&tCharaPict_.get()->position_, charaSelectSceneUI->GetCharaPictPos(numController_), VectorToFloat3(charaSelectSceneUI->GetCharaPictPos(numController_) - CHARA_IMAGE_POS_ADD_VALUE), EASING_TIME, Easing::InCubic);
}
