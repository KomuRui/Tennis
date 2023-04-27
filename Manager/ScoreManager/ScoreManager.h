#pragma once

//テニスのスコア管理
namespace ScoreManager
{
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// シーン遷移の時の初期化
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// 描画(コインの取得数やPlayerライフの表示)
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤースコア加算
	/// </summary>
	void AddPlayerScore();

	/// <summary>
	/// エネミースコア加算
	/// </summary>
	void AddEnemyScore();

	///////////////////////////////セットゲット関数//////////////////////////////////

};

