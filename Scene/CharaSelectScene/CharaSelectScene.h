#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �L�����I���V�[��
/// </summary>
class CharaSelectScene : public GameObject
{

public:

	//�R���X�g���N�^
	CharaSelectScene(GameObject* parent);

	//�f�X�g���N�^
	~CharaSelectScene();

	//������
	void Initialize() override;

};

