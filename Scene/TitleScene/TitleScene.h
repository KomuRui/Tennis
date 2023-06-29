#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/HermiteSplineMove.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public GameObject
{

	//エルミートスプラインを使ってカメラを動かす(連続して動きを変更したいのでvectorにしておく)
	vector<pair<std::unique_ptr<HermiteSplineMove>, std::unique_ptr<HermiteSplineMove>>> hermiteMoveTable_;

	//現在見ている番号
	int nowLookNum_;

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

	/// <summary>
	/// カメラの動き
	/// </summary>
	void CameraMove();

	/// <summary>
	/// データセット
	/// </summary>
	void SetData(string posFileName,string tarFileName);

};

