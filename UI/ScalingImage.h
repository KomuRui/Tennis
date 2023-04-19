#pragma once
#include "../Engine/GameObject/GameObject.h"
#include "ImageBase.h"

/// <summary>
/// �g��k���摜��\��������N���X
/// </summary>
class ScalingImage : public ImageBase
{
	////�ϐ�

	XMVECTOR  beforeScale_;		  //��Ԃ���O�̊g�嗦�ۑ�
	XMVECTOR  targetScale_;       //���̖ڕW�Ƃ���g�嗦

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ScalingImage(GameObject* parent, std::string modelPath, std::string name);

	//�X�V�̑O�Ɉ�x�����Ă΂��
	void ChildStartUpdate() override;

	//�X�V
	void ChildUpdate() override;
};

