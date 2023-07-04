#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"

/// <summary>
/// モード選択シーンのUI
/// </summary>
class ModeSelectSceneUI : public GameObject
{

	//各UI作成用
	std::unique_ptr<CreateStage> pCreateImage_ = std::make_unique<CreateStage>();
	std::unique_ptr<CreateStage> pCreateButton_ = std::make_unique<CreateStage>();

public:

	//コンストラクタ
	ModeSelectSceneUI(GameObject* parent);

	//デストラクタ
	~ModeSelectSceneUI() {};

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

};

