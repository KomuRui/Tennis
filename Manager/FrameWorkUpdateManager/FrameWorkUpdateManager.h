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
};

