#pragma once
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "TennisCourt.h"
#include <map>

//テキスト情報
struct Textinfo
{
	XMFLOAT3 pos;
	XMFLOAT2 scale;
};

//テニスのスコア
class Score
{
	map<TennisCourtName, int> scoreTable_;					//スコア表
	map<TennisCourtName, pair<Text*, Textinfo>> scoreText_; //スコアのテキスト表示用

	TennisCourtName pointGetTennisCourtName_;               //ポイント取得しテニスコートの名前

	Text* pHyphenText_;					 //ハイフン表示する用
	Textinfo hyphenTextInfo_;			 //テキストのポジション

	XMFLOAT3 allScale_;                  //すべての拡大率
	XMFLOAT3 pointGetScale_;             //ポイント取得した方の拡大率

	std::unique_ptr<EasingMove> zPlusCourtEasingPos_ = std::make_unique<EasingMove>();     //位置イージング用
	std::unique_ptr<EasingMove> zMinusCourtEasingPos_ = std::make_unique<EasingMove>();    //位置イージング用
	std::unique_ptr<EasingMove> hyphenEasingPos_ = std::make_unique<EasingMove>();         //位置イージング用
	std::unique_ptr<EasingMove> allScaleEasing_ = std::make_unique<EasingMove>();          //すべての拡大率イージング用
	std::unique_ptr<EasingMove> pointGetScaleEasing_ = std::make_unique<EasingMove>();     //すべての拡大率イージング用

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

	/// <summary>
	/// 位置を戻す動き
	/// </summary>
	void ReturnMovePos();

	/// <summary>
	/// イージングでスコア変更
	/// </summary>
	void ChangeScoreEasing();

};

