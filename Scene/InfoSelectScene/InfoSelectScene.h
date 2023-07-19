#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// ゲーム情報選択シーン
/// </summary>
class InfoSelectScene : public GameObject
{

public:

	//コンストラクタ
	InfoSelectScene(GameObject* parent);

	//デストラクタ
	~InfoSelectScene();

	//初期化
	void Initialize() override;

};

