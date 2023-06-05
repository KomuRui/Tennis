#include "ServingState.h"
#include "../../Engine/System.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"
#include "../../OtherObject/TitleScene/Racket.h"

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
	if (ModelManager::GetAnimFrame(player->GetModelNum()) == 270)
	{
		//��ԕύX
		player->GetState()->ChangeState(player->GetState()->playerStanding_, player);

		//�A�j���[�V����
		ModelManager::SetAnimFrame(player->GetModelNum(), 1, 60, 2.0f);
		ModelManager::SetAnimFrame(player->GetRacket()->GetModelNum(), 1, 60, 2.0f);
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
	ModelManager::SetAnimFrame(player->GetModelNum(), 210, 270, 2.0f);
	ModelManager::SetAnimFrame(player->GetRacket()->GetModelNum(), 210, 270, 2.0f);
}
