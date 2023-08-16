#pragma once
#include "Base/NormalObject.h"
#include "Engine/Component/Collider/BoxCollider.h"

/// <summary>
/// テニスコートモデル
/// </summary>
class testBox : public NormalObject
{

	//当たり判定
	BoxCollider* box_;     //球型の当たり判定

public:

	//コンストラクタ
	testBox(GameObject* parent, std::string modelPath, std::string name);

	//デストラクタ
	~testBox() {};

	//初期化
	void ChildInitialize() override;

	void ChildUpdate() override;
};

