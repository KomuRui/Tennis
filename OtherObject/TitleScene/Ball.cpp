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
	:NormalObject(parent, modelPath, name), ratio(ZERO), strength_(ZERO,ZERO), endPointDirection_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)),
	startPoint_(ZERO, ZERO, ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), v0_(ZERO,ZERO), pLine_(nullptr),
	hEffect_(ZERO), flag(false)
{
}

Ball::Ball(GameObject* parent)
	:NormalObject(parent, "Ball/Ball.fbx", "Ball"), ratio(ZERO), strength_(ZERO, ZERO), endPointDirection_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
	startPoint_(ZERO,ZERO,ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), v0_(ZERO, ZERO), pLine_(nullptr),
    hEffect_(ZERO), flag(false)
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
	//�ǂ̂��炢�̊������Ԃ������������߂�(0�`1)
	ARGUMENT_INITIALIZE(ratio, (Time::GetTimef(hTime_) / 1));

	//0�`1�͈̔͂ɂ����߂�
	ARGUMENT_INITIALIZE(ratio, std::min<float>(ratio, 1.0f));

	//���݂̈ʒu
	XMFLOAT3 nowPos = VectorToFloat3(startPoint_ + (endPointDirection_ * ratio));
	nowPos.y = ((v0_.x * sin(XMConvertToRadians(ANGLE)) * ratio) - (0.5f * GRAVITY * ratio * ratio)) * strength_.y;
	nowPos.x = ((v0_.y * sin(XMConvertToRadians(ANGLE)) * ratio) - (0.5f * GRAVITY * ratio * ratio)) + nowPos.x * (1.0f - ratio);
	nowPos.x -= sin(XMConvertToRadians(PI_DEGREES * ratio)) * strength_.x;

	//���߂��|�W�V�����ݒ�
	ARGUMENT_INITIALIZE(transform_.position_, nowPos);
	pLine_->AddPosition(transform_.position_);

	//�����ڕW�n�_�܂ł̈ړ����I������̂Ȃ�
	if (ratio >= 1.0f) Reset();
}

//�`��
void Ball::ChildDraw()
{
	pLine_->Draw();
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