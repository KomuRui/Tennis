#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/HermiteSplineMove.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TestScene : public GameObject
{


public:

	//�R���X�g���N�^
	TestScene(GameObject* parent);

	//�f�X�g���N�^
	~TestScene();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

};

