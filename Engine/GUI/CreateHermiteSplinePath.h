#pragma once

/// <summary>
/// エルミートスプラインのパス作成
/// </summary>
namespace CreateHermiteSplinePath
{
	/// <summary>
	/// ウィンドウ描画
	/// </summary>
	void WindowDraw();

	/// <summary>
	/// すべてのパス情報を描画
	/// </summary>
	void AllPathInfoGuiDraw();

	/// <summary>
	/// パス追加
	/// </summary>
	void AddPath();

	/// <summary>
	/// セーブ
	/// </summary>
	void Save();

	////////////////////////////////////////セッター・ゲッター////////////////////////////////////////////

	/// <summary>
	/// ウィンドウを描画するか設定
	/// </summary>
	/// <param name="flag">trueなら描画する</param>
	void SetWindowDraw(bool flag);

	/// <summary>
	/// ウィンドウ描画しているか
	/// </summary>
	/// <returns>trueなら描画している</returns>
	bool isWindowDraw();
}
