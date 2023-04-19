#include "ScalingImage.h"
#include "../Engine/ResourceManager/Image.h"

//�萔
namespace
{
	static const XMVECTOR MIN_SCALE = { 0.0f,0.0f,0.0f };  //�Œ�g�嗦
	static const XMVECTOR MAX_SCALE = { 0.1f,0.1f,0.0f };  //�ō��g�嗦
	static const float INTERPOLATION_FACTOR = 0.05f;       //��ԌW��
	static const float CHANGE_TARGET_DISTANCE = 0.01f;     //�^�[�Q�b�g�ύX����Ƃ��̋���
}

//�R���X�g���N�^
ScalingImage::ScalingImage(GameObject* parent, std::string modelPath, std::string name)
	: ImageBase(parent, modelPath, name)
{
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void ScalingImage::ChildStartUpdate()
{
	//��Ԃ���O�̊g�嗦�ۑ�
	ARGUMENT_INITIALIZE(beforeScale_, (XMLoadFloat3(&transform_.scale_) + MIN_SCALE));

	//���̖ڕW�Ƃ���g�嗦�̕ۑ�
	ARGUMENT_INITIALIZE(targetScale_, (XMLoadFloat3(&transform_.scale_) + MAX_SCALE));
}

//�X�V
void ScalingImage::ChildUpdate()
{
	//�g�嗦���Ԃ��Ȃ���ς��Ă���
	XMStoreFloat3(&transform_.scale_, XMVectorLerp(XMLoadFloat3(&transform_.scale_), targetScale_, INTERPOLATION_FACTOR));

	//������0.01���Z���̂Ȃ�
	if (RangeCalculation(transform_.scale_, VectorToFloat3(targetScale_)) < CHANGE_TARGET_DISTANCE)
	{
		//�^�[�Q�b�g����
		std::swap(beforeScale_, targetScale_);
	}
}