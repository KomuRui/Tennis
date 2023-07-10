#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"

/// <summary>
/// キャラ選択シーンのUI
/// </summary>
class CharaSelectSceneUI : public GameObject
{

	//各UI作成用
	std::unique_ptr<CreateStage> pCreateImage_ = std::make_unique<CreateStage>();

public:

	//コンストラクタ
	CharaSelectSceneUI(GameObject* parent);

	//デストラクタ
	~CharaSelectSceneUI() {};

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

};

