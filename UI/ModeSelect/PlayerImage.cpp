#include "PlayerImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//定数
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 0.4, ZERO, ZERO };  //ポジションに対しての加算値
	static const float EASING_TIME = 1.0f;                      //イージング時間
}

//コンストラクタ
PlayerImage::PlayerImage(GameObject* parent, std::string modelPath, std::string name)
	:EasingImage(parent, modelPath, name)
{}

//初期化
void PlayerImage::ChildInitialize()
{
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));
}