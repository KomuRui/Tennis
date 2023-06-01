#include "ScoreManager.h"
#include "../../Engine/ResourceManager/Global.h"
#include "../GameManager/GameManager.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Text.h"
#include <map>

//定数
namespace
{
	static const int LOVE = 0;
	static const int FIFTEEN = 15;
	static const int THIRTY = 30;
	static const int FORTY = 40;
}

//テニスのスコア管理
namespace ScoreManager
{
	///////////////////////////////変数//////////////////////////////////

	int playerScore_; //プレイヤーのスコア
	int enemyScore_;  //エネミーのスコア

	//テキスト
	Text* pPlayerScoreText_;	   //プレイヤースコア表示する用
	XMFLOAT2 playerTextPosition_;  //テキストのポジション

	Text* pEnemyScoreText_;	       //エネミースコア表示する用
	XMFLOAT2 enemyTextPosition_;   //テキストのポジション

	Text* pHyphenText_;            //ハイフン表示する用
	XMFLOAT2 hyphenTextPosition_;  //テキストのポジション

	//スコア表(キー:カウント数0,1,2,3 バリュー:表示するスコア数)
	std::map<int, int> table;

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void ScoreManager::Initialize()
	{
		ARGUMENT_INITIALIZE(playerScore_, ZERO);
		ARGUMENT_INITIALIZE(enemyScore_, ZERO);

		//スコア表の初期化
		table[0] = LOVE;
		table[1] = FIFTEEN;
		table[2] = THIRTY;
		table[3] = FORTY;

		//テキストの初期化
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

	//シーン遷移の時の初期化
	void ScoreManager::SceneTransitionInitialize()
	{
		//テキストの初期化
		ARGUMENT_INITIALIZE(pPlayerScoreText_, new Text);
		ARGUMENT_INITIALIZE(pEnemyScoreText_, new Text);
		ARGUMENT_INITIALIZE(pHyphenText_, new Text);
		pPlayerScoreText_->Initialize("Text/NumberFont.png", 128, 256, 10);
		pEnemyScoreText_->Initialize("Text/NumberFont.png", 128, 256, 10);
		pHyphenText_->Initialize();
	}

	//描画
	void ScoreManager::Draw()
	{
		if (Input::IsKeyDown(DIK_A))
			AddPlayerScore();
		if (Input::IsKeyDown(DIK_D))
			AddEnemyScore();

		//テキスト
		pPlayerScoreText_->NumberDraw((int)playerTextPosition_.x, (int)playerTextPosition_.y, table[playerScore_], 1, 0.05f);

		//もし敵のスコアが0なら
		if(enemyScore_ == ZERO)
			pEnemyScoreText_->NumberDraw((int)enemyTextPosition_.x, (int)enemyTextPosition_.y, table[enemyScore_], 1, 0.05f);
		else
			pEnemyScoreText_->NumberDraw((int)enemyTextPosition_.x - 80, (int)enemyTextPosition_.y, table[enemyScore_], 1, 0.05f);

		pHyphenText_->Draw((int)hyphenTextPosition_.x, (int)hyphenTextPosition_.y, L"-", 1, 0.05f);
	}

	//プレイヤースコア加算
	void ScoreManager::AddPlayerScore()
	{
		playerScore_++;
	}

	//エネミースコア加算
	void ScoreManager::AddEnemyScore()
	{
		enemyScore_++;
	}

	///////////////////////////////セットゲット関数//////////////////////////////////


}