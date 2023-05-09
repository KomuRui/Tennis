#pragma once
#include "../../Base/NormalObject.h"

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

	//二つ目のウィンドウの描画
	void TwoWindowDraw() override;
};

