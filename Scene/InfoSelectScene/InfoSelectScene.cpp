#include "InfoSelectScene.h"
#include "../../UI/InfoSelect/InfoSelectSceneUI.h"

//コンストラクタ
InfoSelectScene::InfoSelectScene(GameObject* parent)
	: GameObject(parent, "InfoSelectScene")
{
}

//デストラクタ
InfoSelectScene::~InfoSelectScene()
{
}

//初期化
void InfoSelectScene::Initialize()
{
	//表示
	Instantiate<InfoSelectSceneUI>(this);
}
