#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/HermiteSplineMove.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public GameObject
{

	//エルミートスプラインを使ってカメラを動かす
	std::unique_ptr<HermiteSplineMove> hermiteMoveCamPos_ = std::make_unique<HermiteSplineMove>(); 
	std::unique_ptr<HermiteSplineMove> hermiteMoveCamTar_ = std::make_unique<HermiteSplineMove>(); 

public:

	//コンストラクタ
	TitleScene(GameObject* parent);

	//デストラクタ
	~TitleScene();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;



};

