#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/VFX.h"

/// <summary>
/// �G�t�F�N�g���Ǘ�����
/// </summary>
namespace EffectManager
{

	/// <summary>
	/// �G�t�F�N�g�\��
	/// </summary>
	/// <param name="pos">�G�t�F�N�g����������ʒu</param>
	/// <param name="filename">�G�t�F�N�g��񂪕ۊǂ��Ă���t�@�C���l�[���p�X</param>
	void Draw(string effectName,string fileNamePath,XMFLOAT3 pos);

	/// <summary>
	/// �G�t�F�N�g���[�h
	/// </summary>
	/// <param name="fileNamePath">�G�t�F�N�g��񂪕ۊǂ��Ă���t�@�C���l�[���p�X</param>
	void Load(string fileNamePath);

	/// <summary>
	/// �G�~�b�^�[�f�[�^���擾
	/// </summary>
	/// <param name="fileNamePath">�G�t�F�N�g��񂪕ۊǂ��Ă���t�@�C���l�[���p�X</param>
	/// <returns>�G�~�b�^�[�f�[�^</returns>
	EmitterData GetEmitterData(string fileNamePath);
}

