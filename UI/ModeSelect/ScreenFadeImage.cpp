#include "ScreenFadeImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"
#include "../../Engine/DirectX/Sprite.h"

//�R���X�g���N�^
ScreenFadeImage::ScreenFadeImage(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent, modelPath,"ScreenFadeImage")
{
}

//������
void ScreenFadeImage::ChildInitialize()
{
	ImageManager::SetSprite(hPict_,Direct3D::pScreen);
}

//�X�V
void ScreenFadeImage::ChildUpdate()
{

}