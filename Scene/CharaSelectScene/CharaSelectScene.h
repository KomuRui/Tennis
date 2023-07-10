#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// キャラ選択シーン
/// </summary>
class CharaSelectScene : public GameObject
{

public:

	//コンストラクタ
	CharaSelectScene(GameObject* parent);

	//デストラクタ
	~CharaSelectScene();

	//初期化
	void Initialize() override;

};

