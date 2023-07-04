#pragma once
#include "ImageBase.h"
#include "../Engine/Component/EasingMove.h"

/// <summary>
/// �C�[�W���O�ړ�������摜��\��������N���X
/// </summary>
class EasingImage : public ImageBase
{
protected:

	//�C�[�W���O�p
	std::unique_ptr<EasingMove> easing_; 


public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	EasingImage(GameObject* parent, std::string modelPath, std::string name);

	//�X�V
	void ChildUpdate() override;

	//�q���p�̍X�V
	virtual void EasingImageChileUpdate() {};
};

