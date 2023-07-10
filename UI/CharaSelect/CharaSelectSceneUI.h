#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"

/// <summary>
/// �L�����I���V�[����UI
/// </summary>
class CharaSelectSceneUI : public GameObject
{

	//�eUI�쐬�p
	std::unique_ptr<CreateStage> pCreateImage_ = std::make_unique<CreateStage>();

public:

	//�R���X�g���N�^
	CharaSelectSceneUI(GameObject* parent);

	//�f�X�g���N�^
	~CharaSelectSceneUI() {};

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

};

