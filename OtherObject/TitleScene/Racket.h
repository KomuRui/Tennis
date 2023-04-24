#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// ラケット
/// </summary>
class Racket : public NormalObject
{
public:

	//コンストラクタ
	Racket(GameObject* parent, std::string modelPath, std::string name);
	Racket(GameObject* parent);

	//デストラクタ
	~Racket() {};
};

