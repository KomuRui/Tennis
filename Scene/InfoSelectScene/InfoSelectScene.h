#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �Q�[�����I���V�[��
/// </summary>
class InfoSelectScene : public GameObject
{

public:

	//�R���X�g���N�^
	InfoSelectScene(GameObject* parent);

	//�f�X�g���N�^
	~InfoSelectScene();

	//������
	void Initialize() override;

};

