#pragma once
#include "../EasingImage.h"

/// <summary>
/// �X�N���[���摜(Fade�p)
/// </summary>
class CharaSelectScreenFadeImage : public EasingImage
{

	//���݂̓����x
	float nowAlpha_;

public:

	//�R���X�g���N�^
	CharaSelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

};

