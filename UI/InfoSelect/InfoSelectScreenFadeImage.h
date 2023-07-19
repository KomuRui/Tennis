#pragma once
#include "../EasingImage.h"

/// <summary>
/// 試合情報選択画像(Fade用)
/// </summary>
class InfoSelectScreenFadeImage : public EasingImage
{

public:

	//コンストラクタ
	InfoSelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

	//更新
	void EasingImageChileUpdate() override;

};

