#include "Ball.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Manager/BasePointManager/BasePointManager.h"
#include "../../Engine/ResourceManager/Time.h"

//�R���X�g���N�^
Ball::Ball(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), ratio(ZERO), upStrength_(ZERO), endPointDirection_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)),
	startPoint_(ZERO, ZERO, ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f)
{
}

Ball::Ball(GameObject* parent)
	:NormalObject(parent, "Ball/Ball.fbx", "Ball"), ratio(ZERO), upStrength_(ZERO), endPointDirection_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
	startPoint_(ZERO,ZERO,ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f)
{}

//������
void Ball::ChildInitialize()
{
	//�e������
	ARGUMENT_INITIALIZE(transform_.position_,BasePointManager::GetBasePoint("Back_R", true));
	ARGUMENT_INITIALIZE(startPoint_,BasePointManager::GetBasePoint("Back_R", true));
	ARGUMENT_INITIALIZE(endPoint_,BasePointManager::GetBasePoint("Back_R", false));
	ARGUMENT_INITIALIZE(endPointDirection_,endPoint_ - startPoint_);
	ARGUMENT_INITIALIZE(upStrength_,4.0f);
	ARGUMENT_INITIALIZE(hTime_, Time::Add());
	Time::UnLock(hTime_);
}

//�X�V
void Ball::ChildUpdate()
{
	//�ǂ̂��炢�̊������Ԃ������������߂�(0�`1)
	ARGUMENT_INITIALIZE(ratio, (Time::GetTimef(hTime_) / moveTime_));

	//0�`1�͈̔͂ɂ����߂�
	ARGUMENT_INITIALIZE(ratio, std::min<float>(ratio, 1.0f));

	//���݂̈ʒu
	XMFLOAT3 nowPos = VectorToFloat3(startPoint_ + (endPointDirection_ * ratio));
	nowPos.y = (6 *  sin(XMConvertToRadians(55)) * ratio) - (0.5 * 9.8f * ratio * ratio);


	ARGUMENT_INITIALIZE(transform_.position_, nowPos);

	//�����ڕW�n�_�܂ł̈ړ����I������̂Ȃ�
	if (ratio >= 1.0f) Reset();
}

//���Z�b�g(�n�_�I�_���ׂčĐݒ�)
void Ball::Reset()
{
	static bool flag = false;

	if (flag)
	{
		ARGUMENT_INITIALIZE(transform_.position_, BasePointManager::GetBasePoint("Back_R", true));
		ARGUMENT_INITIALIZE(startPoint_, BasePointManager::GetBasePoint("Back_R", true));
		ARGUMENT_INITIALIZE(endPoint_, BasePointManager::GetBasePoint("Back_R", false));
		ARGUMENT_INITIALIZE(endPointDirection_, endPoint_ - startPoint_);
		Time::Reset(hTime_);

		flag = false;
	}
	else
	{
		ARGUMENT_INITIALIZE(transform_.position_, BasePointManager::GetBasePoint("Back_R", false));
		ARGUMENT_INITIALIZE(startPoint_, BasePointManager::GetBasePoint("Back_R", false));
		ARGUMENT_INITIALIZE(endPoint_, BasePointManager::GetBasePoint("Back_R", true));
		ARGUMENT_INITIALIZE(endPointDirection_, endPoint_ - startPoint_);
		Time::Reset(hTime_);

		flag = true;
	}
}