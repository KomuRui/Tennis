#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// �C�̃��f��
/// </summary>
class Water : public NormalObject
{

	float scroll;   //UV�X�N���[��

public:

	//�R���X�g���N�^
	Water(GameObject* parent, std::string modelFilePath_, std::string name);

	//�f�X�g���N�^
	~Water() {};

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//��ڂ̃E�B���h�E�̕`��
	void TwoWindowDraw() override;
};

