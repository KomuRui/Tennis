#pragma once
#include "../EasingImage.h"

/// <summary>
/// �o�E���hUI
/// </summary>
class BoundUI : public EasingImage
{

public:

	//�R���X�g���N�^
	BoundUI(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

};

