#pragma once
#include "../EasingImage.h"

/// <summary>
/// ����UI
/// </summary>
class SphereFootUI : public EasingImage
{

public:

	//�R���X�g���N�^
	SphereFootUI(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

};

