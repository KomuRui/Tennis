#include "ScreenFadeImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"
#include "../../Engine/DirectX/Sprite.h"

//コンストラクタ
ScreenFadeImage::ScreenFadeImage(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent, modelPath,"ScreenFadeImage")
{
}

//初期化
void ScreenFadeImage::ChildInitialize()
{
	ImageManager::SetSprite(hPict_,Direct3D::pScreen);
}

//更新
void ScreenFadeImage::ChildUpdate()
{

}