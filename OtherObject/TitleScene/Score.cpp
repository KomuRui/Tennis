#include "Score.h"
#include "../../Engine/DirectX/Input.h"

//�萔
namespace
{
	static const int LOVE = 0;
	static const int FIFTEEN = 15;
	static const int THIRTY = 30;
	static const int FORTY = 40;
}

//�R���X�g���N�^
Score::Score()
{
	ARGUMENT_INITIALIZE(player1Score_, ZERO);
	ARGUMENT_INITIALIZE(player2Score_, ZERO);

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

//�`��
void Score::Draw()
{
	if (Input::IsKeyDown(DIK_A))
		AddPlayer1Score();
	if (Input::IsKeyDown(DIK_D))
		AddPlayer2Score();

	//�e�L�X�g
	pPlayerScoreText_->NumberDraw((int)playerTextPosition_.x, (int)playerTextPosition_.y, table[player1Score_], 1, 0.05f);

	//�����G�̃X�R�A��0�Ȃ�
	if (player2Score_ == ZERO)
		pEnemyScoreText_->NumberDraw((int)enemyTextPosition_.x, (int)enemyTextPosition_.y, table[player2Score_], 1, 0.05f);
	else
		pEnemyScoreText_->NumberDraw((int)enemyTextPosition_.x - 80, (int)enemyTextPosition_.y, table[player2Score_], 1, 0.05f);

	pHyphenText_->Draw((int)hyphenTextPosition_.x, (int)hyphenTextPosition_.y, L"-", 1, 0.05f);
}
