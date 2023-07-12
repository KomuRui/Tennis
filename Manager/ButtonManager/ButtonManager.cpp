#include "ButtonManager.h"
#include "../../UI/Button/ButtonBase.h"
#include "../../Engine/ResourceManager/Global.h"
#include "../AudioManager/OtherAudioManager/OtherAudioManager.h"
#include <vector>
#include<algorithm>


//�萔
namespace
{
	static const float PAD_STICK_SLOPE_RIGHT = 0.8f;  //�p�b�h��L�X�e�B�b�N�̉E�̌X��
	static const float PAD_STICK_SLOPE_LEFT  = -0.8f; //�p�b�h��L�X�e�B�b�N�̍��̌X��
	static const float PAD_STICK_SLOPE_UP    = 0.8f;  //�p�b�h��L�X�e�B�b�N�̏�̌X��
	static const float PAD_STICK_SLOPE_DOWN  = -0.8f; //�p�b�h��L�X�e�B�b�N�̉��̌X��
}


//��ʂɕ\������Ă���{�^�����Ǘ�����
namespace ButtonManager
{

	//���ݎg���Ă���{�^�����i�[����ϐ�
	std::vector<ButtonBase*> nowUseButton;

	//X��Y�̑O����͕ۑ��p
	float beforeXSlope[2] = { ZERO,ZERO };
	float beforeYSlope[2] = { ZERO,ZERO };

	//X��Y�̌��݂̓��͕ۑ��p
	float NowXSlope[2] = { ZERO,ZERO };
	float NowYSlope[2] = { ZERO,ZERO };

	//�X�V
	void Update()
	{
		//�����{�^�����g���Ă��Ȃ������炱�̐�͏������Ȃ�
		if (nowUseButton.empty()) return;

		//�e�R���g���[���[�őI������Ă���{�^���i�[�p
		ButtonBase* pButtonController0 = nullptr;
		ButtonBase* pButtonController1 = nullptr;

		//�Ō�܂ŉ񂵂�nullptr�̂��͍̂폜�E�I������Ă���{�^����������
		for (auto i = nowUseButton.begin(); i != nowUseButton.end();)
		{
			//nullptr��������폜
			if ((*i) == nullptr)
				i = nowUseButton.erase(i);
			else
			{
				//�I������Ă�����i�[
				if ((*i)->IsSelect() && (*i)->GetControllerNum() == 0) pButtonController0 = (*i);
				if ((*i)->IsSelect() && (*i)->GetControllerNum() == 1) pButtonController1 = (*i);

				//���ɐi�߂�
				i++;
			}
		}

		//null����Ȃ��̂Ȃ���͏���
		if (pButtonController0 != nullptr) Input(pButtonController0);
		if (pButtonController1 != nullptr) Input(pButtonController1,1);
	}

	//����
	void Input(ButtonBase* button, int numController)
	{

		//�I������Ă���{�^����x��y��ۑ�
		float x = button->GetComponent<Transform>()->GetPosition().x;
		float y = button->GetComponent<Transform>()->GetPosition().y;

		//�O��̌X�����擾
		ARGUMENT_INITIALIZE(beforeXSlope[numController], NowXSlope[numController]);
		ARGUMENT_INITIALIZE(beforeYSlope[numController], NowYSlope[numController]);

		//PadL�X�e�B�b�N�̌X����ۑ�
		ARGUMENT_INITIALIZE(NowXSlope[numController],Input::GetPadStickL(numController).x);
		ARGUMENT_INITIALIZE(NowYSlope[numController],Input::GetPadStickL(numController).y);

		//�ۑ��p
		std::vector<std::pair<float, ButtonBase*>> date;

		//�X�����萔���傫�����
		if (NowXSlope[numController] >= PAD_STICK_SLOPE_RIGHT && beforeXSlope[numController] <= PAD_STICK_SLOPE_RIGHT)
		{

			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//X�̍��W���I������Ă����{�^���������傫�����
				if ((*i)->GetComponent<Transform>()->GetPosition().x > x)
				{
					date.push_back({ (*i)->GetComponent<Transform>()->GetPosition().x,(*i)});
				}
			}
		}

		//�����󂶂�Ȃ����
		if (!date.empty())
		{

			//�I������Ă���{�^�����ǉ�
			date.push_back({ x,button });

			//�\�[�g(����)
			sort(date.begin(), date.end());

			//���łɑI������Ă���̂Ȃ炱�̐揈�����Ȃ�
			if ((*(date.begin() + 1)).second->IsSelect()) return;

			//�I������
			button->SetSelect(false, numController);

			//�{�^���i�[
			ARGUMENT_INITIALIZE(button, (*(date.begin() + 1)).second);

			//�I�������悤�ɂ���(�O��̃{�^���̈ʒu���i�[)
			button->SetBeforeButtonSelectPos((*(date.begin())).second->GetComponent<Transform>()->GetPosition());
			button->SetSelect(true, numController);

			return;
		}

		//�X�����萔��菬�������
		if (NowXSlope[numController] <= PAD_STICK_SLOPE_LEFT && beforeXSlope[numController] >= PAD_STICK_SLOPE_LEFT)
		{
			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//X�̍��W���I������Ă����{�^�����������������
				if ((*i)->GetComponent<Transform>()->GetPosition().x < x)
				{
					date.push_back({ (*i)->GetComponent<Transform>()->GetPosition().x,(*i) });
				}
			}
		}

		//�����󂶂�Ȃ����
		if (!date.empty())
		{

			//�I������Ă���{�^�����ǉ�
			date.push_back({ x,button });

			//�\�[�g(�~��)
			sort(date.rbegin(), date.rend());

			//���łɑI������Ă���̂Ȃ炱�̐揈�����Ȃ�
			if ((*(date.begin() + 1)).second->IsSelect()) return;

			//�I������
			button->SetSelect(false, numController);

			//�{�^���i�[
			ARGUMENT_INITIALIZE(button, (*(date.begin() + 1)).second);

			//�I�������悤�ɂ���
			button->SetSelect(true, numController);

			return;
		}

		//�X�����萔���傫�����
		if (NowYSlope[numController] >= PAD_STICK_SLOPE_UP && beforeYSlope[numController] <= PAD_STICK_SLOPE_UP)
		{
			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//Y�̍��W���I������Ă����{�^���������傫�����
				if ((*i)->GetComponent<Transform>()->GetPosition().y > y)
				{
					date.push_back({ (*i)->GetComponent<Transform>()->GetPosition().y,(*i) });
				}
			}
		}

		//�����󂶂�Ȃ����
		if (!date.empty())
		{

			//�I������Ă���{�^�����ǉ�
			date.push_back({ y,button });

			//�\�[�g(����)
			sort(date.begin(), date.end());

			//���łɑI������Ă���̂Ȃ炱�̐揈�����Ȃ�
			if ((*(date.begin() + 1)).second->IsSelect()) return;

			//�I������
			button->SetSelect(false, numController);

			//�{�^���i�[
			ARGUMENT_INITIALIZE(button, (*(date.begin() + 1)).second);

			//�I�������悤�ɂ���
			button->SetSelect(true, numController);

			return;
		}

		//�X�����萔��菬�������
		if (NowYSlope[numController] <= PAD_STICK_SLOPE_DOWN && beforeYSlope[numController] >= PAD_STICK_SLOPE_DOWN)
		{
			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//X�̍��W���I������Ă����{�^�����������������
				if ((*i)->GetComponent<Transform>()->GetPosition().y < y)
				{
					date.push_back({ (*i)->GetComponent<Transform>()->GetPosition().y,(*i) });
				}
			}
		}

		//�����󂶂�Ȃ����
		if (!date.empty())
		{

			//�I������Ă���{�^�����ǉ�
			date.push_back({ y,button });

			//�\�[�g(�~��)
			sort(date.rbegin(), date.rend());

			//���łɑI������Ă���̂Ȃ炱�̐揈�����Ȃ�
			if ((*(date.begin() + 1)).second->IsSelect()) return;

			//�I������
			button->SetSelect(false, numController);

			//�{�^���i�[
			ARGUMENT_INITIALIZE(button, (*(date.begin() + 1)).second);

			//�I�������悤�ɂ���
			button->SetSelect(true, numController);

			return;
		}
				
	}


	//�{�^����ǉ�
	void AddButton(ButtonBase* button) 
	{	
		//�{�^�����܂��P���o�^����Ă��Ȃ��̂Ȃ�
		if (nowUseButton.empty()) button->SetSelect(true,ZERO);

		//�{�^����ǉ�
		nowUseButton.push_back(button);
	}

	//�C�ӂɑI����Ԃ̃{�^����ύX
	void SetSelect(ButtonBase* button, int numController)
	{
		for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
		{
			//�����R���g���[���[�ԍ��Ȃ�
			if((*i)->GetControllerNum() == numController)
				(*i)->SetSelect(false, numController);
		}

		button->SetSelect(true, numController);
	}

	//���Z�b�g����
	void Reset()
	{
		//��ɂ���
		nowUseButton.clear();
	}
};