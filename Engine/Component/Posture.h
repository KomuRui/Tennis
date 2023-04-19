#pragma once
#include "../ResourceManager/Model.h"

/// <summary>
/// �ǂ�Ȓn�`�ł��������p��������Ă����R���|�[�l���g(3D���f��)
/// �n�`�̃��f���ԍ����K�v
/// �d�͂��K�����Ă���,�^���̓����蔻�肾�����Ă���
/// </summary>
class Posture
{
public:

	Transform* transform_; //���f���̃g�����X�t�H�[��
	XMVECTOR* down_;       //�L�����̉��x�N�g��
	XMVECTOR* vNormal_;    //���݂̐^���̖@��
	int hGroundModel_;     //�X�e�[�W�̃��f���ԍ�

	//�R���X�g���N�^
	Posture();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �^���̖@���𒲂ׂăL�����̏㎲�����肷��
	/// </summary>
	/// <param name="data">�����蔻��ɕK�v�ȃf�[�^</param>
	void CheckUnderNormal(const RayCastData& data);

	/// <summary>
	/// ���C�œ����蔻��(3D�p)
	/// </summary>
	/// <param name="data">�����蔻��ɕK�v�ȃf�[�^</param>
	void StageRayCast(const RayCastData& data);
};

