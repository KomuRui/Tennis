#include "TennisCourtAround.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/DirectX/Direct3D.h"

//コンストラクタ
TennisCourtAround::TennisCourtAround(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}

//初期化
void TennisCourtAround::ChildInitialize()
{
	SetShadow(false);
}

