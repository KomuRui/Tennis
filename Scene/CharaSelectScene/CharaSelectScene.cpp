#include "CharaSelectScene.h"
#include "../../UI/CharaSelect/CharaSelectSceneUI.h"

//�R���X�g���N�^
CharaSelectScene::CharaSelectScene(GameObject* parent)
	: GameObject(parent, "CharaSelectScene")
{
}

//�f�X�g���N�^
CharaSelectScene::~CharaSelectScene()
{
}

//������
void CharaSelectScene::Initialize()
{
	//�\��
	Instantiate<CharaSelectSceneUI>(this);
}