#pragma once
#include "../EasingImage.h"

/// <summary>
/// �������I���摜(Fade�p)
/// </summary>
class InfoSelectScreenFadeImage : public EasingImage
{

public:

	//�R���X�g���N�^
	InfoSelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

	//�X�V
	void EasingImageChileUpdate() override;

};

