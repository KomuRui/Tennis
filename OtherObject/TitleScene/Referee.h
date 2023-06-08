#pragma once
#include "Score.h"

/// <summary>
/// 審判
/// </summary>
class Referee
{
	Score* score_; //スコア

public:

	//コンストラクタ
	Referee();
	
	//デストラクタ
	~Referee() {};

	//描画
	void Draw();
};

