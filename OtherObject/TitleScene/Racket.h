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

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override;

	//デストラクタ
	~Racket() {};
};

