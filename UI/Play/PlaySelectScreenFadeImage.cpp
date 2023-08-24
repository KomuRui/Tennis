#include "PlaySelectScreenFadeImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//定数
namespace
{
	static const float ALPAH_ADD_VALUE = -0.02f; //透明度に対しての加算値
}

//コンストラクタ
PlaySelectScreenFadeImage::PlaySelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent, modelPath, name), nowAlpha_(1.0f)
{}

//初期化
void PlaySelectScreenFadeImage::ChildInitialize()
{
	ImageManager::SetSprite(hPict_, Direct3D::pScreen.get());
	ImageManager::SetScreenCapture(hPict_, true);
}

//更新
void PlaySelectScreenFadeImage::ChildUpdate()
{
	nowAlpha_ += ALPAH_ADD_VALUE;
	ImageManager::SetAlpha(hPict_, nowAlpha_);
}
