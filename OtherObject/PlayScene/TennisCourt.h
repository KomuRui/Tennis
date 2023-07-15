#pragma once
#include "../../Base/NormalObject.h"
#include <map>

//�e�j�X�R�[�g�̖��O
enum class TennisCourtName
{
	Z_PLUS_COURT, //Z�����v���X�̃R�[�g
	Z_MINUS_COURT //Z�����}�C�i�X�̃R�[�g
};

//�e�j�X�R�[�g�̌^
enum class TennisCourtType
{
	HARD_COURT,  //�n�[�h�R�[�g
	CLAY_COURT,  //�N���C�R�[�g
	GRASS_COURT  //�O���X�R�[�g
};

/// <summary>
/// �e�j�X�R�[�g���f��
/// </summary>
class TennisCourt : public NormalObject
{

	//�e�j�X�R�[�g�̌^
	TennisCourtType type_;

	//�e�j�X�R�[�g�ɑ΂��Ẵ��f���ԍ�
	map<TennisCourtType, int> hModelTable_;

public:

	//�R���X�g���N�^
	TennisCourt(GameObject* parent, std::string modelPath, std::string name);

	//�f�X�g���N�^
	~TennisCourt() {};

	//������
	void ChildInitialize() override;

	//��ڂ̃E�B���h�E�̕`��
	void TwoWindowDraw() override;

	//�e�j�X�R�[�g�̌^��ݒ�
	void SetTennisCourtType(TennisCourtType type);
};

