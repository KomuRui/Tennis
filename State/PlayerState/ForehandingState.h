#pragma once
#include "PlayerState.h"

class PlayerBase;

/// </summary>
///�t�H�A�n���h���
/// </summary>
class ForehandingState : public PlayerState
{
public:

	//2D�p�X�V
	void Update2D(PlayerBase* player) override;

	//3D�p�X�V
	void Update3D(PlayerBase* player) override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput(PlayerBase* player) override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter(PlayerBase* player) override;
};