#include "TennisCourtAround.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/DirectX/Direct3D.h"

//�R���X�g���N�^
TennisCourtAround::TennisCourtAround(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{}

//������
void TennisCourtAround::ChildInitialize()
{
	SetShadow(false);
}

