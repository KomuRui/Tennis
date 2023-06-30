#pragma once
#include "../ImageBase.h"

/// <summary>
/// スクリーン画像(Fade用)
/// </summary>
class ScreenFadeImage : public ImageBase
{

public:

	//コンストラクタ
	ScreenFadeImage(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;
};

