#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/Component/EasingMove.h"
#include <map>

/// <summary>
/// キャラ選択シーンのUI
/// </summary>
class CharaSelectSceneUI : public GameObject
{

	//各UI作成用
	std::unique_ptr<CreateStage> pCreateImage_ = std::make_unique<CreateStage>();

	//選択画像の情報
	struct selectPictInfo
	{
		int hPict_;                                    //画像番号
		std::shared_ptr<Transform> transform_;         //トランスフォーム
		std::unique_ptr<EasingMove> easingSelectPict_; //選択されているときの画像のイージング用
	};

	//Controller0,1の選択してる時の情報を格納
	map<int, selectPictInfo> selectPict_;

public:

	//コンストラクタ
	CharaSelectSceneUI(GameObject* parent);

	//デストラクタ
	~CharaSelectSceneUI() {};

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	/// <summary>
	/// トランスフォーム設定
	/// </summary>
	/// <param name="t">設定したいトランスフォーム</param>
	/// <param name="numController">コントローラー番号</param>
	void SetSelectPictTransform(const Transform& t, int numController);

	/// <summary>
	/// 各コントローラーの選択画像のトランスフォームを取得
	/// </summary>
	/// <param name="numController">コントローラー番号</param>
	/// <returns>トランスフォーム</returns>
	Transform* GetSelectPictTrasnform(int numController) { return selectPict_[numController].transform_.get(); }

	/// <summary>
	/// イージングリセット
	/// </summary>
	/// <param name="t">移動後のポジション</param>
	/// <param name="numController">コントローラー番号</param>
	void ResetEasing(const XMFLOAT3& t,int numController);

};

