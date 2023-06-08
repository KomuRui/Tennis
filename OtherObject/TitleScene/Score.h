#pragma once
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Text.h"
#include <map>

//�e�j�X�̃X�R�A
class Score
{
	int player1Score_;  //�v���C���[1�̃X�R�A
	int player2Score_;  //�v���C���[1�̃X�R�A

	Text* pPlayerScoreText_;	   //�v���C���[�X�R�A�\������p
	XMFLOAT2 playerTextPosition_;  //�e�L�X�g�̃|�W�V����

	Text* pEnemyScoreText_;	       //�G�l�~�[�X�R�A�\������p
	XMFLOAT2 enemyTextPosition_;   //�e�L�X�g�̃|�W�V����

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
	/// �v���C���[1�X�R�A���Z
	/// </summary>
	void AddPlayer1Score() { player1Score_++; }

	/// <summary>
	/// �v���C���[2�X�R�A���Z
	/// </summary>
	void AddPlayer2Score() { player2Score_++; }

};

