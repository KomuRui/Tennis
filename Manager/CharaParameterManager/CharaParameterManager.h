#pragma once
#include "../GameManager/GameManager.h"

//各キャラクターのパラメータを管理
namespace CharaParameterManager
{
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// キャラのスピードを取得
	/// </summary>
	/// <param name="charaModelPath">キャラのモデルパス</param>
	/// <returns>スピード</returns>
	float GetCharaSpeed(string charaModelPath);

	/// <summary>
	/// キャラのパワーを取得
	/// </summary>
	/// <param name="charaModelPath">キャラのモデルパス</param>
	/// <returns>パワー</returns>
	float GetCharaPower(string charaModelPath);

	/// <summary>
	/// キャラのテクニックを取得
	/// </summary>
	/// <param name="charaModelPath">キャラのモデルパス</param>
	/// <returns>テクニック</returns>
	float GetCharaTechnique(string charaModelPath);
};

