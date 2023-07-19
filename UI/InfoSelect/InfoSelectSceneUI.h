#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"

/// <summary>
/// ゲーム情報選択シーンのUI
/// </summary>
class InfoSelectSceneUI : public GameObject
{

	//各UI作成用
	std::unique_ptr<CreateStage> pCreateImage_ = std::make_unique<CreateStage>();
	std::unique_ptr<CreateStage> pCreateButton_ = std::make_unique<CreateStage>();

public:

	//コンストラクタ
	InfoSelectSceneUI(GameObject* parent);

	//デストラクタ
	~InfoSelectSceneUI() {};

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

};

