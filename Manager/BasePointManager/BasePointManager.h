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

	/// <summary>
	/// ��_�������_���Ɏ擾
	/// </summary>
	/// <param name="isPlayer">Player�̊�_���ǂ���</param>
	/// <returns>��_</returns>
	XMFLOAT3 GetRandomBasePoint(bool isPlayer);

	/// <summary>
	/// ��_�̖��O�������_���Ɏ擾
	/// </summary>
	/// <returns>��_�̖��O</returns>
	string GetRandomBasePointName();
};

