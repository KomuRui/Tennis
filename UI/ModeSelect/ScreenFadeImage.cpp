#include "ScreenFadeImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"
#include "../../Engine/DirectX/Sprite.h"

//�萔
namespace
{
	static const float ALPAH_ADD_VALUE = -0.02f; //�����x�ɑ΂��Ẳ��Z�l
}

//�R���X�g���N�^
ScreenFadeImage::ScreenFadeImage(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent, modelPath,"ScreenFadeImage"), nowAlpha_(1.0f)
{
}

//������
void ScreenFadeImage::ChildInitialize()
{
	ImageManager::SetSprite(hPict_,Direct3D::pScreen);
	ImageManager::SetScreenCapture(hPict_, true);
}

//�X�V
void ScreenFadeImage::ChildUpdate()
{
	nowAlpha_ += ALPAH_ADD_VALUE;
	ImageManager::SetAlpha(hPict_, nowAlpha_);
}

