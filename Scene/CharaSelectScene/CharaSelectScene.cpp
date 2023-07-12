#include "CharaSelectScene.h"
#include "../../UI/CharaSelect/CharaSelectSceneUI.h"

//コンストラクタ
CharaSelectScene::CharaSelectScene(GameObject* parent)
	: GameObject(parent, "CharaSelectScene")
{
}

//デストラクタ
CharaSelectScene::~CharaSelectScene()
{
}

//初期化
void CharaSelectScene::Initialize()
{
	//表示
	Instantiate<CharaSelectSceneUI>(this);
}
