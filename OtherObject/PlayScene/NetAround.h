#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// �R�[�g�̎���̃l�b�g
/// </summary>
class NetAround : public NormalObject
{
public:

	//�R���X�g���N�^
	NetAround(GameObject* parent, std::string modelPath, std::string name);

	//�f�X�g���N�^
	~NetAround() {};

	//������
	void ChildInitialize() override;

	//�`��
	void Draw() override {};

	//�����E�������`��
	void TransparentDraw() override;
};

