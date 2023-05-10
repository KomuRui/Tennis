#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// ボールが飛んでいく基準点に配置するモデル
/// </summary>
class BasePointModel : public NormalObject
{
public:

	//コンストラクタ
	BasePointModel(GameObject* parent, std::string modelPath, std::string name);
	BasePointModel(GameObject* parent);

	//デストラクタ
	~BasePointModel() {};

	//初期化
	void ChildInitialize() override;

	//描画
	void Draw() override {};

	//二つ目のウィンドウの描画
	void TwoWindowDraw() override;
};

