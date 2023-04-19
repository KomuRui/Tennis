#pragma once

/// <summary>
/// DirectX���Ɉˑ����Ȃ�Time
/// </summary>
namespace Time
{
	/// <summary>
	/// ������(Main�ŏ�����)
	/// </summary>
	/// <param name="FPS">FPS</param>
	void Initialize(int FPS);

	/// <summary>
	/// �^�C�}�[�ǉ�
	/// </summary>
	/// <returns>�^�C�}�[�ԍ�(�^�C�}�[�g���Ƃ��Ɏg��)</returns>
	int Add();

	/// <summary>
	/// �X�V(Main�ŌĂяo��)
	/// </summary>
	void Update();

	/// <summary>
	/// ���
	/// </summary>
	void AllRelease();

	/// <summary>
	/// �^�C�����Z�b�g
	/// </summary>
	/// <param name="handle">���Z�b�g�������^�C�}�[�̔ԍ�</param>
	void Reset(int handle);

	/// <summary>
	/// �^�C�����X�V���Ȃ��悤��
	/// </summary>
	/// <param name="handle">���Z�b�g�������^�C�}�[�̔ԍ�</param>
	void Lock(int handle);

	/// <summary>
	/// �^�C�����X�V����悤��
	/// </summary>
	/// <param name="handle">���Z�b�g�������^�C�}�[�̔ԍ�</param>
	void UnLock(int handle);

	/// <summary>
	/// �����b�N���Ă��邩�ǂ���
	/// </summary>
	/// <param name="handle">���Z�b�g�������^�C�}�[�̔ԍ�</param>
	/// <returns>true�Ȃ烍�b�N���Ă���</returns>
	bool isLock(int handle);

	/// <summary>
	/// �Ăяo�����_�̎��Ԃ��擾
	/// </summary>
	/// <param name="handle">���Z�b�g�������^�C�}�[�̔ԍ�</param>
	/// <returns>int�^�̎���</returns>
	int GetTimei(int handle);

	/// <summary>
	/// �Ăяo�����_�̎��Ԃ��擾
	/// </summary>
	/// <param name="handle">���Z�b�g�������^�C�}�[�̔ԍ�</param>
	/// <returns>float�^�̎���</returns>
	float GetTimef(int handle);

	/// <summary>
	/// �Ăяo�����_�̎��Ԃ��擾
	/// </summary>
	/// <param name="handle">���Z�b�g�������^�C�}�[�̔ԍ�</param>
	/// <returns>double�^�̎���</returns>
	double GetTime(int handle);
};

