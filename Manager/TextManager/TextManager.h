#pragma once
#include "../../Manager/SceneManager/SceneManager.h"

/// <summary>
/// ���{��̃e�L�X�g�Ǘ�
/// </summary>
namespace TextManager
{
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �����̑Ή�����ԍ����擾
	/// </summary>
	/// <param name="text">�g����������</param>
	/// <returns>�Ή�����ԍ�</returns>
	int GetNumber(wchar_t t);

	/// <summary>
	/// �V�[��ID���Q�b�g
	/// </summary>
	/// <param name="id">���݂̃V�[����ID</param>
	/// <returns>���݂̃V�[����ID�Ŏg���������擾</returns>
	std::string GetText(SCENE_ID nowId);
}
