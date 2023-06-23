#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// 空モデル
/// </summary>
class Sky : public NormalObject
{

	float scroll;   //UVスクロール

public:

	//コンストラクタ
	Sky(GameObject* parent, std::string modelPath, std::string name);

	//デストラクタ
	~Sky() {};

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;
};

