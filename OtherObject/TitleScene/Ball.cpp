#include "Ball.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Manager/BasePointManager/BasePointManager.h"
#include "../../Engine/ResourceManager/Time.h"
#include <math.h>
#include <cmath>

namespace
{
	static const int ANGLE = 45.0f;		//�p�x
	static const float GRAVITY = 9.8f;	//�d��
}

//�R���X�g���N�^
Ball::Ball(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), ratio(ZERO), upStrength_(ZERO), endPointDirection_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)),
	startPoint_(ZERO, ZERO, ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), v0_(ZERO)
{
}

Ball::Ball(GameObject* parent)
	:NormalObject(parent, "Ball/Ball.fbx", "Ball"), ratio(ZERO), upStrength_(ZERO), endPointDirection_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
	startPoint_(ZERO,ZERO,ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), v0_(ZERO)
{}

//������
void Ball::ChildInitialize()
{
	//�e������
	ARGUMENT_INITIALIZE(transform_.position_,BasePointManager::GetBasePoint("Back_R", true));
	ARGUMENT_INITIALIZE(startPoint_,BasePointManager::GetBasePoint("Back_R", true));
	ARGUMENT_INITIALIZE(endPoint_,BasePointManager::GetBasePoint("Back_R", false));
	ARGUMENT_INITIALIZE(endPointDirection_,endPoint_ - startPoint_);
	ARGUMENT_INITIALIZE(upStrength_, Random(1, 5));
	ARGUMENT_INITIALIZE(moveTime_, Random(1, 2));
	ARGUMENT_INITIALIZE(hTime_, Time::Add());
	ARGUMENT_INITIALIZE(v0_, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
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
	nowPos.y = ((v0_ *  sin(XMConvertToRadians(ANGLE)) * ratio) - (0.5 * GRAVITY * ratio * ratio)) * upStrength_;


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
		ARGUMENT_INITIALIZE(v0_, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(moveTime_, Random(1, 2))
		ARGUMENT_INITIALIZE(upStrength_, Random(1, 5));
		Time::Reset(hTime_);

		flag = false;
	}
	else
	{
		ARGUMENT_INITIALIZE(transform_.position_, BasePointManager::GetBasePoint("Back_R", false));
		ARGUMENT_INITIALIZE(startPoint_, BasePointManager::GetBasePoint("Back_R", false));
		ARGUMENT_INITIALIZE(endPoint_, BasePointManager::GetBasePoint("Back_R", true));
		ARGUMENT_INITIALIZE(endPointDirection_, endPoint_ - startPoint_);
		ARGUMENT_INITIALIZE(v0_, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(moveTime_, Random(1, 2))
		ARGUMENT_INITIALIZE(upStrength_, Random(1, 5));
		Time::Reset(hTime_);

		flag = true;
	}
}