#include "ModeSelectScene.h"
#include "../../UI/ModeSelect/ModeSelectSceneUI.h"

//コンストラクタ
ModeSelectScene::ModeSelectScene(GameObject* parent)
	: GameObject(parent, "ModeSelectScene")
{
}

//デストラクタ
ModeSelectScene::~ModeSelectScene()
{
}

//初期化
void ModeSelectScene::Initialize()
{
	//表示
	Instantiate<ModeSelectSceneUI>(this);
}
