#include "PlaySelectScreenFadeImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//�萔
namespace
{
	static const float ALPAH_ADD_VALUE = -0.02f; //�����x�ɑ΂��Ẳ��Z�l
}

//�R���X�g���N�^
PlaySelectScreenFadeImage::PlaySelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent, modelPath, name), nowAlpha_(1.0f)
{}

//������
void PlaySelectScreenFadeImage::ChildInitialize()
{
	ImageManager::SetSprite(hPict_, Direct3D::pScreen.get());
	ImageManager::SetScreenCapture(hPict_, true);
}

//�X�V
void PlaySelectScreenFadeImage::ChildUpdate()
{
	nowAlpha_ += ALPAH_ADD_VALUE;
	ImageManager::SetAlpha(hPict_, nowAlpha_);
}
