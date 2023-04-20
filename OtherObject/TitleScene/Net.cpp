#include "Net.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"

//コンストラクタ
Net::Net(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}
