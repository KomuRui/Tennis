#include "NormalObject.h"
#include "../Engine/ResourceManager/ModelManager.h"

//�R���X�g���N�^
NormalObject::NormalObject(GameObject* parent, std::string modelPath, std::string name)
	:GameObject(parent,name),modelNamePath_(modelPath),hModel_(-1)
{}

//������
void NormalObject::Initialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	ARGUMENT_INITIALIZE(hModel_,ModelManager::Load(modelNamePath_));
	ARGUMENT_INITIALIZE(pathName_, modelNamePath_);
	assert(hModel_ >= ZERO);

	//���f���̖��O�ݒ�
	ModelManager::SetModelName(hModel_,GetObjectName());

	//�Q�[���I�u�W�F�N�g�ǉ�
	ModelManager::SetGameObject(hModel_, this);

	//�eON�ɂ��Ă���
	SetShadow(true);
	
	//�p����p
	ChildInitialize();
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void NormalObject::StartUpdate()
{
	//�p����p
	ChildStartUpdate();
}

//�X�V
void NormalObject::Update()
{
	//�p����p
	ChildUpdate();
}

//�`��
void NormalObject::Draw()
{
	//�`��
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);

	//�p����p
	ChildDraw();
}

//�J��
void NormalObject::Release()
{
	//�p����p
	ChildRelease();
}
