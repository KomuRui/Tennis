#pragma once
#include "../EasingImage.h"

/// <summary>
/// キャラ選択画像(Fade用)
/// </summary>
class CharaSelectScreenFadeImage : public EasingImage
{

public:

	//コンストラクタ
	CharaSelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

	//更新
	void EasingImageChileUpdate() override;

};

