#include "Water.h"
#include "../../Engine/ResourceManager/Model.h"

//コンストラクタ
Water::Water(GameObject* parent, std::string modelFilePath_, std::string name)
	:NormalObject(parent,modelFilePath_,name), scroll(ZERO)
{}

//初期化
void Water::ChildInitialize()
{
	//ノーマルマップを使う
	Model::SetShederType(hModel_, Direct3D::SHADER_NORMALMAP);
}

//更新
void Water::ChildUpdate()
{
	//UVスクロール
	scroll += 0.008f;
	Model::SetUvScroll(hModel_, scroll);
}