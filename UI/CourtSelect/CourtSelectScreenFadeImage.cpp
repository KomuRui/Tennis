#include "CourtSelectScreenFadeImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//�萔
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { 2.0f, ZERO, ZERO };  //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const float EASING_TIME = 1.0f;                       //�C�[�W���O����
}

//�R���X�g���N�^
CourtSelectScreenFadeImage::CourtSelectScreenFadeImage(GameObject* parent, std::string modelPath, std::string name)
	:EasingImage(parent, modelPath, name)
{}

//������
void CourtSelectScreenFadeImage::ChildInitialize()
{
	ImageManager::SetSprite(hPict_, Direct3D::pScreen.get());
	ImageManager::SetScreenCapture(hPict_, true);
	easing_->Reset(&transform_->position_, transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), EASING_TIME, Easing::InCubic);
}
