#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/HermiteSplineMove.h"

/// <summary>
/// ���[�h�I���V�[��
/// </summary>
class ModeSelectScene : public GameObject
{

public:

	//�R���X�g���N�^
	ModeSelectScene(GameObject* parent);

	//�f�X�g���N�^
	~ModeSelectScene();

	//������
	void Initialize() override;

};

