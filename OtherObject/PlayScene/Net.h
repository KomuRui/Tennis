#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// ネット
/// </summary>
class Net : public NormalObject
{
public:

	//コンストラクタ
	Net(GameObject* parent, std::string modelPath, std::string name);

	//デストラクタ
	~Net() {};

	//描画
	void Draw() override {};

	//透明・半透明描画
	void TransparentDraw() override;
};

