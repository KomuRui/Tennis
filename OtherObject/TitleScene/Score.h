#pragma once
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Text.h"
#include <map>

//テニスのスコア
class Score
{
	int player1Score_;  //プレイヤー1のスコア
	int player2Score_;  //プレイヤー1のスコア

	Text* pPlayerScoreText_;	   //プレイヤースコア表示する用
	XMFLOAT2 playerTextPosition_;  //テキストのポジション

	Text* pEnemyScoreText_;	       //エネミースコア表示する用
	XMFLOAT2 enemyTextPosition_;   //テキストのポジション

	Text* pHyphenText_;            //ハイフン表示する用
	XMFLOAT2 hyphenTextPosition_;  //テキストのポジション

	std::map<int, int> table;      //スコア表(キー:カウント数0,1,2,3 バリュー:表示するスコア数)

public:

	//コンストラクタ
	Score();

	/// <summary>
	/// 描画(コインの取得数やPlayerライフの表示)
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤー1スコア加算
	/// </summary>
	void AddPlayer1Score() { player1Score_++; }

	/// <summary>
	/// プレイヤー2スコア加算
	/// </summary>
	void AddPlayer2Score() { player2Score_++; }

};

