#pragma once
#include "../GameManager/GameManager.h"

//�e�L�����N�^�[�̃p�����[�^���Ǘ�
namespace CharaParameterManager
{
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �L�����̃X�s�[�h���擾
	/// </summary>
	/// <param name="charaModelPath">�L�����̃��f���p�X</param>
	/// <returns>�X�s�[�h</returns>
	float GetCharaSpeed(string charaModelPath);

	/// <summary>
	/// �L�����̃p���[���擾
	/// </summary>
	/// <param name="charaModelPath">�L�����̃��f���p�X</param>
	/// <returns>�p���[</returns>
	float GetCharaPower(string charaModelPath);

	/// <summary>
	/// �L�����̃e�N�j�b�N���擾
	/// </summary>
	/// <param name="charaModelPath">�L�����̃��f���p�X</param>
	/// <returns>�e�N�j�b�N</returns>
	float GetCharaTechnique(string charaModelPath);
};

