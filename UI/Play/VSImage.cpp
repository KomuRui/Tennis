#include "VSImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//定数
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { ZERO, -1.0, ZERO };  //ポジションに対しての加算値
	static const float EASING_TIME = 1.0f;                       //イージング時間
}

//コンストラクタ
VSImage::VSImage(GameObject* parent, std::string modelPath, std::string name)
	:EasingImage(parent, modelPath, name)
{}

//初期化
void VSImage::ChildInitialize()
{
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));
}