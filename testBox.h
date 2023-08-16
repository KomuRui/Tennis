#pragma once
#include "Base/NormalObject.h"
#include "Engine/Component/Collider/BoxCollider.h"

/// <summary>
/// �e�j�X�R�[�g���f��
/// </summary>
class testBox : public NormalObject
{

	//�����蔻��
	BoxCollider* box_;     //���^�̓����蔻��

public:

	//�R���X�g���N�^
	testBox(GameObject* parent, std::string modelPath, std::string name);

	//�f�X�g���N�^
	~testBox() {};

	//������
	void ChildInitialize() override;

	void ChildUpdate() override;
};

