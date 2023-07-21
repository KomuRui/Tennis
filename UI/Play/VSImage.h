#pragma once
#include "../EasingImage.h"

/// <summary>
/// VS画像
/// </summary>
class VSImage : public EasingImage
{

public:

	//コンストラクタ
	VSImage(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

};

