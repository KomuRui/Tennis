#include "Racket.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"

//コンストラクタ
Racket::Racket(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}

Racket::Racket(GameObject* parent)
	:NormalObject(parent, "Racket/Normal.fbx", "Racket")
{}
