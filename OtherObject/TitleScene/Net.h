#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// �l�b�g
/// </summary>
class Net : public NormalObject
{
public:

	//�R���X�g���N�^
	Net(GameObject* parent, std::string modelPath, std::string name);

	//�f�X�g���N�^
	~Net() {};
};

