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

	//�f�X�g���N�^
	~Racket() {};

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

};

