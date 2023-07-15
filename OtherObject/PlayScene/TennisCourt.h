#pragma once
#include "../../Base/NormalObject.h"
#include <map>

//テニスコートの名前
enum class TennisCourtName
{
	Z_PLUS_COURT, //Z方向プラスのコート
	Z_MINUS_COURT //Z方向マイナスのコート
};

//テニスコートの型
enum class TennisCourtType
{
	HARD_COURT,  //ハードコート
	CLAY_COURT,  //クレイコート
	GRASS_COURT  //グラスコート
};

/// <summary>
/// テニスコートモデル
/// </summary>
class TennisCourt : public NormalObject
{

	//テニスコートの型
	TennisCourtType type_;

	//テニスコートに対してのモデル番号
	map<TennisCourtType, int> hModelTable_;

public:

	//コンストラクタ
	TennisCourt(GameObject* parent, std::string modelPath, std::string name);

	//デストラクタ
	~TennisCourt() {};

	//初期化
	void ChildInitialize() override;

	//二つ目のウィンドウの描画
	void TwoWindowDraw() override;

	//テニスコートの型を設定
	void SetTennisCourtType(TennisCourtType type);
};

