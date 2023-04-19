#include "EasingMove.h"
#include "../ResourceManager/Easing.h"
#include "../ResourceManager/Time.h"

//�R���X�g���N�^
EasingMove::EasingMove()
	:targetPos_(nullptr), beforePos_(XMFLOAT3(ZERO, ZERO, ZERO)), afterPos_(XMFLOAT3(ZERO, ZERO, ZERO)), moveTime_(ZERO), easingFunc(Easing::InBack), nowTime_(ZERO), timerhNum_((int)ZERO)
{}

//�R���X�g���N�^
EasingMove::EasingMove(XMFLOAT3* targetPos, XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float))
	:targetPos_(targetPos),beforePos_(beforePos),afterPos_(afterPos),moveTime_(moveTime), easingFunc(func), nowTime_(ZERO), timerhNum_((int)ZERO)
{
	//�^�C�}�[�쐬
	ARGUMENT_INITIALIZE(timerhNum_,Time::Add());
}


//�C�[�W���O���Ȃ���ړ�
bool EasingMove::Move()
{
	//�^�C�������b�N����Ă�����A�����b�N
	if (Time::isLock(timerhNum_)) Time::UnLock(timerhNum_);

	//�ǂ̂��炢�̊������Ԃ������������߂�(0�`1)
	ARGUMENT_INITIALIZE(nowTime_, (Time::GetTimef(timerhNum_) / moveTime_));

	//�����Ō�܂ŏI����Ă����̂Ȃ�true��Ԃ�
	if (nowTime_ > 1) return true;

	//�ړ�
	ARGUMENT_INITIALIZE(*targetPos_,VectorToFloat3(XMVectorLerp(XMLoadFloat3(&beforePos_), XMLoadFloat3(&afterPos_),(*easingFunc)(nowTime_))));


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

	//�^�C��������
	Time::Reset(timerhNum_);
	Time::Lock(timerhNum_);
}


