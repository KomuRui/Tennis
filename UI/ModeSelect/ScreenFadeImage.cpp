#include "ScreenFadeImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"
#include "../../Engine/DirectX/Sprite.h"

//定数
namespace
{
	static const float ALPAH_ADD_VALUE = -0.02f; //透明度に対しての加算値
}

//コンストラクタ
ScreenFadeImage::ScreenFadeImage(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent, modelPath,"ScreenFadeImage"), nowAlpha_(1.0f)
{
}

//初期化
void ScreenFadeImage::ChildInitialize()
{
	ImageManager::SetSprite(hPict_,Direct3D::pScreen);
	ImageManager::SetScreenCapture(hPict_, true);
}

//更新
void ScreenFadeImage::ChildUpdate()
{
	nowAlpha_ += ALPAH_ADD_VALUE;
	ImageManager::SetAlpha(hPict_, nowAlpha_);
}

