#include "NetAround.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/DirectX/Direct3D.h"

//コンストラクタ
NetAround::NetAround(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}

//初期化
void NetAround::ChildInitialize()
{
	SetShadow(false);
}

//透明描画
void NetAround::TransparentDraw()
{
	//描画
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}