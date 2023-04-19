#pragma once

/// <summary>
/// �l�X�ȉ����Ǘ�����
/// </summary>
namespace OtherAudioManager
{
	/// <summary>
	/// ������
	///</summary>
	void Initialize();

	/// <summary>
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// �N���b�N��
	/// </summary>
	void ClickAudio();

	/// <summary>
	/// ���[�v�q�b�g��
	/// </summary>
	void WarpHitAudio();

	/// <summary>
	/// ���[�v�V���b�g��
	/// </summary>
	void WarpShootAudio();

	/// <summary>
	/// �^�C�g��������
	/// </summary>
	void TitleExplosionAudio();

	/// <summary>
	/// �{�X�̃`���[�W��
	/// </summary>
	void BossCharge();

	/// <summary>
	/// �{�X�̔�����
	/// </summary>
	void BossExplosion();

	/// <summary>
	/// �~�j�Q�[���̃J�E���g�_�E��
	/// </summary>
	void MiniGameCountDown();

	/// <summary>
	/// �Q�[���I�[�o�[��
	/// </summary>
	void GameOverAudio();
}