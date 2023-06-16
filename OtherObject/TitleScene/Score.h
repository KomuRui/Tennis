#pragma once
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "TennisCourt.h"
#include <map>

//スコア情報
struct ScoreInfo
{
	int point;      //ポイント数
	int gamePoint;  //ゲームポイント数
	int setPoint;   //セットポイント数
};

//テキスト情報
struct TextInfo
{
	XMFLOAT3 pos;
	XMFLOAT2 scale;
};

//テニスのスコア
class Score
{
	map<TennisCourtName, ScoreInfo> scoreTable_;			//スコア表
	map<TennisCourtName, pair<Text*, TextInfo>> scoreText_; //スコアのテキスト表示用

	TennisCourtName pointGetTennisCourtName_;               //ポイント取得しテニスコートの名前

	Text* pHyphenText_;					 //ハイフン表示する用
	TextInfo hyphenTextInfo_;			 //テキストのポジション

	XMFLOAT3 allScale_;                  //すべての拡大率
	XMFLOAT3 pointGetScale_;             //ポイント取得した方の拡大率

	std::unique_ptr<EasingMove> zPlusCourtEasingPos_ = std::make_unique<EasingMove>();     //位置イージング用
	std::unique_ptr<EasingMove> zMinusCourtEasingPos_ = std::make_unique<EasingMove>();    //位置イージング用
	std::unique_ptr<EasingMove> hyphenEasingPos_ = std::make_unique<EasingMove>();         //位置イージング用
	std::unique_ptr<EasingMove> allScaleEasing_ = std::make_unique<EasingMove>();          //すべての拡大率イージング用
	std::unique_ptr<EasingMove> pointGetScaleEasing_ = std::make_unique<EasingMove>();     //すべての拡大率イージング用

	std::map<int, int> table;      //スコア表(キー:カウント数0,1,2,3 バリュー:表示するスコア数)

	std::unique_ptr<Sprite> offGameUi_ = std::make_unique<Sprite>();           //ゲーム未取得時のUI
	std::unique_ptr<Sprite> onZPlusCourtGameUi_ = std::make_unique<Sprite>();  //Zプラスコートがゲーム取得時のUI
	std::unique_ptr<Sprite> onZMinusCourtGameUi_ = std::make_unique<Sprite>(); //Zマイナスコートがゲーム取得時のUI
	
public:

	//コンストラクタ
	Score();

	/// <summary>
	/// 描画(コインの取得数やPlayerライフの表示)
	/// </summary>
	void Draw();

	/// <summary>
	/// ポイント数描画
	/// </summary>
	void PointDraw();

	/// <summary>
	/// ゲームポイント描画
	/// </summary>
	void GamePointDraw();

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

