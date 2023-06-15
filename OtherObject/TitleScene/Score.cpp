#include "Score.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Manager/GameManager/GameManager.h"
#include "Referee.h"

//�萔
namespace
{
	static const int LOVE = 0;
	static const int FIFTEEN = 15;
	static const int THIRTY = 30;
	static const int FORTY = 40;

	static const XMFLOAT3 Z_PLUS_COURT_SCORE_TEXT =  { -0.2f ,0.87f,ZERO };
	static const XMFLOAT3 Z_MINUS_COURT_SCORE_TEXT = { 0.2f ,0.87f,ZERO };
	static const XMFLOAT3 HYPHEN_TEXT = { ZERO ,0.87f,ZERO };
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
	ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_PLUS_COURT].second.pos, Z_PLUS_COURT_SCORE_TEXT);
	ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_PLUS_COURT].second.scale, XMFLOAT2(1.0f, 1.0f));
	ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_MINUS_COURT].second.pos,Z_MINUS_COURT_SCORE_TEXT);
	ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_MINUS_COURT].second.scale, XMFLOAT2(1.0f, 1.0f));
	ARGUMENT_INITIALIZE(hyphenTextInfo_.pos, HYPHEN_TEXT);
	ARGUMENT_INITIALIZE(hyphenTextInfo_.scale, XMFLOAT2(1.0f, 1.0f));

	//�g�嗦������
	ARGUMENT_INITIALIZE(allScale_,XMFLOAT3(1.0f,1.0f,ZERO));
	ARGUMENT_INITIALIZE(pointGetScale_,XMFLOAT3(1.0f,1.0f,ZERO));
}

//�`��
void Score::Draw()
{

	//�C�[�W���O�œ���
	zPlusCourtEasingPos_->Move();
	zMinusCourtEasingPos_->Move();
	hyphenEasingPos_->Move();
	if (allScaleEasing_->Move())
		ChangeScoreEasing();
	else
	{
		ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_PLUS_COURT].second.scale, XMFLOAT2(allScale_.x, allScale_.y));
		ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_MINUS_COURT].second.scale, XMFLOAT2(allScale_.x, allScale_.y));
		ARGUMENT_INITIALIZE(hyphenTextInfo_.scale, XMFLOAT2(allScale_.x, allScale_.y));
	}
	
	//�f�o�b�O�p
	if (Input::IsKeyDown(DIK_A))
		AddScore(TennisCourtName::Z_PLUS_COURT);
	else if(Input::IsKeyDown(DIK_D))
		AddScore(TennisCourtName::Z_MINUS_COURT);

	//�C�[�W���O��̈ʒu���i�[����ϐ��p��
	XMFLOAT2 zPlusCourtAfterPos = XMFLOAT2(scoreText_[TennisCourtName::Z_PLUS_COURT].second.pos.x, scoreText_[TennisCourtName::Z_PLUS_COURT].second.pos.y);
	XMFLOAT2 zMinusCourtAfterPos = XMFLOAT2(scoreText_[TennisCourtName::Z_MINUS_COURT].second.pos.x, scoreText_[TennisCourtName::Z_MINUS_COURT].second.pos.y);

	//�X�R�A��0�̎������ʒu���C��
	if (scoreTable_[TennisCourtName::Z_PLUS_COURT] == ZERO)
		zPlusCourtAfterPos.x += 0.05f;

	if (scoreTable_[TennisCourtName::Z_MINUS_COURT] == ZERO)
		zMinusCourtAfterPos.x -= 0.055f;

	//�`��
	scoreText_[TennisCourtName::Z_PLUS_COURT].first->NumberDraw(zPlusCourtAfterPos.x, zPlusCourtAfterPos.y, table[scoreTable_[TennisCourtName::Z_PLUS_COURT]], scoreText_[TennisCourtName::Z_PLUS_COURT].second.scale, 0.05f);
	scoreText_[TennisCourtName::Z_MINUS_COURT].first->NumberDraw(zMinusCourtAfterPos.x, zMinusCourtAfterPos.y, table[scoreTable_[TennisCourtName::Z_MINUS_COURT]], scoreText_[TennisCourtName::Z_MINUS_COURT].second.scale, 0.05f);

	pHyphenText_->Draw(hyphenTextInfo_.pos.x, hyphenTextInfo_.pos.y, L"-", hyphenTextInfo_.scale, 0.05f);
}

//�X�R�A���Z
void Score::AddScore(TennisCourtName n)
{
	//�|�C���g�擾�����e�j�X�R�[�g�̖��O��ۑ����Ă���
	ARGUMENT_INITIALIZE(pointGetTennisCourtName_, n);

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

	////////////////////////////�C�[�W���O�ݒ�

	//�C�[�W���O��̈ʒu���i�[����ϐ��p��
	XMFLOAT3 zPlusCourtAfterPos = XMFLOAT3(ZERO,ZERO,ZERO);
	XMFLOAT3 zMinusCourtAfterPos = XMFLOAT3(ZERO,ZERO,ZERO);

	//�X�R�A��0�̎��Ƃ���ȊO�̈ʒu��ς���
	if (scoreTable_[TennisCourtName::Z_PLUS_COURT] == ZERO)
		zPlusCourtAfterPos = XMFLOAT3(-0.5f, ZERO, ZERO);
	else
		zPlusCourtAfterPos = XMFLOAT3(-0.7f, ZERO, ZERO);

	//�X�R�A��0�̎��Ƃ���ȊO�̈ʒu��ς���
	if(scoreTable_[TennisCourtName::Z_MINUS_COURT] == ZERO)
		zMinusCourtAfterPos = XMFLOAT3(0.55f, ZERO, ZERO);
	else
		zMinusCourtAfterPos = XMFLOAT3(0.38f, ZERO, ZERO);

	zPlusCourtEasingPos_->Reset(&scoreText_[TennisCourtName::Z_PLUS_COURT].second.pos, scoreText_[TennisCourtName::Z_PLUS_COURT].second.pos, zPlusCourtAfterPos, 1.5f, Easing::OutBounce);
	zMinusCourtEasingPos_->Reset(&scoreText_[TennisCourtName::Z_MINUS_COURT].second.pos, scoreText_[TennisCourtName::Z_MINUS_COURT].second.pos, zMinusCourtAfterPos, 1.5f, Easing::OutBounce);
	hyphenEasingPos_->Reset(&hyphenTextInfo_.pos, hyphenTextInfo_.pos, XMFLOAT3(ZERO, ZERO, ZERO), 1.5f, Easing::OutBounce);
	allScaleEasing_->Reset(&allScale_, allScale_, XMFLOAT3(2.5f, 2.5f, ZERO), 1.5f, Easing::OutCubic);
	pointGetScaleEasing_->Reset(&pointGetScale_, XMFLOAT3(2.5f, 2.5f, ZERO), XMFLOAT3(2.5f, 0.3f, ZERO), 0.2f, Easing::OutCubic);
	pointGetScaleEasing_->ResetEndEasingCount();

	//�|�C���g�擾�֐����Ă�
	GameManager::GetReferee()->GetPoint();
}

/// <summary>
/// �ʒu��߂�����
/// </summary>
void Score::ReturnMovePos()
{
	zPlusCourtEasingPos_->Reset(&scoreText_[TennisCourtName::Z_PLUS_COURT].second.pos, scoreText_[TennisCourtName::Z_PLUS_COURT].second.pos, Z_PLUS_COURT_SCORE_TEXT, 1.0f, Easing::OutCubic);
	hyphenEasingPos_->Reset(&hyphenTextInfo_.pos, hyphenTextInfo_.pos, HYPHEN_TEXT, 1.0f, Easing::OutCubic);
	allScaleEasing_->Reset(&allScale_, allScale_, XMFLOAT3(1.0f, 1.0f, ZERO), 1.0f, Easing::OutCubic);

	//�C�[�W���O��̈ʒu���i�[����ϐ��p��
	XMFLOAT3 afterPos = Z_MINUS_COURT_SCORE_TEXT;

	//�X�R�A��0�̎��Ƃ���ȊO�̈ʒu��ς���
	if (scoreTable_[TennisCourtName::Z_MINUS_COURT] != ZERO)
		afterPos.x -= 0.08f;

	//���Z�b�g
	zMinusCourtEasingPos_->Reset(&scoreText_[TennisCourtName::Z_MINUS_COURT].second.pos, scoreText_[TennisCourtName::Z_MINUS_COURT].second.pos, afterPos, 1.0f, Easing::OutCubic);
}

/// <summary>
/// �C�[�W���O�ŃX�R�A�ύX
/// </summary>
void Score::ChangeScoreEasing()
{
	if (pointGetScaleEasing_->Move())
	{
		if (pointGetScaleEasing_->GetEndEasingCount() == 2)
		{
			ReturnMovePos();
		}
		else
			pointGetScaleEasing_->Reset(&pointGetScale_, pointGetScale_, XMFLOAT3(2.5f, 2.5f, ZERO), 0.8f, Easing::OutBack);
	}

	if (pointGetScaleEasing_->GetEndEasingCount() < 2)
	{
		ARGUMENT_INITIALIZE(scoreText_[pointGetTennisCourtName_].second.scale, XMFLOAT2(pointGetScale_.x, pointGetScale_.y));
	}
}