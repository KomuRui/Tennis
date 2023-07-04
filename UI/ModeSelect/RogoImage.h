#pragma once
#include "../EasingImage.h"

/// <summary>
/// ロゴ画像
/// </summary>
class RogoImage : public EasingImage
{

public:

	//コンストラクタ
	RogoImage(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

};

