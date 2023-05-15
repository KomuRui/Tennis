#include "ForehandingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"

//�X�V
void ForehandingState::Update2D(PlayerBase* player)
{
	//���͏����֐����Ă�
	HandleInput(player);
}

//3D�p�X�V
void ForehandingState::Update3D(PlayerBase* player)
{
	//�����A�j���[�V�������Ō�܂ŏI������̂Ȃ�
	if (Model::GetAnimFrame(player->GetModelNum()) >= 130)
	{
		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
		PlayerStateManager::playerState_->Enter(player);

		//�A�j���[�V����
		Model::SetAnimFrame(player->GetModelNum(), 1, 60, 2.0f);
		Model::SetAnimFrame(player->GetRacket()->GetModelNum(), 1, 60, 2.0f);
	}

	//���͏����֐����Ă�
	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void ForehandingState::HandleInput(PlayerBase* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void ForehandingState::Enter(PlayerBase* player)
{
	//�A�j���[�V����
	Model::SetAnimFrame(player->GetModelNum(), 70, 130, 4.0f);
	Model::SetAnimFrame(player->GetRacket()->GetModelNum(), 70, 130, 4.0f);
	Model::SetAnimLoop(player->GetRacket()->GetModelNum(), false);
}
