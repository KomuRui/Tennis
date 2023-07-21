#include "PlaySelectScreenFadeImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//定数
namespace
{
	static const float EASING_TIME = 1.0f;                       //イージング時間
}

//コンストラクタ
PlaySelectScreenFadeImage::PlaySelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name)
	:EasingImage(parent, modelPath, name)
{}

//初期化
void PlaySelectScreenFadeImage::ChildInitialize()
{
	ImageManager::SetSprite(hPict_, Direct3D::pScreen.get());
	ImageManager::SetScreenCapture(hPict_, true);
	easing_->Reset(&transform_->scale_, transform_->scale_, { ZERO,ZERO,ZERO }, EASING_TIME, Easing::InCubic);
}

//更新
void PlaySelectScreenFadeImage::EasingImageChileUpdate()
{
	//回転させる
	transform_->rotate_.z += 10.0f;

	//イージングが終了したら削除
	if (easing_->IsFinish())KillMe();
}
