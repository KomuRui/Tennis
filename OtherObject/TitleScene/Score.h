#pragma once
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Text.h"
#include "TennisCourt.h"
#include <map>

//�e�j�X�̃X�R�A
class Score
{
	
	map<TennisCourtName, int> scoreTable_;					//�X�R�A�\
	map<TennisCourtName, pair<Text*, XMFLOAT2>> scoreText_; //�X�R�A�̃e�L�X�g�\���p

	Text* pHyphenText_;            //�n�C�t���\������p
	XMFLOAT2 hyphenTextPosition_;  //�e�L�X�g�̃|�W�V����

	std::map<int, int> table;      //�X�R�A�\(�L�[:�J�E���g��0,1,2,3 �o�����[:�\������X�R�A��)

public:

	//�R���X�g���N�^
	Score();

	/// <summary>
	/// �`��(�R�C���̎擾����Player���C�t�̕\��)
	/// </summary>
	void Draw();

	/// <summary>
	/// �X�R�A���Z
	/// </summary>
	void AddScore(TennisCourtName n);

};

