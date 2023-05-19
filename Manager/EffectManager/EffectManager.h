#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// エフェクトを管理する
/// </summary>
namespace EffectManager
{

	/// <summary>
	/// エフェクト表示
	/// </summary>
	/// <param name="pos">エフェクトが発生する位置</param>
	/// <param name="filename">エフェクト情報が保管しているファイルネームパス</param>
	void Draw(string fileNamePath,XMFLOAT3 pos);

	/// <summary>
	/// エフェクトロード
	/// </summary>
	/// <param name="fileNamePath"></param>
	void Load(string fileNamePath);
}

