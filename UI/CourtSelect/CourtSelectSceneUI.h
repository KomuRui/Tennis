#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"

/// <summary>
/// �R�[�g�I���V�[����UI
/// </summary>
class CourtSelectSceneUI : public GameObject
{

	//�eUI�쐬�p
	std::unique_ptr<CreateStage> pCreateImage_ = std::make_unique<CreateStage>();

public:

	//�R���X�g���N�^
	CourtSelectSceneUI(GameObject* parent);

	//�f�X�g���N�^
	~CourtSelectSceneUI() {};

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

};

