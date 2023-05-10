#pragma once
#include "../../OtherObject/TitleScene/TennisCourt.h"

//テニスボールが飛んでいく基準点を管理している名前空間
namespace BasePointManager
{
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 基準点モデルを生成
	/// </summary>
	void InstantiateBasePointModel();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();
};

