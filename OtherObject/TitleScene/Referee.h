#pragma once
#include "Score.h"

/// <summary>
/// �R��
/// </summary>
class Referee
{
	Score* score_; //�X�R�A

public:

	//�R���X�g���N�^
	Referee();
	
	//�f�X�g���N�^
	~Referee() {};

	//�`��
	void Draw();
};

