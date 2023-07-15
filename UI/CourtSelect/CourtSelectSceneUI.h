#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"

/// <summary>
/// コート選択シーンのUI
/// </summary>
class CourtSelectSceneUI : public GameObject
{

	//各UI作成用
	std::unique_ptr<CreateStage> pCreateImage_ = std::make_unique<CreateStage>();

public:

	//コンストラクタ
	CourtSelectSceneUI(GameObject* parent);

	//デストラクタ
	~CourtSelectSceneUI() {};

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

};

