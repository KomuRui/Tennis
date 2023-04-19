#include "ButtonBase.h"
#include "../../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"

//�R���X�g���N�^
ButtonBase::ButtonBase(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent,modelPath,name), isSelect_(false), isPush_(false), isPushOk_(true)
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

	//�����I������Ă��邩�v�b�V��Ok�ɂȂ��Ă��邩��A�{�^�����������̂Ȃ�
	if (isSelect_ && isPushOk_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//�N���b�N��
		OtherAudioManager::ClickAudio();

		//���ł��������ɐݒ�
		ARGUMENT_INITIALIZE(isPush_, true);

		//�ݒ肳��Ă���֐����Ăяo��
		IsButtonPush();
	}

	//�p����p
	ChildButtonUpdate();
}

//�I������Ă��邩���Z�b�g 
void ButtonBase::SetSelect(bool flag)
{
	//�����I������Ă��Ȃ����ݒ肳���flag��true�Ȃ�
	if (!isSelect_ && flag) IsButtonSelect();

	//�����I������Ă��Đݒ肳���flag��false�Ȃ�
	if (isSelect_ && !flag) IsButtonSelectRelease();

	//�ݒ�
	ARGUMENT_INITIALIZE(isSelect_, flag);
}

//�����̂������邩�Z�b�g
void ButtonBase::SetPushOk(bool flag) { ARGUMENT_INITIALIZE(isPushOk_, flag); }