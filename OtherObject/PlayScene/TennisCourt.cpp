#include "TennisCourt.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../OtherObject/PlayScene/Referee.h"
#include "../../Manager/GameManager/GameManager.h"

//�R���X�g���N�^
TennisCourt::TennisCourt(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent,modelPath,name),type_(TennisCourtType::HARD_COURT)
{}

//������
void TennisCourt::ChildInitialize()
{
	//�e�R�[�g�̃��f�����[�h
	ARGUMENT_INITIALIZE(hModelTable_[TennisCourtType::HARD_COURT], ModelManager::Load("Stage/TennisCourt_ha-do.fbx"));
	ARGUMENT_INITIALIZE(hModelTable_[TennisCourtType::GRASS_COURT], ModelManager::Load("Stage/TennisCourt_gurasu.fbx"));
	ARGUMENT_INITIALIZE(hModelTable_[TennisCourtType::CLAY_COURT], ModelManager::Load("Stage/TennisCourt_kurei.fbx"));

	//�e�j�X�R�[�g�^�C�v�ݒ�
	SetTennisCourtType(GameManager::GetReferee()->GetTennisCourtType());

	//�e�K�p���Ȃ��悤��
	SetShadow(false);
}

//��ڂ̃E�B���h�E�̕`��
void TennisCourt::TwoWindowDraw()
{
	//�`��
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

//�e�j�X�R�[�g�̌^��ݒ�
void TennisCourt::SetTennisCourtType(TennisCourtType type)
{
	if (this == nullptr) return;

	//�^�C�v�o�^
	ARGUMENT_INITIALIZE(type_, type);
	ARGUMENT_INITIALIZE(hModel_, hModelTable_[type]);
}