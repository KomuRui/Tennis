#pragma once
#include "../EasingImage.h"

/// <summary>
/// �X�N���[���摜(Fade�p)
/// </summary>
class CourtSelectScreenFadeImage : public EasingImage
{

public:

	//�R���X�g���N�^
	CourtSelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

	//�X�V
	void EasingImageChileUpdate() override;

};

