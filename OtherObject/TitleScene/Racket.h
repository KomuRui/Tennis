#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// ���P�b�g
/// </summary>
class Racket : public NormalObject
{
public:

	//�R���X�g���N�^
	Racket(GameObject* parent, std::string modelPath, std::string name);
	Racket(GameObject* parent);

	//������
	void ChildInitialize() override;

	//�f�X�g���N�^
	~Racket() {};
};

