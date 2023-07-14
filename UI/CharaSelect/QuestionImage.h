#pragma once
#include "../EasingImage.h"

/// <summary>
/// 確認画像
/// </summary>
class QuestionImage : public EasingImage
{

public:

	//コンストラクタ
	QuestionImage(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

};

