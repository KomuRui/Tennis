#include "StandingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"

//�X�V
void StandingState::Update2D(PlayerBase* player)
{
	//���͏����֐����Ă�
	HandleInput(player);
}

//3D�p�X�V
void StandingState::Update3D(PlayerBase* player)
{
	//���͏����֐����Ă�
	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void StandingState::HandleInput(PlayerBase* player)
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerForehanding_;
		PlayerStateManager::playerState_->Enter(player);
	}

	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerBackhanding_;
		PlayerStateManager::playerState_->Enter(player);
	}

	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerServing_;
		PlayerStateManager::playerState_->Enter(player);
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void StandingState::Enter(PlayerBase* player)
{
}
