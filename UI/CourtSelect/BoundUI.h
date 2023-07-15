#pragma once
#include "../EasingImage.h"

/// <summary>
/// バウンドUI
/// </summary>
class BoundUI : public EasingImage
{

public:

	//コンストラクタ
	BoundUI(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

};

