#include "TennisCourt.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"

//コンストラクタ
TennisCourt::TennisCourt(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent,modelPath,name)
{}

//初期化
void TennisCourt::ChildInitialize()
{
	SetShadow(false);
}

//二つ目のウィンドウの描画
void TennisCourt::TwoWindowDraw()
{
	//描画
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}
