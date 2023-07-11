#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include <map>

/// <summary>
/// キャラ選択シーンのUI
/// </summary>
class CharaSelectSceneUI : public GameObject
{

	//各UI作成用
	std::unique_ptr<CreateStage> pCreateImage_ = std::make_unique<CreateStage>();

	//Controller0,1の選択してる時の画像とトランスフォームを格納
	map<int, pair<int, std::shared_ptr<Transform>>> selectPict_;

public:

	//コンストラクタ
	CharaSelectSceneUI(GameObject* parent);

	//デストラクタ
	~CharaSelectSceneUI() {};

	//初期化
	void Initialize() override;

	/// <summary>
	/// トランスフォーム設定
	/// </summary>
	/// <param name="t">設定したいトランスフォーム</param>
	/// <param name="numController">コントローラー番号</param>
	void SetTransform(const Transform& t, int numController);

	/// <summary>
	/// 各コントローラーの選択画像のトランスフォームを取得
	/// </summary>
	/// <param name="numController">コントローラー番号</param>
	/// <returns>トランスフォーム</returns>
	Transform* GetTrasnform(int numController) { return selectPict_[numController].second.get(); }

};

