#pragma once
#include "../../Base/NormalObject.h"

//�e�j�X�R�[�g�̖��O
enum class TennisCourtName
{
	Z_PLUS_COURT, //Z�����v���X�̃R�[�g
	Z_MINUS_COURT //Z�����}�C�i�X�̃R�[�g
};

/// <summary>
/// �e�j�X�R�[�g���f��
/// </summary>
class TennisCourt : public NormalObject
{
public:

	//�R���X�g���N�^
	TennisCourt(GameObject* parent, std::string modelPath, std::string name);

	//�f�X�g���N�^
	~TennisCourt() {};

	//������
	void ChildInitialize() override;

	//��ڂ̃E�B���h�E�̕`��
	void TwoWindowDraw() override;
};

