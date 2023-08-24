#include "VSImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//定数
namespace
{
	static const XMFLOAT3 SCALE_ADD_VALUE = { 4.0f, 4.0f, ZERO };  //ポジションに対しての加算値
	static const float EASING_TIME = 2.5f;                         //イージング時間
}

//コンストラクタ
VSImage::VSImage(GameObject* parent, std::string modelPath, std::string name)
	:EasingImage(parent, modelPath, name)
{}

//初期化
void VSImage::ChildInitialize()
{
	easing_->Reset(&transform_->scale_, VectorToFloat3(transform_->scale_ + SCALE_ADD_VALUE), transform_->scale_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->scale_, VectorToFloat3(transform_->scale_ + SCALE_ADD_VALUE));
}