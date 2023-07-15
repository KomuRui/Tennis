#pragma once
#include "../EasingImage.h"

/// <summary>
/// 球足UI
/// </summary>
class SphereFootUI : public EasingImage
{

public:

	//コンストラクタ
	SphereFootUI(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

};

