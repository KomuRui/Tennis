#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// テニスコートの周りのモデル
/// </summary>
class TennisCourtAround : public NormalObject
{
public:

	//コンストラクタ
	TennisCourtAround(GameObject* parent, std::string modelPath, std::string name);

	//デストラクタ
	~TennisCourtAround() {};

	//初期化
	void ChildInitialize() override;
};

