#include "RogoImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//�萔
namespace
{
	static const XMFLOAT3 POS_ADD_VALUE = { -0.4, ZERO, ZERO }; //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const float EASING_TIME = 1.0f;                      //�C�[�W���O����
}

//�R���X�g���N�^
RogoImage::RogoImage(GameObject* parent, std::string modelPath, std::string name)
	:EasingImage(parent, modelPath, name)
{}

//������
void RogoImage::ChildInitialize()
{
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutCubic);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));
}