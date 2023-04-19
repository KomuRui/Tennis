#include "OtherAudioManager.h"
#include "../../../Engine/ResourceManager/Audio.h"

// �l�X�ȉ����Ǘ�����
namespace OtherAudioManager
{
	
	int hClickAudio_;			   //�N���b�N��
	int hWarpHitAudio_;			   //���[�v�q�b�g��
	int hWarpShootAudio_;		   //���[�v�V���b�g��
	int hTitleExplosionAudio_;	   //������
	int hBossExplosionAudio_;	   //�{�X������
	int hBossChargeAudio_;	       //�`���[�W��
	int hMiniGameCountDownAudio_;  //�~�j�Q�[���̃J�E���g�_�E����
	int hGameOverAudio_;		   //�Q�[���I�[�o�[��

	/// <summary>
	/// ������
	///</summary>
	void Initialize()
	{
		hClickAudio_ = Audio::Load("Audio/SE/Click/NormalClick.wav");
		assert(hClickAudio_ >= ZERO);

		hWarpHitAudio_ = Audio::Load("Audio/SE/Warp/Hit.wav");
		assert(hWarpHitAudio_ >= ZERO);

		hWarpShootAudio_ = Audio::Load("Audio/SE/Warp/Shoot.wav");
		assert(hWarpShootAudio_ >= ZERO);

		hTitleExplosionAudio_ = Audio::Load("Audio/SE/Other/TitleExplosion.wav");
		assert(hTitleExplosionAudio_ >= ZERO);

		hBossExplosionAudio_ = Audio::Load("Audio/SE/Boss/Explosion.wav");
		assert(hBossExplosionAudio_ >= ZERO);

		hBossChargeAudio_ = Audio::Load("Audio/SE/Boss/Charge.wav");
		assert(hBossChargeAudio_ >= ZERO);

		hMiniGameCountDownAudio_ = Audio::Load("Audio/SE/MiniGame/CountDown.wav");
		assert(hMiniGameCountDownAudio_ >= ZERO);

		hGameOverAudio_ = Audio::Load("Audio/SE/Other/GameOver.wav");
		assert(hGameOverAudio_ >= ZERO);
	}

	/// <summary>
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize()
	{
		Initialize();
	}

	/// <summary>
	/// �N���b�N��
	/// </summary>
	void ClickAudio() { Audio::Play(hClickAudio_); }

	/// <summary>
	/// ���[�v�q�b�g��
	/// </summary>
	void WarpHitAudio() { Audio::Play(hWarpHitAudio_); }

	/// <summary>
	/// ���[�v�V���b�g��
	/// </summary>
	void WarpShootAudio() { Audio::Play(hWarpShootAudio_); }

	/// <summary>
	/// �^�C�g��������
	/// </summary>
	void TitleExplosionAudio() { Audio::Play(hTitleExplosionAudio_); }

	/// <summary>
	/// �{�X�̃`���[�W��
	/// </summary>
	void BossCharge() { Audio::Play(hBossChargeAudio_); }

	/// <summary>
	/// �{�X�̔�����
	/// </summary>
	void BossExplosion() { Audio::Play(hBossExplosionAudio_); }

	/// <summary>
	/// �~�j�Q�[���̃J�E���g�_�E��
	/// </summary>
	void MiniGameCountDown() { Audio::Play(hMiniGameCountDownAudio_); }

	/// <summary>
	/// �Q�[���I�[�o�[��
	/// </summary>
	void GameOverAudio() { Audio::Play(hGameOverAudio_); }
}