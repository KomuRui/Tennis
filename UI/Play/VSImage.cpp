#include "VSImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//�萔
namespace
{
	static const XMFLOAT3 SCALE_ADD_VALUE = { 4.0f, 4.0f, ZERO };  //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const float EASING_TIME = 2.5f;                         //�C�[�W���O����
}

//�R���X�g���N�^
VSImage::VSImage(GameObject* parent, std::string modelPath, std::string name)
	:EasingImage(parent, modelPath, name)
{}

//������
void VSImage::ChildInitialize()
{
	easing_->Reset(&transform_->scale_, VectorToFloat3(transform_->scale_ + SCALE_ADD_VALUE), transform_->scale_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->scale_, VectorToFloat3(transform_->scale_ + SCALE_ADD_VALUE));
}