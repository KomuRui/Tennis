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
	void Input(ButtonBase* button);

	/// <summary>
	/// �{�^����ǉ�
	/// </summary>
	void AddButton(ButtonBase* button);

	/// <summary>
	/// ���Z�b�g����
	/// </summary>
	void Reset();
};

