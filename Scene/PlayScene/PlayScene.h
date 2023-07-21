#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// プレイシーン
/// </summary>
class PlayScene : public GameObject
{

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	//デストラクタ
	~PlayScene();

	//初期化
	void Initialize() override;

	/// <summary>
	/// UI作成
	/// </summary>
	void CreateUI();
};

