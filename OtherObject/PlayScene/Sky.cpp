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
	ModelManager::SetMyShadowApply(hModel_,false);
	ModelManager::SetBrightness(hModel_, 1.0f);
	SetShadow(false);
}

//更新
void Sky::ChildUpdate()
{
}

