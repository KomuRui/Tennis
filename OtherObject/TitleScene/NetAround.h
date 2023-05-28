#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// コートの周りのネット
/// </summary>
class NetAround : public NormalObject
{
public:

	//コンストラクタ
	NetAround(GameObject* parent, std::string modelPath, std::string name);

	//デストラクタ
	~NetAround() {};

	//初期化
	void ChildInitialize() override;

	//描画
	void Draw() override {};

	//透明・半透明描画
	void TransparentDraw() override;
};

