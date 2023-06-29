#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/HermiteSplineMove.h"

/// <summary>
/// モード選択シーン
/// </summary>
class ModeSelectScene : public GameObject
{

public:

	//コンストラクタ
	ModeSelectScene(GameObject* parent);

	//デストラクタ
	~ModeSelectScene();

	//初期化
	void Initialize() override;

};

