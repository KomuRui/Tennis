#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// 海のモデル
/// </summary>
class Water : public NormalObject
{

	float scroll;   //UVスクロール

public:

	//コンストラクタ
	Water(GameObject* parent, std::string modelFilePath_, std::string name);

	//デストラクタ
	~Water() {};

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	//二つ目のウィンドウの描画
	void TwoWindowDraw() override;
};

