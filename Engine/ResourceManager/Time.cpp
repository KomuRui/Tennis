#include "Time.h"
#include "Global.h"
#include <vector>

//�ϐ�
namespace
{
	//���ԑ���ɕK�v�ȏ��
	std::vector<int> CountFps_;	//���݂̃t���[�����[�g���i�[���Ă�������
	int FPS_;		            //���������ɍő�t���[�����[�g���i�[���Ă���
	int LookAt_;	            //�z��̂ǂ������邩

	//�^�C�}�[�ɕK�v�ȏ��
	struct TimeInfo{
		double Seconds_ = ZERO; //�ǂ̂��炢�̕b����������
		bool Lock_ = true;		//���݂̏�ԂŌŒ肷�邩
	};
	
	//���ݎg�p����Ă�^�C�}�[��S�Ă܂Ƃ߂Ă������
	std::vector<TimeInfo*> date;
	
}

//����
namespace Time
{
	//������
	void Initialize(int FPS)
	{
		//�e�ϐ�������
		ARGUMENT_INITIALIZE(FPS_, FPS);
		ARGUMENT_INITIALIZE(LookAt_, (int)ZERO);

		date.clear();           //�O�̂��߂̏�����
		CountFps_.clear();		//�O�̂��߂̏�����
		CountFps_.reserve(FPS);	//�v�f�����m�ۂ��Ă���

		//������
		while (CountFps_.size() != CountFps_.capacity())
		{
			CountFps_.push_back(FPS);
		}
	}

	//�^�C�}�[�ǉ�
	int Add()
	{
		//�f�[�^�쐬
		TimeInfo* pDate = new TimeInfo;
		ARGUMENT_INITIALIZE(pDate->Lock_,false);
		ARGUMENT_INITIALIZE(pDate->Seconds_,ZERO);

		//�V���ɒǉ�
		date.push_back(pDate);
		return (int)date.size() - 1;
	}

	//�X�V
	void Update()
	{
		for (int i = 0; i < CountFps_.size(); i++)
		{
			//�ő�t���[�����[�g�𒴂��邱�Ƃ͂Ȃ��̂�
			if (CountFps_.at(i) < FPS_)
				CountFps_.at(i)++;
		}

		LookAt_++;
		if (LookAt_ >= FPS_)
			LookAt_ -= FPS_;


		//���݂̃^�C�}�[�̐���������
		for (auto i = date.begin(); i != date.end(); i++)
		{
			//���b�N����Ă��Ȃ��̂Ȃ�
			if (!(*i)->Lock_)
			{
				float fps = CountFps_.at(LookAt_) * 0.98f;
				(*i)->Seconds_ += 1.0 / fps;
			}
		}

		//������
		ARGUMENT_INITIALIZE(CountFps_.at(LookAt_),ZERO);
	}

	//���
	void AllRelease()
	{
		//�폜
		for (auto i = date.begin(); i != date.end(); i++)
		{
			SAFE_DELETE((*i));
		}

		//��ɂ���
		date.clear();
	}

	/// <summary>
	/// ���Z�b�g(�b��0��)
	/// </summary>
	/// <param name="handle">�n���h���ԍ�</param>
	void Reset(int handle){ ARGUMENT_INITIALIZE(date[handle]->Seconds_,ZERO);}

	/// <summary>
	/// ���b�N(�^�C�}�[�X�g�b�v)
	/// </summary>
	/// <param name="handle">�n���h���ԍ�</param>
	void Lock(int handle){ ARGUMENT_INITIALIZE(date[handle]->Lock_,true); }

	/// <summary>
	/// �A�����b�N(�^�C�}�[�J�n)
	/// </summary>
	/// <param name="handle">�n���h���ԍ�</param>
	void UnLock(int handle){ ARGUMENT_INITIALIZE(date[handle]->Lock_,false); }

	/// <summary>
	/// ���b�N���Ă��邩�ǂ���
	/// </summary>
	/// <param name="handle">�n���h���ԍ�</param>
	/// <returns>true�Ȃ烍�b�N���Ă���</returns>
	bool isLock(int handle){ return date[handle]->Lock_; }

	//���Ԏ擾
	int GetTimei(int handle){ return (int)date[handle]->Seconds_;}
	float GetTimef(int handle){ return (float)date[handle]->Seconds_;}
	double GetTime(int handle){ return date[handle]->Seconds_;}
}