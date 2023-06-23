#pragma once
#include "../../Base/NormalObject.h"

//テニスコートの名前
enum class TennisCourtName
{
	Z_PLUS_COURT, //Z方向プラスのコート
	Z_MINUS_COURT //Z方向マイナスのコート
};

/// <summary>
/// テニスコートモデル
/// </summary>
class TennisCourt : public NormalObject
{
public:

	//コンストラクタ
	TennisCourt(GameObject* parent, std::string modelPath, std::string name);

	//デストラクタ
	~TennisCourt() {};

	//初期化
	void ChildInitialize() override;

	//二つ目のウィンドウの描画
	void TwoWindowDraw() override;
};

