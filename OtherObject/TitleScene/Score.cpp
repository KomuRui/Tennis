#include "Score.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "Referee.h"

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
	//�X�R�A�\�̏�����
	ARGUMENT_INITIALIZE(scoreTable_[TennisCourtName::Z_MINUS_COURT], ZERO);
	ARGUMENT_INITIALIZE(scoreTable_[TennisCourtName::Z_PLUS_COURT], ZERO);
	ARGUMENT_INITIALIZE(table[0],LOVE);
	ARGUMENT_INITIALIZE(table[1],FIFTEEN);
	ARGUMENT_INITIALIZE(table[2],THIRTY);
	ARGUMENT_INITIALIZE(table[3],FORTY);

	//�e�L�X�g�̏�����
	ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_MINUS_COURT].first, new Text);
	ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_PLUS_COURT].first, new Text);
	ARGUMENT_INITIALIZE(pHyphenText_, new Text);
	scoreText_[TennisCourtName::Z_MINUS_COURT].first->Initialize("Text/NumberFont.png", 128, 256, 10);
	scoreText_[TennisCourtName::Z_PLUS_COURT].first->Initialize("Text/NumberFont.png", 128, 256, 10);
	pHyphenText_->Initialize();
	ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_PLUS_COURT].second, XMFLOAT2(-0.2f,0.87f));
	ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_MINUS_COURT].second, XMFLOAT2(0.2f, 0.87f));
	ARGUMENT_INITIALIZE(hyphenTextPosition_.x, ZERO);
	ARGUMENT_INITIALIZE(hyphenTextPosition_.y, 0.85f);
}

//�`��
void Score::Draw()
{
	//�e�L�X�g
	scoreText_[TennisCourtName::Z_PLUS_COURT].first->NumberDraw(scoreText_[TennisCourtName::Z_PLUS_COURT].second.x,scoreText_[TennisCourtName::Z_PLUS_COURT].second.y, table[scoreTable_[TennisCourtName::Z_PLUS_COURT]], 1, 0.05f);

	//�����E���\���̃X�R�A��0�Ȃ�
	if (scoreTable_[TennisCourtName::Z_MINUS_COURT] == ZERO)
		scoreText_[TennisCourtName::Z_MINUS_COURT].first->NumberDraw(scoreText_[TennisCourtName::Z_MINUS_COURT].second.x, scoreText_[TennisCourtName::Z_MINUS_COURT].second.y, table[scoreTable_[TennisCourtName::Z_MINUS_COURT]], 1, 0.05f);
	else
		scoreText_[TennisCourtName::Z_MINUS_COURT].first->NumberDraw(scoreText_[TennisCourtName::Z_MINUS_COURT].second.x - 80, scoreText_[TennisCourtName::Z_MINUS_COURT].second.y, table[scoreTable_[TennisCourtName::Z_MINUS_COURT]], 1, 0.05f);

	pHyphenText_->Draw(hyphenTextPosition_.x, hyphenTextPosition_.y, L"-", 1, 0.05f);
}

//�X�R�A���Z
void Score::AddScore(TennisCourtName n)
{
	//�ǂ��炩���Q�[�����擾�����̂Ȃ�
	if (table.size() <= scoreTable_[n] + 1)
	{
		//�X�R�A������Ԃɂ��Ă���
		ARGUMENT_INITIALIZE(scoreTable_[TennisCourtName::Z_MINUS_COURT], ZERO);
		ARGUMENT_INITIALIZE(scoreTable_[TennisCourtName::Z_PLUS_COURT], ZERO);

		//�Q�[���擾�֐����Ă�
		GameManager::GetReferee()->GetGame();

		return;
	}

	//�X�R�A���Z
	scoreTable_[n]++; 

	//�|�C���g�擾�֐����Ă�
	GameManager::GetReferee()->GetPoint();
}