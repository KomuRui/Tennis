#pragma once
#include "Base/NormalObject.h"
#include "Engine/Component/Collider/SphereCollider.h"

/// <summary>
/// �e�j�X�R�[�g���f��
/// </summary>
class test : public NormalObject
{

	//�����蔻��
	SphereCollider* sphere_;     //���^�̓����蔻��

public:

	//�R���X�g���N�^
	test(GameObject* parent, std::string modelPath, std::string name);

	//�f�X�g���N�^
	~test() {};

	//������
	void ChildInitialize() override;

	void ChildUpdate() override;
};

