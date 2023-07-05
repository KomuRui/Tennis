#include "EasingMove.h"
#include "../ResourceManager/Easing.h"
#include "../ResourceManager/Time.h"

//�R���X�g���N�^
EasingMove::EasingMove()
	:targetPos_(nullptr), beforePos_(XMFLOAT3(ZERO, ZERO, ZERO)), afterPos_(XMFLOAT3(ZERO, ZERO, ZERO)), moveTime_(ZERO), easingFunc(Easing::InBack), nowTime_(ZERO), timerhNum_((int)ZERO), isSet_(false), endEasingCount_(ZERO), beforeEndEasingCount_(ZERO)
{
	//�^�C�}�[�쐬
	ARGUMENT_INITIALIZE(timerhNum_, Time::Add());
}

//�R���X�g���N�^
EasingMove::EasingMove(XMFLOAT3* targetPos, XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float))
	:targetPos_(targetPos), beforePos_(beforePos), afterPos_(afterPos), moveTime_(moveTime), easingFunc(func), nowTime_(ZERO), timerhNum_((int)ZERO), isSet_(true), endEasingCount_(ZERO), beforeEndEasingCount_(ZERO)
{
	//�^�C�}�[�쐬
	ARGUMENT_INITIALIZE(timerhNum_,Time::Add());
}


//�C�[�W���O���Ȃ���ړ�
bool EasingMove::Move()
{
	if (!isSet_) return false;

	//�^�C�������b�N����Ă�����A�����b�N
	if (Time::isLock(timerhNum_)) Time::UnLock(timerhNum_);

	//�ǂ̂��炢�̊������Ԃ������������߂�(0�`1)
	ARGUMENT_INITIALIZE(nowTime_, (Time::GetTimef(timerhNum_) / moveTime_));

	//�����Ō�܂ŏI����Ă����̂Ȃ�true��Ԃ�
	if (nowTime_ > 1)
	{
		ARGUMENT_INITIALIZE(endEasingCount_, beforeEndEasingCount_ + 1);
		return true;
	}

	(*targetPos_) = beforePos_;
	float x = afterPos_.x - beforePos_.x;
	float y = afterPos_.y - beforePos_.y;
	float z = afterPos_.z - beforePos_.z;
	(*targetPos_).x += (x * (*easingFunc)(nowTime_));
	(*targetPos_).y += (y * (*easingFunc)(nowTime_));
	(*targetPos_).y += (z * (*easingFunc)(nowTime_));

	ARGUMENT_INITIALIZE(beforeEndEasingCount_, endEasingCount_);

	return false;
}

//���Z�b�g
void EasingMove::Reset(XMFLOAT3* targetPos,XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float))
{
	//�e�ϐ�������
	ARGUMENT_INITIALIZE(targetPos_, targetPos);
	ARGUMENT_INITIALIZE(beforePos_,beforePos);
	ARGUMENT_INITIALIZE(afterPos_,afterPos);
	ARGUMENT_INITIALIZE(moveTime_,moveTime);
	ARGUMENT_INITIALIZE(easingFunc,func);
	ARGUMENT_INITIALIZE(nowTime_,ZERO);
	ARGUMENT_INITIALIZE(isSet_,true);

	//�^�C��������
	Time::Reset(timerhNum_);
	Time::Lock(timerhNum_);
}

//�܂������Ă���̂��擾
bool EasingMove::IsMove()
{
	return (isSet_ && nowTime_ < 1);
}

/// <summary>
/// ������
/// </summary>
void EasingMove::Initialize()
{
	//��񏉊���
	ARGUMENT_INITIALIZE(nowTime_, ZERO);
	ARGUMENT_INITIALIZE(isSet_, false);

	//�^�C��������
	Time::Reset(timerhNum_);
	Time::Lock(timerhNum_);
}


