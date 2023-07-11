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
	void Input(ButtonBase* button,int numController = 0);

	/// <summary>
	/// ボタンを追加
	/// </summary>
	void AddButton(ButtonBase* button);

	/// <summary>
	/// 任意に選択状態のボタンを変更
	/// </summary>
	/// <param name="button">ボタン</param>
	void SetSelect(ButtonBase* button,int numController = 0);

	/// <summary>
	/// リセットする
	/// </summary>
	void Reset();
};

