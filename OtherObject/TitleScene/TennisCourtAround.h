#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// �e�j�X�R�[�g�̎���̃��f��
/// </summary>
class TennisCourtAround : public NormalObject
{
public:

	//�R���X�g���N�^
	TennisCourtAround(GameObject* parent, std::string modelPath, std::string name);

	//�f�X�g���N�^
	~TennisCourtAround() {};

	//������
	void ChildInitialize() override;
};

