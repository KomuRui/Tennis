#pragma once
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Text.h"
#include "TennisCourt.h"
#include <map>

//テニスのスコア
class Score
{
	
	map<TennisCourtName, int> scoreTable_;					//スコア表
	map<TennisCourtName, pair<Text*, XMFLOAT2>> scoreText_; //スコアのテキスト表示用

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
	/// スコア加算
	/// </summary>
	void AddScore(TennisCourtName n);

};

