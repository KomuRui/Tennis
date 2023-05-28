#include "NetAround.h"
#include "../../Engine/ResourceManager/Model.h"
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
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}