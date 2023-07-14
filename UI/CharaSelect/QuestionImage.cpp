#include "QuestionImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//定数
namespace
{
	static const XMFLOAT3 INITIAL_SCALE = { 1.0f, ZERO, ZERO };  //初期拡大率
	static const float EASING_TIME = 1.0f;                       //イージング時間
}

//コンストラクタ
QuestionImage::QuestionImage(GameObject* parent, std::string modelPath, std::string name)
	:EasingImage(parent, modelPath, name)
{}

//初期化
void QuestionImage::ChildInitialize()
{
	easing_->Reset(&transform_->scale_, INITIAL_SCALE, transform_->scale_, EASING_TIME, Easing::OutBack);
	ARGUMENT_INITIALIZE(transform_->scale_, INITIAL_SCALE);
}
