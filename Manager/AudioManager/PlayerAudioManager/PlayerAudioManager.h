#pragma once

/// <summary>
/// Player�̉����Ǘ�����
/// </summary>
namespace PlayerAudioManager
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
	/// ��]��
	/// </summary>
	void RotationAudio();

	/// <summary>
	/// �U�������������̉�
	/// </summary>
	void AttackHitAudio();

	/// <summary>
	/// �_���[�W����������̉�
	/// </summary>
	void DamageAudio();

	/// <summary>
	/// �W�����v��
	/// </summary>
	void JumpAudio();

	/// <summary>
	/// ���n��
	/// </summary>
	void JumpLandAudio();

	/// <summary>
	/// ������
	/// </summary>
	void FootStepAudio();

	/// <summary>
	/// �u���b�N�q�b�g��
	/// </summary>
	void BlockHitAudio();

	/// <summary>
	/// �����X�g�b�v
	/// </summary>
	void StopFootStep();

	/// <summary>
	/// ���������~�܂��Ă���̂��ǂ���
	/// </summary>
	/// <returns>true�Ȃ�~�܂��Ă���</returns>
	bool IsStopFootStepAudio();
}