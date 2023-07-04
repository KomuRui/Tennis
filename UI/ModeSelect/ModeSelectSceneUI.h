#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"

/// <summary>
/// ���[�h�I���V�[����UI
/// </summary>
class ModeSelectSceneUI : public GameObject
{

	//�eUI�쐬�p
	std::unique_ptr<CreateStage> pCreateImage_ = std::make_unique<CreateStage>();
	std::unique_ptr<CreateStage> pCreateButton_ = std::make_unique<CreateStage>();

public:

	//�R���X�g���N�^
	ModeSelectSceneUI(GameObject* parent);

	//�f�X�g���N�^
	~ModeSelectSceneUI() {};

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

};

