#pragma once
#include "../../OtherObject/TitleScene/TennisCourt.h"

//�e�j�X�{�[�������ł�����_���Ǘ����Ă��閼�O���
namespace BasePointManager
{
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ��_���f���𐶐�
	/// </summary>
	void InstantiateBasePointModel();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ��_�G�N�X�|�[�g
	/// </summary>
	void BasePointExport();

	/// <summary>
	/// ��_���擾
	/// </summary>
	/// <param name="name">��_�̖��O</param>
	/// <param name="isPlayer">Player�̊�_���ǂ���</param>
	/// <returns>��_</returns>
	XMFLOAT3 GetBasePoint(string name,bool isPlayer);
};
