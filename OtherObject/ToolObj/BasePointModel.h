#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// �{�[�������ł�����_�ɔz�u���郂�f��
/// </summary>
class BasePointModel : public NormalObject
{
public:

	//�R���X�g���N�^
	BasePointModel(GameObject* parent, std::string modelPath, std::string name);
	BasePointModel(GameObject* parent);

	//�f�X�g���N�^
	~BasePointModel() {};

	//��ڂ̃E�B���h�E�̕`��
	void TwoWindowDraw() override;
};

