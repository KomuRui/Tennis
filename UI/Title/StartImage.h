#pragma once
#include "../ImageBase.h"

/// <summary>
/// 開始画像
/// </summary>
class StartImage : public ImageBase
{

	int sign_;       //符号
	float nowAlpha_; //現在の透明度

public:

	//コンストラクタ
	StartImage(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

};

