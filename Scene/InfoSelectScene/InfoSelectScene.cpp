#include "InfoSelectScene.h"
#include "../../UI/InfoSelect/InfoSelectSceneUI.h"

//�R���X�g���N�^
InfoSelectScene::InfoSelectScene(GameObject* parent)
	: GameObject(parent, "InfoSelectScene")
{
}

//�f�X�g���N�^
InfoSelectScene::~InfoSelectScene()
{
}

//������
void InfoSelectScene::Initialize()
{
	//�\��
	Instantiate<InfoSelectSceneUI>(this);
}
