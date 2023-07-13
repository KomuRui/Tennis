#include "ButtonBase.h"
#include "../../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"

//�R���X�g���N�^
ButtonBase::ButtonBase(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent,modelPath,name), isSelect_(false), isPush_(false), isMove_(false), numController_(ZERO), beforeButtonSelectPos_(ZERO, ZERO, ZERO), isSelectNoChange_(false)
{}


//�X�V
void ButtonBase::ChildUpdate()
{
	//�����I������Ă���̂Ȃ�
	if (isSelect_)
	{
		//�ݒ肳��Ă���֐����Ăяo��
		IsButtonSelecting();
	}

	//�����I������Ă��邩�����Ă��Ȃ�����A�{�^�����������̂Ȃ�
	if (isSelect_ && !isMove_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_A, numController_))
	{
		//���ł��������ɐݒ�
		ARGUMENT_INITIALIZE(isPush_, true);

		//�ݒ肳��Ă���֐����Ăяo��
		IsButtonPush();
	}

	//�p����p
	ChildButtonUpdate();
}

//�I������Ă��邩���Z�b�g 
void ButtonBase::SetSelect(bool flag,int numController)
{
	ARGUMENT_INITIALIZE(numController_, numController);

	//�����I������Ă��Ȃ����ݒ肳���flag��true�Ȃ�
	if (!isSelect_ && flag) IsButtonSelect();

	//�����I������Ă��Đݒ肳���flag��false�Ȃ�
	if (isSelect_ && !flag) IsButtonSelectRelease();

	//�ݒ�
	ARGUMENT_INITIALIZE(isSelect_, flag);
}

//�����̂������邩�Z�b�g
void ButtonBase::SetMove(bool flag) { ARGUMENT_INITIALIZE(isMove_, flag); }