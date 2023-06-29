#pragma once
#include "../../Engine/GameObject/GameObject.h"

//フレームワーク更新するとこと
namespace FrameWorkUpdateManager
{
	/// <summary>
	/// 更新
	/// </summary>
	void Update(GameObject* root);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(GameObject* root);

	/// <summary>
	/// 二つ目のウィンドウ描画
	/// </summary>
	void TwoWindowDraw(GameObject* root);

	/// <summary>
	/// 一人プレイの描画
	/// </summary>
	void OnePlayerDraw(GameObject* root);

	/// <summary>
	/// 二人プレイの描画
	/// </summary>
	void TwoPlayerDraw(GameObject* root);

	//スクリーンショットをとるための関数
	void GameScreenDraw(GameObject* root);

	/// <summary>
	/// 影描画
	/// </summary>
	void ShadowDraw(GameObject* root);
};

