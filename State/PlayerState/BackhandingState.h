#pragma once
#include "PlayerState.h"

class PlayerBase;

/// </summary>
///バックハンド状態
/// </summary>
class BackhandingState : public PlayerState
{
	int hTime_;		 //タイマーハンドル
	bool isHitMove_; //打つ動きをしているか

public:

	//2D用更新
	void Update2D(PlayerBase* player) override;

	//3D用更新
	void Update3D(PlayerBase* player) override;

	//入力によって状態変化する
	void HandleInput(PlayerBase* player) override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter(PlayerBase* player) override;
};