#include "QuestionImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"

//�萔
namespace
{
	static const XMFLOAT3 INITIAL_SCALE = { 1.0f, ZERO, ZERO };  //�����g�嗦
	static const float EASING_TIME = 1.0f;                       //�C�[�W���O����
}

//�R���X�g���N�^
QuestionImage::QuestionImage(GameObject* parent, std::string modelPath, std::string name)
	:EasingImage(parent, modelPath, name)
{}

//������
void QuestionImage::ChildInitialize()
{
	easing_->Reset(&transform_->scale_, INITIAL_SCALE, transform_->scale_, EASING_TIME, Easing::OutBack);
	ARGUMENT_INITIALIZE(transform_->scale_, INITIAL_SCALE);
}
