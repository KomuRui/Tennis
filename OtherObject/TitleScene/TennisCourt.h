#pragma once
#include "../../Base/NormalObject.h"

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
};

