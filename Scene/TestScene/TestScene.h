#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/HermiteSplineMove.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TestScene : public GameObject
{


public:

	//コンストラクタ
	TestScene(GameObject* parent);

	//デストラクタ
	~TestScene();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

};

