#pragma once
#include "ButtonBase.h"
#include "../../Engine/Component/EasingMove.h"

/// <summary>
/// �C�[�W���O�ړ�������{�^����\��������N���X
/// </summary>
class EasingButton : public ButtonBase
{
protected:

	//�C�[�W���O�p
	std::unique_ptr<EasingMove> easing_;


public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	EasingButton(GameObject* parent, std::string modelPath, std::string name);

	//�X�V
	void ChildButtonUpdate() override;

	//�q���p�̍X�V
	virtual void EasingButtonChileUpdate() {};
};

