#pragma once
#include "../EasingImage.h"

/// <summary>
/// �L�����I���摜(Fade�p)
/// </summary>
class CharaSelectScreenFadeImage : public EasingImage
{

public:

	//�R���X�g���N�^
	CharaSelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

	//�X�V
	void EasingImageChileUpdate() override;

};
