#include "Water.h"
#include "../../Engine/ResourceManager/ModelManager.h"

//コンストラクタ
Water::Water(GameObject* parent, std::string modelFilePath_, std::string name)
	:NormalObject(parent,modelFilePath_,name), scroll(ZERO)
{}

//初期化
void Water::ChildInitialize()
{
	//ノーマルマップを使う
	ModelManager::SetShederType(hModel_, Direct3D::SHADER_NORMALMAP);

	SetShadow(false);
}

//更新
void Water::ChildUpdate()
{
	//UVスクロール
	scroll += 0.008f;
	ModelManager::SetUvScroll(hModel_, scroll);
}

//二つ目のウィンドウの描画
void Water::TwoWindowDraw()
{
	//描画
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}