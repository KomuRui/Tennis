#pragma once
#include "../EasingImage.h"

/// <summary>
/// �m�F�摜
/// </summary>
class QuestionImage : public EasingImage
{

public:

	//�R���X�g���N�^
	QuestionImage(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

};

