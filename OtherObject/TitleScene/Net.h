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
};

