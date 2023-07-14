#include "CourtSelectScreenFadeImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//定数
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 2.0f, ZERO, ZERO };  //ポジションに対しての加算値
	static const float EASING_TIME = 1.0f;                       //イージング時間
}

//コンストラクタ
CourtSelectScreenFadeImage::CourtSelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name)
	:EasingImage(parent, modelPath, name)
{}

//初期化
void CourtSelectScreenFadeImage::ChildInitialize()
{
	ImageManager::SetSprite(hPict_, Direct3D::pScreen.get());
	ImageManager::SetScreenCapture(hPict_, true);
	easing_->Reset(&transform_->position_, transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), EASING_TIME, Easing::InCubic);
}
