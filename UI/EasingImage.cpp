#include "EasingImage.h"
#include "../Engine/ResourceManager/ImageManager.h"


//コンストラクタ
EasingImage::EasingImage(GameObject* parent, std::string modelPath, std::string name)
	: ImageBase(parent, modelPath, name)
{
	ARGUMENT_INITIALIZE(easing_, std::make_unique<EasingMove>());
}

//更新
void EasingImage::ChildUpdate()
{
	//イージング
	easing_->Move();

	//継承用の
	EasingImageChileUpdate();
}