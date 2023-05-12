#include "Ball.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Manager/BasePointManager/BasePointManager.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"
#include "../../Engine/ResourceManager/VFX.h"
#include <math.h>
#include <cmath>

namespace
{
	static const int ANGLE = 45.0f;		//�p�x
	static const float GRAVITY = 9.8f;	//�d��
}

//�R���X�g���N�^
Ball::Ball(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), ratio_(ZERO), strength_(ZERO,ZERO), endPointDirection_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)),
	startPoint_(ZERO, ZERO, ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), v0_(ZERO,ZERO), pLine_(nullptr),
	hEffect_(ZERO), flag(false), ballStatus_(BallStatus::PURPOSE_MOVE)
{
}

Ball::Ball(GameObject* parent)
	:NormalObject(parent, "Ball/Ball.fbx", "Ball"), ratio_(ZERO), strength_(ZERO, ZERO), endPointDirection_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
	startPoint_(ZERO,ZERO,ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), v0_(ZERO, ZERO), pLine_(nullptr),
    hEffect_(ZERO), flag(false), ballStatus_(BallStatus::PURPOSE_MOVE)
{}

//������
void Ball::ChildInitialize()
{
	//�e������
	XMFLOAT3 s = BasePointManager::GetRandomBasePoint(true);
	ARGUMENT_INITIALIZE(transform_.position_,s);
	ARGUMENT_INITIALIZE(startPoint_,s);
	ARGUMENT_INITIALIZE(endPoint_,BasePointManager::GetRandomBasePoint(false));
	ARGUMENT_INITIALIZE(endPointDirection_,endPoint_ - startPoint_);
	ARGUMENT_INITIALIZE(strength_.x, Random(1, 5));
	ARGUMENT_INITIALIZE(strength_.y, Random(1, 5));
	ARGUMENT_INITIALIZE(moveTime_, Random(1, 2));
	ARGUMENT_INITIALIZE(hTime_, Time::Add());
	ARGUMENT_INITIALIZE(v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(v0_.x, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(pLine_, new PolyLine);
	pLine_->Load("Image/Effect/tex.png");
	pLine_->AddPosition(transform_.position_);

	//���n�G�t�F�N�g�\��(���������ɕ\������Ɣ���Ă��܂��̂ŁA�����グ��)
	XMFLOAT3 pos = endPoint_;
	pos.y += 0.1f;
	ARGUMENT_INITIALIZE(hEffect_,OtherEffectManager::LandingEffect(pos, moveTime_));

	//�A���r�G���g
	Model::SetAmbient(hModel_, XMFLOAT4(1.0f, 1.0f, ZERO, ZERO));

	//�^�C���X�^�[�g
	Time::UnLock(hTime_);
}

//�X�V
void Ball::ChildUpdate()
{
	//��Ԃ��Ƃɕ�����
	switch (ballStatus_)
	{
	//�ړI�n�܂ňړ�
	case BallStatus::PURPOSE_MOVE:
		MoveToPurpose();
		break;

	//�o�E���h�ړ�
	case BallStatus::BOUND_MOVE:
		BoundMove();
		break;

	default:
		break;
	}
}

//�`��
void Ball::ChildDraw()
{
	pLine_->Draw();
}

//�ړI�n�܂ňړ�
void Ball::MoveToPurpose()
{
	//�ǂ̂��炢�̊������Ԃ������������߂�(0�`1)
	ARGUMENT_INITIALIZE(ratio_, (Time::GetTimef(hTime_) / moveTime_));

	//0�`1�͈̔͂ɂ����߂�
	ARGUMENT_INITIALIZE(ratio_, std::min<float>(ratio_, 1.0f));

	//���݂̈ʒu
	XMFLOAT3 nowPos = VectorToFloat3(startPoint_ + (endPointDirection_ * ratio_));
	nowPos.y = ((v0_.y * sin(XMConvertToRadians(ANGLE)) * ratio_) - (0.5f * GRAVITY * ratio_ * ratio_)) * strength_.y;
	nowPos.x = ((v0_.x * sin(XMConvertToRadians(ANGLE)) * ratio_) - (0.5f * GRAVITY * ratio_ * ratio_)) + nowPos.x * (1.0f - ratio_);
	nowPos.x -= sin(XMConvertToRadians(PI_DEGREES * ratio_)) * strength_.x;

	//�ړ��O�̃|�W�V�����ۑ�
	XMFLOAT3 beforePos = transform_.position_;

	//���߂��|�W�V�����ݒ�
	ARGUMENT_INITIALIZE(transform_.position_, nowPos);
	pLine_->AddPosition(transform_.position_);

	//�i�s�x�N�g�������߂�
	ARGUMENT_INITIALIZE(progressVector_, transform_.position_ - beforePos);

	//�����ڕW�n�_�܂ł̈ړ����I������̂Ȃ�
	if (ratio_ >= 1.0f)
	{
		//���˃x�N�g�������߂Đi�s�x�N�g���Ƃ���
		ARGUMENT_INITIALIZE(progressVector_, XMVector3Reflect(progressVector_, UP_VECTOR));
		
		//�o�E���h��Ԃ�
		ARGUMENT_INITIALIZE(ballStatus_, BallStatus::BOUND_MOVE);
		
		Time::Reset(hTime_);
		VFX::ForcedEnd(hEffect_);
		//Reset();
	}
}

//�o�E���h�ړ�
void Ball::BoundMove()
{
	static int a = 1;

	ARGUMENT_INITIALIZE(transform_.position_, VectorToFloat3(transform_.position_ + XMVector3Normalize(progressVector_) * 0.2f));

	progressVector_ -= XMVectorSet(ZERO, 0.015f, ZERO, ZERO);

	pLine_->AddPosition(transform_.position_);

	if (transform_.position_.y < ZERO)
	{

		ARGUMENT_INITIALIZE(progressVector_, XMVector3Reflect(progressVector_, UP_VECTOR));
		a++;

		if (a == 3)
		{
			//�o�E���h��Ԃ�
			ARGUMENT_INITIALIZE(ballStatus_, BallStatus::PURPOSE_MOVE);
			a = 1;
			Time::Reset(hTime_);
			VFX::ForcedEnd(hEffect_);
			Reset();
		}
	}
}

//���Z�b�g(�n�_�I�_���ׂčĐݒ�)
void Ball::Reset()
{

	if (flag)
	{
		ARGUMENT_INITIALIZE(startPoint_, transform_.position_);
		ARGUMENT_INITIALIZE(endPoint_, BasePointManager::GetRandomBasePoint(false));
		ARGUMENT_INITIALIZE(endPointDirection_, endPoint_ - startPoint_);
		ARGUMENT_INITIALIZE(v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(v0_.x, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(moveTime_, Random(1, 2))
		ARGUMENT_INITIALIZE(strength_.y, Random(1, 5));
		ARGUMENT_INITIALIZE(strength_.x, Random(1, 5));
		Time::Reset(hTime_);

		//���n�G�t�F�N�g�\��(���������ɕ\������Ɣ���Ă��܂��̂ŁA�����グ��)
		XMFLOAT3 pos = endPoint_;
		pos.y += 0.1f;
		VFX::ForcedEnd(hEffect_);
		ARGUMENT_INITIALIZE(hEffect_, OtherEffectManager::LandingEffect(pos, moveTime_));

		flag = false;
	}
	else
	{
		ARGUMENT_INITIALIZE(startPoint_, transform_.position_);
		ARGUMENT_INITIALIZE(endPoint_, BasePointManager::GetRandomBasePoint(true));
		ARGUMENT_INITIALIZE(endPointDirection_, endPoint_ - startPoint_);
		ARGUMENT_INITIALIZE(v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(v0_.x, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(moveTime_, Random(1, 2))
		ARGUMENT_INITIALIZE(strength_.y, Random(1, 5));
		ARGUMENT_INITIALIZE(strength_.x, Random(1, 5));
		Time::Reset(hTime_);

		//���n�G�t�F�N�g�\��(���������ɕ\������Ɣ���Ă��܂��̂ŁA�����グ��)
		XMFLOAT3 pos = endPoint_;
		pos.y += 0.1f;
		VFX::ForcedEnd(hEffect_);
		ARGUMENT_INITIALIZE(hEffect_, OtherEffectManager::LandingEffect(pos, moveTime_));

		flag = true;
	}
}