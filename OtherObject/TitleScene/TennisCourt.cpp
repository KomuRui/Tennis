#include "TennisCourt.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"

//コンストラクタ
TennisCourt::TennisCourt(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent,modelPath,name)
{}
