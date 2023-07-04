#pragma once
#include "../EasingImage.h"

/// <summary>
/// プレイヤー画像
/// </summary>
class PlayerImage : public EasingImage
{

public:

	//コンストラクタ
	PlayerImage(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

};

