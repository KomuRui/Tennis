#pragma once

class ButtonBase;

/// <summary>
/// ��ʂɕ\������Ă���{�^�����Ǘ�����
/// </summary>
namespace ButtonManager
{
	
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ����
	/// </summary>
	void Input(ButtonBase* button,int numController = 0);

	/// <summary>
	/// �{�^����ǉ�
	/// </summary>
	void AddButton(ButtonBase* button);

	/// <summary>
	/// �C�ӂɑI����Ԃ̃{�^����ύX
	/// </summary>
	/// <param name="button">�{�^��</param>
	void SetSelect(ButtonBase* button,int numController = 0);

	/// <summary>
	/// ���Z�b�g����
	/// </summary>
	void Reset();
};

