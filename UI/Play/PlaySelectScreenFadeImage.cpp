#include "PlaySelectScreenFadeImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//�萔
namespace
{
	static const float EASING_TIME = 1.0f;                       //�C�[�W���O����
}

//�R���X�g���N�^
PlaySelectScreenFadeImage::PlaySelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name)
	:EasingImage(parent, modelPath, name)
{}

//������
void PlaySelectScreenFadeImage::ChildInitialize()
{
	ImageManager::SetSprite(hPict_, Direct3D::pScreen.get());
	ImageManager::SetScreenCapture(hPict_, true);
	easing_->Reset(&transform_->scale_, transform_->scale_, { ZERO,ZERO,ZERO }, EASING_TIME, Easing::InCubic);
}

//�X�V
void PlaySelectScreenFadeImage::EasingImageChileUpdate()
{
	//��]������
	transform_->rotate_.z += 10.0f;

	//�C�[�W���O���I��������폜
	if (easing_->IsFinish())KillMe();
}
