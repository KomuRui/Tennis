#pragma once
#include "../EasingImage.h"

/// <summary>
/// �v���C���[�摜
/// </summary>
class PlayerImage : public EasingImage
{

public:

	//�R���X�g���N�^
	PlayerImage(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

};

