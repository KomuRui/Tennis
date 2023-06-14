#pragma once
#include "../../OtherObject/TitleScene/TennisCourt.h"

class PlayerBase;

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
	/// <param name="TennisCourtName">��_���擾�������R�[�g�̖��O</param>
	/// <returns>��_</returns>
	XMFLOAT3 GetBasePoint(string name, TennisCourtName isPlayer);

	/// <summary>
	/// ��_�������_���Ɏ擾
	/// </summary>
	/// <param name="TennisCourtName">��_���擾�������R�[�g�̖��O</param>
	/// <returns>��_</returns>
	XMFLOAT3 GetRandomBasePoint(TennisCourtName n);

	/// <summary>
	/// ���͂ɑ΂����_�̖��O���擾
	/// </summary>
	/// <returns>��_�̖��O</returns>
	string GetInputBasePoint(PlayerBase* p);

	/// <summary>
	/// ���͂ɑ΂����_�̖��O���擾(�����[��)
	/// </summary>
	/// <returns>��_�̖��O</returns>
	string GetRallyInputBasePoint(PlayerBase* p);

	/// <summary>
	/// ���͂ɑ΂����_�̖��O���擾(�T�[�u���V�[�u��)
	/// </summary>
	/// <returns>��_�̖��O</returns>
	string GetServeReceiveInputBasePoint(PlayerBase* p);

	/// <summary>
	/// ��_�̖��O�������_���Ɏ擾
	/// </summary>
	/// <returns>��_�̖��O</returns>
	string GetRandomBasePointName();
};

