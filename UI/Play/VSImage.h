#pragma once
#include "../EasingImage.h"

/// <summary>
/// VS�摜
/// </summary>
class VSImage : public EasingImage
{

public:

	//�R���X�g���N�^
	VSImage(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

};

