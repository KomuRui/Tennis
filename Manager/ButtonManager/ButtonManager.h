#pragma once

class ButtonBase;

/// <summary>
/// 画面に表示されているボタンを管理する
/// </summary>
namespace ButtonManager
{
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 入力
	/// </summary>
	void Input(ButtonBase* button);

	/// <summary>
	/// ボタンを追加
	/// </summary>
	void AddButton(ButtonBase* button);

	/// <summary>
	/// 任意に選択状態のボタンを変更
	/// </summary>
	/// <param name="button">ボタン</param>
	void SetSelect(ButtonBase* button);

	/// <summary>
	/// リセットする
	/// </summary>
	void Reset();
};

