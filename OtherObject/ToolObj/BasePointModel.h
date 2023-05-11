#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// �{�[�������ł�����_�ɔz�u���郂�f��
/// </summary>
class BasePointModel : public NormalObject
{
	//��_�̖��O
	string basePointName_;

	//�v���C���[�^�C�v���ǂ���
	bool isPlayerType_;

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
	/// �v���C���[�^�C�v���ǂ����Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ�v���C���[�^�C�v�ɃZ�b�g</param>
	void SetPlayerType(bool flag) { isPlayerType_ = flag; }

	/// <summary>
	/// �v���C���[�^�C�v���ǂ����擾
	/// </summary>
	/// <returns>true�Ȃ�v���C���[�^�C�v</returns>
	bool isPlayerType() { return isPlayerType_; }

	/// <summary>
	/// ��_�̖��O���擾
	/// </summary>
	/// <returns>��_�̖��O</returns>
	string GetBasePointName() { return basePointName_; }
};

