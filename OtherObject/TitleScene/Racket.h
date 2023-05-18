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

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override;

};

