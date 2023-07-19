#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"

/// <summary>
/// �Q�[�����I���V�[����UI
/// </summary>
class InfoSelectSceneUI : public GameObject
{

	//�eUI�쐬�p
	std::unique_ptr<CreateStage> pCreateImage_ = std::make_unique<CreateStage>();
	std::unique_ptr<CreateStage> pCreateButton_ = std::make_unique<CreateStage>();

public:

	//�R���X�g���N�^
	InfoSelectSceneUI(GameObject* parent);

	//�f�X�g���N�^
	~InfoSelectSceneUI() {};

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

};

