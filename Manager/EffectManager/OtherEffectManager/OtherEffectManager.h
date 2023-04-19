#pragma once
#include "../../../Engine/GameObject/GameObject.h"

/// <summary>
/// �l�X�ȃG�t�F�N�g���Ǘ�����
/// </summary>
namespace OtherEffectManager
{
	/// <summary>
	/// �����G�t�F�N�g
	/// </summary>
	/// <param name="pos">�������������|�W�V����</param>
	/// <param name="dir">�����̕���</param>
	int WaterCurrentEffect(const XMFLOAT3& pos,const XMFLOAT3& dir);

	/// <summary>
	/// �����G�t�F�N�g
	/// </summary>
	/// <param name="Hitpos">�G�t�F�N�g�𔭐����������ʒu</param>
	void ExplosionEffect(const XMFLOAT3& pos);
}