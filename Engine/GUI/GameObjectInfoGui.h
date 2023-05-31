#pragma once


/// <summary>
/// ゲームオブジェクトの情報を表示するGUI
/// </summary>
namespace GameObjectInfoGui
{
	/// </summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// ゲームオブジェクトの情報を描画
	/// </summary>
	void GameObjectInfoDraw();

	/// <summary>
	/// 名前とトランスフォーム描画
	/// </summary>
	void NameAndTransformDraw();

	/// </summary>
	/// 色情報描画
	/// </summary>
	void ColorInfoDraw();

	/// </summary>
	/// モデル情報描画
	/// </summary>
	void ModelInfoDraw();

	/// <summary>
	/// モデル設定
	/// </summary>
	/// <param name="ModelNum">モデル番号</param>
	void SetModel(int ModelNum);
}