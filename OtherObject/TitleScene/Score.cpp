#include "Score.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Manager/GameManager/GameManager.h"
#include "Referee.h"

//定数
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

//コンストラクタ
Score::Score()
{
	//スコア表の初期化
	ARGUMENT_INITIALIZE(scoreTable_[TennisCourtName::Z_MINUS_COURT], ZERO);
	ARGUMENT_INITIALIZE(scoreTable_[TennisCourtName::Z_PLUS_COURT], ZERO);
	ARGUMENT_INITIALIZE(table[0],LOVE);
	ARGUMENT_INITIALIZE(table[1],FIFTEEN);
	ARGUMENT_INITIALIZE(table[2],THIRTY);
	ARGUMENT_INITIALIZE(table[3],FORTY);

	//テキストの初期化
	ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_MINUS_COURT].first, new Text);
	ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_PLUS_COURT].first, new Text);
	ARGUMENT_INITIALIZE(pHyphenText_, new Text);
	scoreText_[TennisCourtName::Z_MINUS_COURT].first->Initialize("Text/NumberFont.png", 128, 256, 10);
	scoreText_[TennisCourtName::Z_PLUS_COURT].first->Initialize("Text/NumberFont.png", 128, 256, 10);
	pHyphenText_->Initialize();
	ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_PLUS_COURT].second, Z_PLUS_COURT_SCORE_TEXT);
	ARGUMENT_INITIALIZE(scoreText_[TennisCourtName::Z_MINUS_COURT].second,Z_MINUS_COURT_SCORE_TEXT);
	ARGUMENT_INITIALIZE(hyphenTextPosition_.x, HYPHEN_TEXT.x);
	ARGUMENT_INITIALIZE(hyphenTextPosition_.y, HYPHEN_TEXT.y);

	//拡大率初期化
	ARGUMENT_INITIALIZE(scale_,XMFLOAT3(ZERO,1.0f,ZERO));
}

//描画
void Score::Draw()
{
	zPlusCourtEasingPos_.Move();
	zMinusCourtEasingPos_.Move();
	hyphenEasingPos_.Move();
	if (scaleEasing_.Move())
	{
		zPlusCourtEasingPos_.Reset(&scoreText_[TennisCourtName::Z_PLUS_COURT].second, scoreText_[TennisCourtName::Z_PLUS_COURT].second, Z_PLUS_COURT_SCORE_TEXT, 1.5f, Easing::OutCubic);
		zMinusCourtEasingPos_.Reset(&scoreText_[TennisCourtName::Z_MINUS_COURT].second, scoreText_[TennisCourtName::Z_MINUS_COURT].second, Z_MINUS_COURT_SCORE_TEXT, 1.5f, Easing::OutCubic);
		hyphenEasingPos_.Reset(&hyphenTextPosition_, hyphenTextPosition_, HYPHEN_TEXT, 1.5f, Easing::OutCubic);
		scaleEasing_.Reset(&scale_, scale_, XMFLOAT3(ZERO, 1.0f, ZERO), 1.5f, Easing::OutCubic);
	}

	if (Input::IsKeyDown(DIK_A))
		AddScore(TennisCourtName::Z_PLUS_COURT);
	else if(Input::IsKeyDown(DIK_D))
		AddScore(TennisCourtName::Z_MINUS_COURT);

	//テキスト
	scoreText_[TennisCourtName::Z_PLUS_COURT].first->NumberDraw(scoreText_[TennisCourtName::Z_PLUS_COURT].second.x,scoreText_[TennisCourtName::Z_PLUS_COURT].second.y, table[scoreTable_[TennisCourtName::Z_PLUS_COURT]], scale_.y, 0.05f);

	//もし右側表示のスコアが0なら
	if (scoreTable_[TennisCourtName::Z_MINUS_COURT] == ZERO)
		scoreText_[TennisCourtName::Z_MINUS_COURT].first->NumberDraw(scoreText_[TennisCourtName::Z_MINUS_COURT].second.x - 0.01f, scoreText_[TennisCourtName::Z_MINUS_COURT].second.y, table[scoreTable_[TennisCourtName::Z_MINUS_COURT]], scale_.y, 0.05f);
	else
		scoreText_[TennisCourtName::Z_MINUS_COURT].first->NumberDraw(scoreText_[TennisCourtName::Z_MINUS_COURT].second.x, scoreText_[TennisCourtName::Z_MINUS_COURT].second.y, table[scoreTable_[TennisCourtName::Z_MINUS_COURT]], scale_.y, 0.05f);

	pHyphenText_->Draw(hyphenTextPosition_.x, hyphenTextPosition_.y, L"-", scale_.y, 0.05f);
}

//スコア加算
void Score::AddScore(TennisCourtName n)
{
	//どちらかがゲームを取得したのなら
	if (table.size() <= scoreTable_[n] + 1)
	{
		//スコア初期状態にしておく
		ARGUMENT_INITIALIZE(scoreTable_[TennisCourtName::Z_MINUS_COURT], ZERO);
		ARGUMENT_INITIALIZE(scoreTable_[TennisCourtName::Z_PLUS_COURT], ZERO);

		//ゲーム取得関数を呼ぶ
		GameManager::GetReferee()->GetGame();

		return;
	}

	//スコア加算
	scoreTable_[n]++;

	////////////////////////////イージング処理

	if (scoreTable_[TennisCourtName::Z_PLUS_COURT] == ZERO)
		zPlusCourtEasingPos_.Reset(&scoreText_[TennisCourtName::Z_PLUS_COURT].second, scoreText_[TennisCourtName::Z_PLUS_COURT].second, XMFLOAT3(-0.5f, ZERO, ZERO), 1.5f, Easing::OutBounce);
	else
		zPlusCourtEasingPos_.Reset(&scoreText_[TennisCourtName::Z_PLUS_COURT].second, scoreText_[TennisCourtName::Z_PLUS_COURT].second, XMFLOAT3(-0.7f, ZERO, ZERO), 1.5f, Easing::OutBounce);

	if(scoreTable_[TennisCourtName::Z_MINUS_COURT] == ZERO)
		zMinusCourtEasingPos_.Reset(&scoreText_[TennisCourtName::Z_MINUS_COURT].second, scoreText_[TennisCourtName::Z_MINUS_COURT].second, XMFLOAT3(0.55f, ZERO, ZERO), 1.5f, Easing::OutBounce);
	else
		zMinusCourtEasingPos_.Reset(&scoreText_[TennisCourtName::Z_MINUS_COURT].second, scoreText_[TennisCourtName::Z_MINUS_COURT].second, XMFLOAT3(0.38f, ZERO, ZERO), 1.5f, Easing::OutBounce);

	hyphenEasingPos_.Reset(&hyphenTextPosition_, hyphenTextPosition_, XMFLOAT3(ZERO, ZERO, ZERO), 1.5f, Easing::OutCubic);
	scaleEasing_.Reset(&scale_, scale_, XMFLOAT3(ZERO, 2.5f, ZERO), 1.5f, Easing::OutCubic);

	//ポイント取得関数を呼ぶ
	GameManager::GetReferee()->GetPoint();
}