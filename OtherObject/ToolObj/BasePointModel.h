#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// �{�[�������ł�����_�ɔz�u���郂�f��
/// </summary>
class BasePointModel : public NormalObject
{
	//��_�̖��O
	string basePointName_;

	//�v���C���[1�̃R�[�g���ǂ���
	bool isPlayer1CourtType_;

	//�T�[�u���V�[�u�̊�_���ǂ���
	bool isServeReceiveBasePoint_;

public:

	//�R���X�g���N�^
	BasePointModel(GameObject* parent, std::string modelPath, std::string name);
	BasePointModel(GameObject* parent);

	//�f�X�g���N�^
	~BasePointModel() {};

	//������
	void ChildInitialize() override;

	//�`��
	void Draw() override;

	//��ڂ̃E�B���h�E�̕`��
	void TwoWindowDraw() override;

	//��_�̖��O�Z�b�g
	void SetBasePointName(string name) { basePointName_ = name; }

	/// <summary>
	/// �v���C���[1�̃R�[�g���ǂ����Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ�v���C���[1�̃R�[�g�ɃZ�b�g</param>
	void SetPlayer1CourtType(bool flag) { isPlayer1CourtType_ = flag; }

	/// <summary>
	/// �v���C���[1�̃R�[�g���ǂ����擾
	/// </summary>
	/// <returns>true�Ȃ�v���C���[�^�C�v</returns>
	bool isPlaye1CourtType() { return isPlayer1CourtType_; }

	/// <summary>
	/// �T�[�u���V�[�u���̊�_���ǂ����Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ�T�[�u���V�[�u���̊�_�ɃZ�b�g</param>
	void SetServeReceiveBasePoint(bool flag) { isServeReceiveBasePoint_ = flag; }

	/// <summary>
	/// �T�[�u���V�[�u���̊�_���ǂ����擾
	/// </summary>
	/// <returns>true�Ȃ�T�[�u���V�[�u���̊�_</returns>
	bool isServeReceiveBasePoint() { return isServeReceiveBasePoint_; }

	/// <summary>
	/// ��_�̖��O���擾
	/// </summary>
	/// <returns>��_�̖��O</returns>
	string GetBasePointName() { return basePointName_; }
};

