#include "ModeSelectScene.h"
#include "../../UI/ModeSelect/ModeSelectSceneUI.h"

//�R���X�g���N�^
ModeSelectScene::ModeSelectScene(GameObject* parent)
	: GameObject(parent, "ModeSelectScene")
{
}

//�f�X�g���N�^
ModeSelectScene::~ModeSelectScene()
{
}

//������
void ModeSelectScene::Initialize()
{
	//�\��
	Instantiate<ModeSelectSceneUI>(this);
}
