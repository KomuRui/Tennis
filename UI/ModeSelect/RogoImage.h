#pragma once
#include "../EasingImage.h"

/// <summary>
/// ���S�摜
/// </summary>
class RogoImage : public EasingImage
{

public:

	//�R���X�g���N�^
	RogoImage(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

};

