#include "Sky.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/DirectX/Direct3D.h"

//コンストラクタ
Sky::Sky(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), scroll(ZERO)
{}

//初期化
void Sky::ChildInitialize()
{
	ModelManager::SetShederType(hModel_, Direct3D::SHADER_NORMALMAP);
	SetShadow(false);
}

//更新
void Sky::ChildUpdate()
{
	//UVスクロール
	scroll += 0.003f;
	ModelManager::SetUvScroll(hModel_, scroll);
}

