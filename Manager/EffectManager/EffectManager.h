#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/VFX.h"

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
	void Draw(string effectName,string fileNamePath,XMFLOAT3 pos);

	/// <summary>
	/// エフェクトロード
	/// </summary>
	/// <param name="fileNamePath">エフェクト情報が保管しているファイルネームパス</param>
	void Load(string fileNamePath);

	/// <summary>
	/// エミッターデータを取得
	/// </summary>
	/// <param name="fileNamePath">エフェクト情報が保管しているファイルネームパス</param>
	/// <returns>エミッターデータ</returns>
	EmitterData GetEmitterData(string fileNamePath);
}

