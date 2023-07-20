#pragma once
#include "../EasingImage.h"

/// <summary>
/// スクリーン画像(Fade用)
/// </summary>
class PlaySelectScreenFadeImage : public EasingImage
{

public:

	//コンストラクタ
	PlaySelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

	//更新
	void EasingImageChileUpdate() override;

};

