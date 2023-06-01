#include "ScoreManager.h"
#include "../../Engine/ResourceManager/Global.h"
#include "../GameManager/GameManager.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Text.h"
#include <map>

//�萔
namespace
{
	static const int LOVE = 0;
	static const int FIFTEEN = 15;
	static const int THIRTY = 30;
	static const int FORTY = 40;
}

//�e�j�X�̃X�R�A�Ǘ�
namespace ScoreManager
{
	///////////////////////////////�ϐ�//////////////////////////////////

	int playerScore_; //�v���C���[�̃X�R�A
	int enemyScore_;  //�G�l�~�[�̃X�R�A

	//�e�L�X�g
	Text* pPlayerScoreText_;	   //�v���C���[�X�R�A�\������p
	XMFLOAT2 playerTextPosition_;  //�e�L�X�g�̃|�W�V����

	Text* pEnemyScoreText_;	       //�G�l�~�[�X�R�A�\������p
	XMFLOAT2 enemyTextPosition_;   //�e�L�X�g�̃|�W�V����

	Text* pHyphenText_;            //�n�C�t���\������p
	XMFLOAT2 hyphenTextPosition_;  //�e�L�X�g�̃|�W�V����

	//�X�R�A�\(�L�[:�J�E���g��0,1,2,3 �o�����[:�\������X�R�A��)
	std::map<int, int> table;

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void ScoreManager::Initialize()
	{
		ARGUMENT_INITIALIZE(playerScore_, ZERO);
		ARGUMENT_INITIALIZE(enemyScore_, ZERO);

		//�X�R�A�\�̏�����
		table[0] = LOVE;
		table[1] = FIFTEEN;
		table[2] = THIRTY;
		table[3] = FORTY;

		//�e�L�X�g�̏�����
		ARGUMENT_INITIALIZE(pPlayerScoreText_, new Text);
		ARGUMENT_INITIALIZE(pEnemyScoreText_, new Text);
		ARGUMENT_INITIALIZE(pHyphenText_, new Text);
		pPlayerScoreText_->Initialize("Text/NumberFont.png", 128, 256, 10);
		pEnemyScoreText_->Initialize("Text/NumberFont.png", 128, 256, 10);
		pHyphenText_->Initialize();
		ARGUMENT_INITIALIZE(playerTextPosition_.x, 760);
		ARGUMENT_INITIALIZE(playerTextPosition_.y, 70);
		ARGUMENT_INITIALIZE(enemyTextPosition_.x, 1160);
		ARGUMENT_INITIALIZE(enemyTextPosition_.y, 70);
		ARGUMENT_INITIALIZE(hyphenTextPosition_.x, 965);
		ARGUMENT_INITIALIZE(hyphenTextPosition_.y, 75);
	}

	//�V�[���J�ڂ̎��̏�����
	void ScoreManager::SceneTransitionInitialize()
	{
		//�e�L�X�g�̏�����
		ARGUMENT_INITIALIZE(pPlayerScoreText_, new Text);
		ARGUMENT_INITIALIZE(pEnemyScoreText_, new Text);
		ARGUMENT_INITIALIZE(pHyphenText_, new Text);
		pPlayerScoreText_->Initialize("Text/NumberFont.png", 128, 256, 10);
		pEnemyScoreText_->Initialize("Text/NumberFont.png", 128, 256, 10);
		pHyphenText_->Initialize();
	}

	//�`��
	void ScoreManager::Draw()
	{
		if (Input::IsKeyDown(DIK_A))
			AddPlayerScore();
		if (Input::IsKeyDown(DIK_D))
			AddEnemyScore();

		//�e�L�X�g
		pPlayerScoreText_->NumberDraw((int)playerTextPosition_.x, (int)playerTextPosition_.y, table[playerScore_], 1, 0.05f);

		//�����G�̃X�R�A��0�Ȃ�
		if(enemyScore_ == ZERO)
			pEnemyScoreText_->NumberDraw((int)enemyTextPosition_.x, (int)enemyTextPosition_.y, table[enemyScore_], 1, 0.05f);
		else
			pEnemyScoreText_->NumberDraw((int)enemyTextPosition_.x - 80, (int)enemyTextPosition_.y, table[enemyScore_], 1, 0.05f);

		pHyphenText_->Draw((int)hyphenTextPosition_.x, (int)hyphenTextPosition_.y, L"-", 1, 0.05f);
	}

	//�v���C���[�X�R�A���Z
	void ScoreManager::AddPlayerScore()
	{
		playerScore_++;
	}

	//�G�l�~�[�X�R�A���Z
	void ScoreManager::AddEnemyScore()
	{
		enemyScore_++;
	}

	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////


}