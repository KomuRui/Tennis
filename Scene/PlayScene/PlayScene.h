#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �v���C�V�[��
/// </summary>
class PlayScene : public GameObject
{

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	//�f�X�g���N�^
	~PlayScene();

	//������
	void Initialize() override;

	/// <summary>
	/// UI�쐬
	/// </summary>
	void CreateUI();
};

