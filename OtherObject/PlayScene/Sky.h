#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// �󃂃f��
/// </summary>
class Sky : public NormalObject
{

	float scroll;   //UV�X�N���[��

public:

	//�R���X�g���N�^
	Sky(GameObject* parent, std::string modelPath, std::string name);

	//�f�X�g���N�^
	~Sky() {};

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;
};

