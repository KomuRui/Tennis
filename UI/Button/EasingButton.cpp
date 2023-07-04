#include "EasingButton.h"
#include "../../Engine/ResourceManager/ImageManager.h"


//コンストラクタ
EasingButton::EasingButton(GameObject* parent, std::string modelPath, std::string name)
	: ButtonBase(parent, modelPath, name)
{
	ARGUMENT_INITIALIZE(easing_, std::make_unique<EasingMove>());
}

//更新
void EasingButton::ChildButtonUpdate()
{
	//イージング
	easing_->Move();

	//継承用の
	EasingButtonChileUpdate();
}