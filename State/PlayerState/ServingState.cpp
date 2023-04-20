#include "ServingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"

//�X�V
void ServingState::Update2D(PlayerBase* player)
{
	//���͏����֐����Ă�
	HandleInput(player);
}

//3D�p�X�V
void ServingState::Update3D(PlayerBase* player)
{
	//�����A�j���[�V�������Ō�܂ŏI������̂Ȃ�
	if (Model::GetAnimFrame(player->GetModelNum()) == 270)
	{
		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
		PlayerStateManager::playerState_->Enter(player);

		//�A�j���[�V����
		Model::SetAnimFrame(player->GetModelNum(), 1, 60, 2.0f);
	}

	//���͏����֐����Ă�
	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void ServingState::HandleInput(PlayerBase* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void ServingState::Enter(PlayerBase* player)
{
	//�A�j���[�V����
	Model::SetAnimFrame(player->GetModelNum(), 210, 270, 2.0f);
}
