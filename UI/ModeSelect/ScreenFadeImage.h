#pragma once
#include "../ImageBase.h"

/// <summary>
/// �X�N���[���摜(Fade�p)
/// </summary>
class ScreenFadeImage : public ImageBase
{

public:

	//�R���X�g���N�^
	ScreenFadeImage(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;
};

