#pragma once
#include "Base/NormalObject.h"
#include "Engine/Component/Collider/SphereCollider.h"

/// <summary>
/// テニスコートモデル
/// </summary>
class test : public NormalObject
{

	//当たり判定
	SphereCollider* sphere_;     //球型の当たり判定

public:

	//コンストラクタ
	test(GameObject* parent, std::string modelPath, std::string name);

	//デストラクタ
	~test() {};

	//初期化
	void ChildInitialize() override;

	void ChildUpdate() override;
};

