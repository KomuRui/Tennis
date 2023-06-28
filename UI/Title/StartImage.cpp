#include "StartImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Time.h"

//�萔
namespace
{
	static const float CHANGE_VALUE = 0.015f; //�ω���
	static const float MAX_ALPHA = 1.0f;	  //�ő哧���x
	static const float MIN_ALPHA = 0.2f;	  //�ŏ������x
}

//�R���X�g���N�^
StartImage::StartImage(GameObject* parent, std::string modelPath, std::string name)
	: ImageBase(parent, modelPath, name), nowAlpha_(MAX_ALPHA), sign_(-1)
{
}

//������
void StartImage::ChildInitialize()
{
	//��������Ȃ����Ă���
	ImageManager::SetAlpha(hPict_, nowAlpha_);
}

//�X�V
void StartImage::ChildUpdate()
{
	//�l���Z
	nowAlpha_ += CHANGE_VALUE * sign_;
	ImageManager::SetAlpha(hPict_, nowAlpha_);

	//�͈͊O�Ȃ畄����ς���
	if (nowAlpha_ < MIN_ALPHA || nowAlpha_ > MAX_ALPHA) sign_ *= -1;

	//�����x���͈͓��Ɏ��܂�悤��
	ARGUMENT_INITIALIZE(nowAlpha_,Clamp<float>(nowAlpha_, MAX_ALPHA, MIN_ALPHA));
}

