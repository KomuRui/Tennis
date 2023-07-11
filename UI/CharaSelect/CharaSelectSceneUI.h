#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include <map>

/// <summary>
/// �L�����I���V�[����UI
/// </summary>
class CharaSelectSceneUI : public GameObject
{

	//�eUI�쐬�p
	std::unique_ptr<CreateStage> pCreateImage_ = std::make_unique<CreateStage>();

	//Controller0,1�̑I�����Ă鎞�̉摜�ƃg�����X�t�H�[�����i�[
	map<int, pair<int, std::shared_ptr<Transform>>> selectPict_;

public:

	//�R���X�g���N�^
	CharaSelectSceneUI(GameObject* parent);

	//�f�X�g���N�^
	~CharaSelectSceneUI() {};

	//������
	void Initialize() override;

	/// <summary>
	/// �g�����X�t�H�[���ݒ�
	/// </summary>
	/// <param name="t">�ݒ肵�����g�����X�t�H�[��</param>
	/// <param name="numController">�R���g���[���[�ԍ�</param>
	void SetTransform(const Transform& t, int numController);

	/// <summary>
	/// �e�R���g���[���[�̑I���摜�̃g�����X�t�H�[�����擾
	/// </summary>
	/// <param name="numController">�R���g���[���[�ԍ�</param>
	/// <returns>�g�����X�t�H�[��</returns>
	Transform* GetTrasnform(int numController) { return selectPict_[numController].second.get(); }

};

