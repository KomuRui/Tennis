#include "ButtonBase.h"
#include "../../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"

//コンストラクタ
ButtonBase::ButtonBase(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent,modelPath,name), isSelect_(false), isPush_(false), isMove_(false), numController_(ZERO), beforeButtonSelectPos_(ZERO, ZERO, ZERO), isSelectNoChange_(false)
{}


//更新
void ButtonBase::ChildUpdate()
{
	//もし選択されているのなら
	if (isSelect_)
	{
		//設定されている関数を呼び出す
		IsButtonSelecting();
	}

	//もし選択されているかつ動いていないかつAボタンを押したのなら
	if (isSelect_ && !isMove_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_A, numController_))
	{
		//一回でも押したに設定
		ARGUMENT_INITIALIZE(isPush_, true);

		//設定されている関数を呼び出す
		IsButtonPush();
	}

	//継承先用
	ChildButtonUpdate();
}

//選択されているかをセット 
void ButtonBase::SetSelect(bool flag,int numController)
{
	ARGUMENT_INITIALIZE(numController_, numController);

	//もし選択されていないかつ設定されるflagがtrueなら
	if (!isSelect_ && flag) IsButtonSelect();

	//もし選択されていて設定されるflagがfalseなら
	if (isSelect_ && !flag) IsButtonSelectRelease();

	//設定
	ARGUMENT_INITIALIZE(isSelect_, flag);
}

//押すのを許可するかセット
void ButtonBase::SetMove(bool flag) { ARGUMENT_INITIALIZE(isMove_, flag); }