#pragma once
#include "../ImageBase.h"

/// <summary>
/// �J�n�摜
/// </summary>
class StartImage : public ImageBase
{

	int sign_;       //����
	float nowAlpha_; //���݂̓����x

public:

	//�R���X�g���N�^
	StartImage(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

};

