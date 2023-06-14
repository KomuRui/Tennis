#pragma once
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "TennisCourt.h"
#include <map>

//�e�j�X�̃X�R�A
class Score
{
	map<TennisCourtName, int> scoreTable_;					//�X�R�A�\
	map<TennisCourtName, pair<Text*, XMFLOAT3>> scoreText_; //�X�R�A�̃e�L�X�g�\���p

	Text* pHyphenText_;            //�n�C�t���\������p
	XMFLOAT3 hyphenTextPosition_;  //�e�L�X�g�̃|�W�V����

	XMFLOAT3 scale_;               //�g�嗦

	EasingMove zPlusCourtEasingPos_;     //�ʒu�C�[�W���O�p
	EasingMove zMinusCourtEasingPos_;    //�ʒu�C�[�W���O�p
	EasingMove hyphenEasingPos_;         //�ʒu�C�[�W���O�p
	EasingMove scaleEasing_;             //�g�嗦�C�[�W���O�p

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

