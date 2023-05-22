#include "Ball.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Manager/BasePointManager/BasePointManager.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"
#include "../../Engine/ResourceManager/VFX.h"
#include "../../Engine/Collider/SphereCollider.h"
#include <math.h>
#include <cmath>

namespace
{
	static const int ANGLE = 45;			        //�p�x
	static const int ADD_ANGLE_VALUE = 15;          //���Z����p�x�̒l
	static const float GRAVITY = 9.8f;		        //�d��
	static const float MAX_RATIO = 1.0f;	        //�ő�̊���
	static const float LANDING_EFFECT_POS_Y = 0.1f; //���n�G�t�F�N�g��Y�|�W�V����
	static const float MAX_POS_X = 4.34f;           //�ő�X�l
	static const float MAX_POS_Z = 11.9f;           //�ő�Z�l
	static const float MIN_POS_X = -4.34f;          //�ŏ�X�l
	static const float MIN_POS_Z = -11.9f;          //�ŏ�Z�l

	static const XMFLOAT4 AMBIENT_COLOR = { 1.0f, 1.0f, ZERO, ZERO }; //�A���r�G���g�F
}

//�R���X�g���N�^
Ball::Ball(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), ratio_(ZERO), strength_(ZERO,ZERO), endPointDirection_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)),
	startPoint_(ZERO, ZERO, ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), v0_(ZERO,ZERO), pLine_(nullptr),
	hEffect_(ZERO), isGoToBasePoint_(true), ballStatus_(BallStatus::PURPOSE_MOVE), boundCount_(ZERO)
{
}

Ball::Ball(GameObject* parent)
	:NormalObject(parent, "Ball/Ball.fbx", "Ball"), ratio_(ZERO), strength_(ZERO, ZERO), endPointDirection_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
	startPoint_(ZERO,ZERO,ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), v0_(ZERO, ZERO), pLine_(nullptr),
    hEffect_(ZERO), isGoToBasePoint_(true), ballStatus_(BallStatus::PURPOSE_MOVE), boundCount_(ZERO)
{}

//������
void Ball::ChildInitialize()
{
	//�e������
	ARGUMENT_INITIALIZE(transform_.position_, BasePointManager::GetRandomBasePoint(true));
	ARGUMENT_INITIALIZE(startPoint_, transform_.position_);
	ARGUMENT_INITIALIZE(endPoint_,BasePointManager::GetRandomBasePoint(false));
	ARGUMENT_INITIALIZE(endPointDirection_,endPoint_ - startPoint_);
	ARGUMENT_INITIALIZE(strength_.x, Random(1, 5));
	ARGUMENT_INITIALIZE(strength_.y, Random(2, 5));
	ARGUMENT_INITIALIZE(moveTime_, 0.7f);
	ARGUMENT_INITIALIZE(hTime_, Time::Add());
	ARGUMENT_INITIALIZE(v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(v0_.x, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(pLine_, new PolyLine);
	pLine_->Load("Image/Effect/tex.png");
	pLine_->AddPosition(transform_.position_);

	//���n�G�t�F�N�g�\��(���������ɕ\������Ɣ���Ă��܂��̂ŁA�����グ��)
	XMFLOAT3 pos = endPoint_;
	ARGUMENT_INITIALIZE(pos.y, LANDING_EFFECT_POS_Y);
	ARGUMENT_INITIALIZE(hEffect_,OtherEffectManager::LandingEffect(pos, moveTime_));

	//�����蔻��
	SphereCollider* collision = new SphereCollider({ ZERO,ZERO,ZERO },0.1f);
	AddCollider(collision);

	//�A���r�G���g
	Model::SetAmbient(hModel_, AMBIENT_COLOR);

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
	//�|�����C���`��
	pLine_->Draw();
}

//�ړI�n�܂ňړ�
void Ball::MoveToPurpose()
{
	//�ǂ̂��炢�̊������Ԃ������������߂�(0�`1)
	ARGUMENT_INITIALIZE(ratio_, (Time::GetTimef(hTime_) / moveTime_));

	//0�`1�͈̔͂ɂ����߂�
	ARGUMENT_INITIALIZE(ratio_, std::min<float>(ratio_, MAX_RATIO));

	//���݂̈ʒu
	XMFLOAT3 nowPos = VectorToFloat3(startPoint_ + (endPointDirection_ * ratio_));
	nowPos.y = ((v0_.y * sin(XMConvertToRadians(ANGLE)) * ratio_) - (0.5f * GRAVITY * ratio_ * ratio_)) * strength_.y;

	//X�����̋�����0�ȊO�̂Ȃ�
	if (strength_.x != ZERO)
	{
		nowPos.x = ((v0_.x * sin(XMConvertToRadians(ANGLE)) * ratio_) - (0.5f * GRAVITY * ratio_ * ratio_)) + nowPos.x * (MAX_RATIO - ratio_);
		
		//���Ȃ�
		if(signbit(strength_.x))
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * ratio_)) * strength_.x * 2);
		//���Ȃ�
		else 
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * ratio_)) * strength_.x / 2);
	}

	//�ړ��O�̃|�W�V�����ۑ�
	XMFLOAT3 beforePos = transform_.position_;

	//���߂��|�W�V�����ݒ�
	ARGUMENT_INITIALIZE(transform_.position_, nowPos);
	pLine_->AddPosition(transform_.position_);

	//�i�s�x�N�g�������߂�
	ARGUMENT_INITIALIZE(progressVector_, transform_.position_ - beforePos);

	//�����ڕW�n�_�܂ł̈ړ����I������̂Ȃ�
	if (ratio_ >= MAX_RATIO)
	{
		//���˃x�N�g�������߂Đi�s�x�N�g���Ƃ���
		ARGUMENT_INITIALIZE(progressVector_, XMVector3Reflect(progressVector_, UP_VECTOR));
		
		//�o�E���h��Ԃ�
		ARGUMENT_INITIALIZE(ballStatus_, BallStatus::BOUND_MOVE);
		
		//�^�C�}�[���Z�b�g
		Time::Reset(hTime_);

		//�G�t�F�N�g�폜
		VFX::ForcedEnd(hEffect_);

		//�����˃x�N�g���̊p�x�����߂����̂Ő����˃x�N�g����Y�𖳎������x�N�g�������
		XMVECTOR v = { XMVectorGetX(progressVector_),ZERO,XMVectorGetZ(progressVector_),ZERO };

		//�����˃x�N�g���̊p�x�ŕ�������`���ƒႢ�e���ɂȂ�̂ŁA�萔���p�x�𑝂₷
		ARGUMENT_INITIALIZE(firstAngle_,GetDot(progressVector_, v) + XMConvertToRadians(ADD_ANGLE_VALUE));
	}
}

//�o�E���h�ړ�
void Ball::BoundMove()
{

	ARGUMENT_INITIALIZE(transform_.position_, VectorToFloat3(transform_.position_ + XMVector3Normalize(progressVector_) * 0.2f));

	float time = Time::GetTimef(hTime_);
	XMFLOAT3 nowPos = transform_.position_;
	nowPos.y = (v0_.y * sin(firstAngle_) * time) - (0.5f * GRAVITY * (time * time));

	transform_.position_.y = nowPos.y;

	pLine_->AddPosition(transform_.position_);

	if (transform_.position_.y < ZERO)
	{

		ARGUMENT_INITIALIZE(progressVector_, XMVector3Reflect(progressVector_, UP_VECTOR));
		
		XMVECTOR v = { XMVectorGetX(progressVector_),ZERO,XMVectorGetZ(progressVector_),ZERO };
		firstAngle_ = GetDot(progressVector_, v);
		Time::Reset(hTime_);
		v0_.y *= 0.4f;

		boundCount_++;

		if (boundCount_ == 2)
		{
			//���̖ړI�n�Ɉړ�����悤��
			ARGUMENT_INITIALIZE(ballStatus_, BallStatus::PURPOSE_MOVE);
			ARGUMENT_INITIALIZE(boundCount_,ZERO);

			Time::Reset(hTime_);
			VFX::ForcedEnd(hEffect_);
			Reset(isGoToBasePoint_,BasePointManager::GetRandomBasePointName());
		}
	}
}

//���Z�b�g(�n�_�I�_���ׂčĐݒ�)
void Ball::Reset(bool isGotoPlayer, string basePpointName)
{
	//�������|�W�V�������擾(���������_���ɂ��炷)
	XMFLOAT3 endPos = BasePointManager::GetBasePoint(basePpointName, isGotoPlayer);
	endPos.x += ((rand() % 31 + 1) / 10) * (rand() % 3 - 1);
	endPos.z += ((rand() % 31 + 1) / 10) * (rand() % 3 - 1);

	//�N�����v����
	ARGUMENT_INITIALIZE(endPos.x, Clamp<float>(endPos.x, MAX_POS_X, MIN_POS_X));
	ARGUMENT_INITIALIZE(endPos.z, Clamp<float>(endPos.z, MAX_POS_Z, MIN_POS_Z));

	//�e���Đݒ�
	ARGUMENT_INITIALIZE(startPoint_, transform_.position_);
	ARGUMENT_INITIALIZE(endPoint_, endPos);
	ARGUMENT_INITIALIZE(endPointDirection_, endPoint_ - startPoint_);
	ARGUMENT_INITIALIZE(v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(v0_.x, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(moveTime_, 0.7f)
	ARGUMENT_INITIALIZE(strength_.y, 1);
	ARGUMENT_INITIALIZE(strength_.x, 1.5f);
	Time::Reset(hTime_);

	//�l�b�g�����Ă�����{�[���̋O�����C������
	//�l�b�g��Z�ʒu��ʉ߂���Ƃ��̕b�������߂�
	float t = abs(startPoint_.z / abs(XMVectorGetZ(endPointDirection_)));

	//�l�b�g��Z�ʒu��ʉ߂���Ƃ���Y�ʒu�����߂�
	float y = (v0_.y * sin(XMConvertToRadians(ANGLE)) * t) - (0.5f * GRAVITY * pow(t, 2));

	//����Y�̈ʒu���l�b�g�̈ʒu���Ⴂ�Ȃ�
	if (y <= 1.2f)
	{
		//���������߂�
		float differential = 1.2f - y;

		//���� + �萔��Y�̋����𑝂₷
		strength_.y += differential * 2.0f;
	}

	//���n�G�t�F�N�g�\��(���������ɕ\������Ɣ���Ă��܂��̂ŁA�����グ��)
	XMFLOAT3 pos = endPoint_;
	ARGUMENT_INITIALIZE(pos.y, LANDING_EFFECT_POS_Y);
	VFX::ForcedEnd(hEffect_);
	ARGUMENT_INITIALIZE(hEffect_, OtherEffectManager::LandingEffect(pos, moveTime_));

	//���̖ړI�n�Ɉړ�����悤��
	ARGUMENT_INITIALIZE(ballStatus_, BallStatus::PURPOSE_MOVE);

	//�t�ɂ���
	if(isGotoPlayer)
		isGoToBasePoint_ = false;
	else
		isGoToBasePoint_ = true;
}

//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
void Ball::TimeMethod()
{
	Enter();
}