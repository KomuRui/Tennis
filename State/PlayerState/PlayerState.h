#pragma once
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/DirectX/Input.h"

class PlayerBase;

/// <summary>
/// Player�̏�Ԃ̊��N���X
/// </summary>
class PlayerState
{
public:

	/// <summary>
	/// 2D�p�X�V
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	virtual void Update2D(PlayerBase* player) {};

	/// <summary>
	/// 3D�p�X�V
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	virtual void Update3D(PlayerBase* player) {};

	/// <summary>
	/// �~�j�Q�[���p�X�V
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	virtual void UpdateMiniGame(PlayerBase* player) {};

	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	virtual void HandleInput(PlayerBase* player) {};

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	virtual void Enter(PlayerBase* player) {};

	/// <summary>
	/// ��ԕύX
	/// </summary>
	/// <param name="nowState">���݂̏��</param>
	/// <param name="state">�ω����������</param>
	void ChangeState(PlayerState* nowState,PlayerState* state);
};
