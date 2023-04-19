#pragma once
#include "../../../Engine/GameObject/GameObject.h"

/// <summary>
/// Player�̃G�t�F�N�g���Ǘ�����
/// </summary>
namespace PlayerEffectManager
{

	/// <summary>
	/// ��]�G�t�F�N�g
	/// </summary>
	/// <param name="modelnum">player�̃��f���ԍ�</param>
	void RotationEffect(int modelnum);

	/// <summary>
	/// �����G�t�F�N�g
	/// </summary>
	/// <param name="position">�G�t�F�N�g�𔭐����������|�W�V����</param>
	void FallEffect(XMFLOAT3 position);

	/// <summary>
	/// ���S�|�W�V����
	/// </summary>
	void DieEffect(const XMFLOAT3& position, const XMVECTOR& dir);

	/// <summary>
	/// �R�C�����z�������G�t�F�N�g
	/// </summary>
	/// <param name="pos">�����|�W�V����</param>
	/// <param name="dir">����</param>
	/// <param name="up">�L�����̏����</param>
	void AbsorptionEffect(const XMFLOAT3& pos, const XMVECTOR& dir,const XMVECTOR& up);
}

