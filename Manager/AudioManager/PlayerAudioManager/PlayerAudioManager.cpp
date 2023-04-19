#include "PlayerAudioMAnager.h"
#include "../../../Engine/ResourceManager/Audio.h"

// Player�̉����Ǘ�����
namespace PlayerAudioManager
{
	//�����������̉��ԍ�
	int hRotationAudio_; //��]��
	int hAttackHitAudio_;//�U����
	int hDamageAudio_;   //�_���[�W��
	int hJumpAudio_;     //�W�����v��
	int hJumpLandAudio_; //���n��
	int hFootStepAudio_; //������
	int hBlockHitAudio_; //�u���b�N�q�b�g��

	//�t���O
	bool IsStopFootStep; //�������~�܂��Ă��邩�ǂ���

	/// <summary>
	/// ������
	///</summary>
	void Initialize()
	{
		hRotationAudio_ = Audio::Load("Audio/SE/Player/Rotation.wav");
		assert(hRotationAudio_ >= ZERO);

		hAttackHitAudio_ = Audio::Load("Audio/SE/Player/Hit.wav");
		assert(hAttackHitAudio_ >= ZERO);

		hDamageAudio_ = Audio::Load("Audio/SE/Player/Damage.wav");
		assert(hDamageAudio_ >= ZERO);

		hJumpAudio_ = Audio::Load("Audio/SE/Player/Jump.wav");
		assert(hJumpAudio_ >= ZERO);

		hJumpLandAudio_ = Audio::Load("Audio/SE/Player/JumpLanding.wav");
		assert(hJumpLandAudio_ >= ZERO);

		hFootStepAudio_ = Audio::Load("Audio/SE/Player/FootStep.wav");
		assert(hFootStepAudio_ >= ZERO);

		hBlockHitAudio_ = Audio::Load("Audio/SE/Player/BlockHit.wav");
		assert(hBlockHitAudio_ >= ZERO);

		ARGUMENT_INITIALIZE(IsStopFootStep, true);
	}

	/// <summary>
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize()
	{
		Initialize();
	}

	//��]��
	void RotationAudio() { Audio::Play(hRotationAudio_); }

	//�U�������������̉�
	void AttackHitAudio() { Audio::Play(hAttackHitAudio_); }
	
	//�_���[�W����������̉�
	void DamageAudio() { Audio::Play(hDamageAudio_); }

	//�W�����v��
	void JumpAudio() { Audio::Play(hJumpAudio_); }

	//���n��
	void JumpLandAudio() { Audio::Play(hJumpLandAudio_); }

	//������
	void FootStepAudio() 
	{
		//�܂��������炵�Ă��Ȃ��̂Ȃ�
		if (IsStopFootStep)
		{
			Audio::PlayLoop(hFootStepAudio_);
			ARGUMENT_INITIALIZE(IsStopFootStep, false);
		}
	}

	//�u���b�N�q�b�g��
	void BlockHitAudio() { Audio::Play(hBlockHitAudio_); }

	//�����X�g�b�v
	void StopFootStep() 
	{
		Audio::Stop(hFootStepAudio_);
		ARGUMENT_INITIALIZE(IsStopFootStep, true);
	}

	//���������~�܂��Ă���̂��ǂ���
	bool IsStopFootStepAudio() { return IsStopFootStep; }
}