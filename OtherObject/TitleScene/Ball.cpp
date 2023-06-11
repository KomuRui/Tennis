#include "Ball.h"
#include "../../Engine/System.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../OtherObject/TitleScene/Referee.h"
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
	static const XMVECTOR TOSS_UP_VALUE = { ZERO,0.2f,ZERO,ZERO };    //�g�X�A�b�v�̎��̒l

	static const XMFLOAT4 AMBIENT_COLOR = { 1.0f, 1.0f, ZERO, ZERO }; //�A���r�G���g�F
}

//�R���X�g���N�^
Ball::Ball(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{
	hShadowModel_ = ZERO;
	ballInfo_.ratio_ = ZERO;
	ballInfo_.hTime_ = ZERO;
	ballInfo_.boundCount_ = ZERO;
	ballInfo_.hTime_ = ZERO;
	ballInfo_.moveTime_ = 1.0f;
	ballInfo_.strength_ = { ZERO,ZERO };
	ballInfo_.v0_ = { ZERO,ZERO };
	ballInfo_.endPointDirection_ = XMVectorSet(ZERO, ZERO, ZERO, ZERO);
	ballInfo_.tossUpVector_ = TOSS_UP_VALUE;
	ballInfo_.startPoint_ = { ZERO, ZERO, ZERO };
	ballInfo_.endPoint_ = { ZERO, ZERO, ZERO };
	ballInfo_.pLine_ = nullptr;
	ballInfo_.isGoToBasePoint_ = false;
	ballInfo_.isTossUp_ = false;
	ballInfo_.hLandEffectName_ = "LandEffect";
	ballInfo_.hDropEffectName_ = "DropEffect";
	ballInfo_.dropEffectFilePath_ = "Effect/SliceDrop.txt";
	ballInfo_.ballStatus_ = BallStatus::PLAYER_HAV_BALL;
}

Ball::Ball(GameObject* parent)
	:NormalObject(parent, "Ball/Ball.fbx", "Ball")
{
	hShadowModel_ = ZERO;
	ballInfo_.ratio_ = ZERO;
	ballInfo_.hTime_ = ZERO;
	ballInfo_.boundCount_ = ZERO;
	ballInfo_.hTime_ = ZERO;
	ballInfo_.moveTime_ = 1.0f;
	ballInfo_.strength_ = { ZERO,ZERO };
	ballInfo_.v0_ = { ZERO,ZERO };
	ballInfo_.endPointDirection_ = XMVectorSet(ZERO, ZERO, ZERO, ZERO);
	ballInfo_.tossUpVector_ = TOSS_UP_VALUE;
	ballInfo_.startPoint_ = { ZERO, ZERO, ZERO };
	ballInfo_.endPoint_ = { ZERO, ZERO, ZERO };
	ballInfo_.pLine_ = nullptr;
	ballInfo_.isGoToBasePoint_ = false;
	ballInfo_.isTossUp_ = false;
	ballInfo_.hLandEffectName_ = "LandEffect";
	ballInfo_.hDropEffectName_ = "DropEffect";
	ballInfo_.dropEffectFilePath_ = "Effect/SliceDrop.txt";
	ballInfo_.ballStatus_ = BallStatus::PLAYER_HAV_BALL;
}

//������
void Ball::ChildInitialize()
{
	//�e������
	//ARGUMENT_INITIALIZE(transform_->position_, BasePointManager::GetRandomBasePoint(true));
	//ARGUMENT_INITIALIZE(startPoint_, transform_->position_);
	//ARGUMENT_INITIALIZE(endPoint_,BasePointManager::GetRandomBasePoint(false));
	//ARGUMENT_INITIALIZE(endPointDirection_,endPoint_ - startPoint_);
	//ARGUMENT_INITIALIZE(strength_.x, Random(1, 5));
	//ARGUMENT_INITIALIZE(strength_.y, Random(2, 5));
	//ARGUMENT_INITIALIZE(moveTime_, 0.7f);
	//ARGUMENT_INITIALIZE(hTime_, Time::Add());
	//ARGUMENT_INITIALIZE(v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	//ARGUMENT_INITIALIZE(v0_.x, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(ballInfo_.pLine_, new PolyLine);
	ballInfo_.pLine_->Load("Image/Effect/circle_Wh.png");
	ballInfo_.pLine_->AddPosition(transform_->position_);

	//�e�̃��f�����[�h
	ARGUMENT_INITIALIZE(hShadowModel_, ModelManager::Load("Ball/BallShadow.fbx"));
	assert(hShadowModel_ >= ZERO);
	ARGUMENT_INITIALIZE(tShadow_.position_, transform_->position_);
	ARGUMENT_INITIALIZE(tShadow_.position_.y, 0.2f);
	SetShadow(false);

	//���n�G�t�F�N�g�\��(���������ɕ\������Ɣ���Ă��܂��̂ŁA�����グ��)
	//XMFLOAT3 pos = endPoint_;
	//ARGUMENT_INITIALIZE(pos.y, LANDING_EFFECT_POS_Y);
	//OtherEffectManager::LandingEffect(hLandEffectName_,pos, moveTime_);

	//���݂����ȃG�t�F�N�g�\��
	//EffectManager::Draw(hDropEffectName_,dropEffectFilePath_, transform_->position_);

	//�����蔻��
	sphere_ = AddComponent<SphereCollider>();
	sphere_->SetPos({ ZERO,ZERO,ZERO });
	sphere_->SetSize({ 0.1f,0.1f,0.1f });

	//�A���r�G���g
	ModelManager::SetAmbient(hModel_, AMBIENT_COLOR);

	//�^�C���X�^�[�g
	Time::UnLock(ballInfo_.hTime_);
}

//�X�V
void Ball::ChildUpdate()
{
	//��Ԃ��Ƃɕ�����
	switch (ballInfo_.ballStatus_)
	{

	//�ړI�n�܂ňړ�
	case BallStatus::PURPOSE_MOVE:
		MoveToPurpose();
		break;

	//�o�E���h�ړ�
	case BallStatus::BOUND_MOVE:
		BoundMove();
		break;

	//�v���C���[���{�[���������Ă�����
	case BallStatus::PLAYER_HAV_BALL:
		PlayerHavingBall();
		break;

	//��~
	case BallStatus::STOP:
		Stop();
		break;

	default:
		break;
	}

	//�e�̃|�W�V�����X�V
	ARGUMENT_INITIALIZE(tShadow_.position_, transform_->position_);
	ARGUMENT_INITIALIZE(tShadow_.position_.y, 0.01f);
}

//�`��
void Ball::ChildDraw()
{
	//�e�`��
	ModelManager::SetTransform(hShadowModel_, &tShadow_);
	ModelManager::Draw(hShadowModel_);

	//�|�����C���`��
	ballInfo_.pLine_->Draw();
}

//�ړI�n�܂ňړ�
void Ball::MoveToPurpose()
{
	//�ǂ̂��炢�̊������Ԃ������������߂�(0�`1)
	ARGUMENT_INITIALIZE(ballInfo_.ratio_, (Time::GetTimef(ballInfo_.hTime_) / ballInfo_.moveTime_));

	//0�`1�͈̔͂ɂ����߂�
	ARGUMENT_INITIALIZE(ballInfo_.ratio_, std::min<float>(ballInfo_.ratio_, MAX_RATIO));

	//���݂̈ʒu
	XMFLOAT3 nowPos = VectorToFloat3(ballInfo_.startPoint_ + (ballInfo_.endPointDirection_ * ballInfo_.ratio_));
	nowPos.y = ((ballInfo_.v0_.y * sin(XMConvertToRadians(ANGLE)) * ballInfo_.ratio_) - (0.5f * GRAVITY * ballInfo_.ratio_ * ballInfo_.ratio_)) * ballInfo_.strength_.y;
	nowPos.y += ballInfo_.startPoint_.y * (MAX_RATIO - ballInfo_.ratio_);

	//X�����̋�����0�ȊO�̂Ȃ�
	if (ballInfo_.strength_.x != ZERO)
	{
		nowPos.x = ((ballInfo_.v0_.x * sin(XMConvertToRadians(ANGLE)) * ballInfo_.ratio_) - (0.5f * GRAVITY * ballInfo_.ratio_ * ballInfo_.ratio_)) + nowPos.x * (MAX_RATIO - ballInfo_.ratio_);
		
		//���Ȃ�
		if(signbit(ballInfo_.strength_.x))
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * ballInfo_.ratio_)) * ballInfo_.strength_.x * 2);
		//���Ȃ�
		else 
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * ballInfo_.ratio_)) * ballInfo_.strength_.x / 2);
	}

	//�ړ��O�̃|�W�V�����ۑ�
	XMFLOAT3 beforePos = transform_->position_;

	//���߂��|�W�V�����ݒ�
	ARGUMENT_INITIALIZE(transform_->position_, nowPos);
	ballInfo_.pLine_->AddPosition(transform_->position_);

	//�G�t�F�N�g�̃|�W�V�����X�V
	ARGUMENT_INITIALIZE(VFX::GetEmitter(ballInfo_.hDropEffectName_)->data.position,transform_->position_);

	//�i�s�x�N�g�������߂�
	ARGUMENT_INITIALIZE(ballInfo_.progressVector_, transform_->position_ - beforePos);

	//�����ڕW�n�_�܂ł̈ړ����I������̂Ȃ�
	if (ballInfo_.ratio_ >= MAX_RATIO)
	{
		//���˃x�N�g�������߂Đi�s�x�N�g���Ƃ���
		ARGUMENT_INITIALIZE(ballInfo_.progressVector_, XMVector3Reflect(ballInfo_.progressVector_, UP_VECTOR));
		
		//�o�E���h��Ԃ�
		ARGUMENT_INITIALIZE(ballInfo_.ballStatus_, BallStatus::BOUND_MOVE);
		
		//�^�C�}�[���Z�b�g
		Time::Reset(ballInfo_.hTime_);

		//�����˃x�N�g���̊p�x�����߂����̂Ő����˃x�N�g����Y�𖳎������x�N�g�������
		XMVECTOR v = { XMVectorGetX(ballInfo_.progressVector_),ZERO,XMVectorGetZ(ballInfo_.progressVector_),ZERO };

		//�����˃x�N�g���̊p�x�ŕ�������`���ƒႢ�e���ɂȂ�̂ŁA�萔���p�x�𑝂₷
		ARGUMENT_INITIALIZE(ballInfo_.firstAngle_,GetDot(ballInfo_.progressVector_, v) + XMConvertToRadians(ADD_ANGLE_VALUE));
	}
}

//�o�E���h�ړ�
void Ball::BoundMove()
{
	//�ǂ̂��炢���Ԃ����������擾
	float time = Time::GetTimef(ballInfo_.hTime_);

	//�i�s�x�N�g���𑫂��Đi�߂�
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + XMVector3Normalize(ballInfo_.progressVector_) * 0.2f));
	
	//���݂̈ʒu�����߂�
	XMFLOAT3 nowPos = transform_->position_;
	nowPos.y = (ballInfo_.v0_.y * sin(ballInfo_.firstAngle_) * time) - (0.5f * GRAVITY * (time * time));
	transform_->position_.y = nowPos.y;

	//�G�t�F�N�g�̃|�W�V�����X�V
	ballInfo_.pLine_->AddPosition(transform_->position_);
	ARGUMENT_INITIALIZE(VFX::GetEmitter(ballInfo_.hDropEffectName_)->data.position, transform_->position_);

	//�n�ʂɒ����ĂȂ��̂Ȃ炱�̐�͏������Ȃ�
	if (transform_->position_.y > ZERO) return;

	//�i�s�x�N�g�����X�V
	ARGUMENT_INITIALIZE(ballInfo_.progressVector_, XMVector3Reflect(ballInfo_.progressVector_, UP_VECTOR));
	
	//�i�s�x�N�g���̊p�x���X�V
	XMVECTOR v = { XMVectorGetX(ballInfo_.progressVector_),ZERO,XMVectorGetZ(ballInfo_.progressVector_),ZERO };
	ballInfo_.firstAngle_ = GetDot(ballInfo_.progressVector_, v);

	//�^�C�����Z�b�g
	Time::Reset(ballInfo_.hTime_);

	//Y�̋��x�����炷
	ballInfo_.v0_.y *= 0.4f;

	//�o�E���h�J�E���g���₷
	ballInfo_.boundCount_++;

	//2��o�E���h������
	if (ballInfo_.boundCount_ == 2)
	{
		//���̖ړI�n�Ɉړ�����悤��
		ARGUMENT_INITIALIZE(ballInfo_.ballStatus_, BallStatus::PURPOSE_MOVE);
		ARGUMENT_INITIALIZE(ballInfo_.boundCount_,ZERO);

		Time::Reset(ballInfo_.hTime_);
		VFX::ForcedEnd(ballInfo_.hLandEffectName_);
		VFX::ForcedEnd(ballInfo_.hDropEffectName_);

		//�ł����������_���Ɏ擾
		HitStrength h =  GameManager::GetpPlayer()->GetRacket()->GetRamdomHitStrength();

		//���Z�b�g
		Reset(h.strength_.x, h.strength_.y,h.moveTime_,BasePointManager::GetRandomBasePointName());
	}
}

//�v���C���[���{�[���������Ă����Ԃ̎��ɌĂԊ֐�
void Ball::PlayerHavingBall()
{
	ImGuiSet::DebugLog("tossup", VectorToFloat3(ballInfo_.tossUpVector_));
	ImGuiSet::DebugLog("flag", ballInfo_.isTossUp_);
	//�����g�X�A�b�v�����̂Ȃ�
	if (ballInfo_.isTossUp_)
	{
		//�{�[�����グ��
		ARGUMENT_INITIALIZE(transform_->position_,VectorToFloat3(transform_->position_ + ballInfo_.tossUpVector_));
		ballInfo_.tossUpVector_ -= XMVectorSet(ZERO, 0.0065f, ZERO, ZERO);

		//�����n�ʂ�艺�ɂȂ����̂Ȃ�
		if (transform_->GetPosition().y <= ZERO)
		{
			//�g�X�A�b�v�̃x�N�g���̒l�����ɖ߂�
			ARGUMENT_INITIALIZE(ballInfo_.tossUpVector_, TOSS_UP_VALUE);
			ARGUMENT_INITIALIZE(ballInfo_.isTossUp_, false);
			transform_->SetPositionY(ZERO);
		}
	}
}

//���Z�b�g(�n�_�I�_���ׂčĐݒ�)
void Ball::Reset(float strengthX, float strengthY, float moveTime,string basePpointName)
{
	//�������|�W�V�������擾(���������_���ɂ��炷)
	XMFLOAT3 endPos = BasePointManager::GetBasePoint(basePpointName, ballInfo_.isGoToBasePoint_);

	//�����[���̎�����
	if (GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_RALLY)
	{
		endPos.x += ((rand() % 31 + 1) / 10) * (rand() % 3 - 1);
		endPos.z += ((rand() % 31 + 1) / 10) * (rand() % 3 - 1);

		//�N�����v����
		ARGUMENT_INITIALIZE(endPos.x, Clamp<float>(endPos.x, MAX_POS_X, MIN_POS_X));
		ARGUMENT_INITIALIZE(endPos.z, Clamp<float>(endPos.z, MAX_POS_Z, MIN_POS_Z));
	}

	//�e���Đݒ�
	ARGUMENT_INITIALIZE(ballInfo_.startPoint_, transform_->position_);
	ARGUMENT_INITIALIZE(ballInfo_.endPoint_, endPos);
	ARGUMENT_INITIALIZE(ballInfo_.endPointDirection_, ballInfo_.endPoint_ - ballInfo_.startPoint_);
	ARGUMENT_INITIALIZE(ballInfo_.v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(ballInfo_.v0_.x, (ballInfo_.endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(ballInfo_.moveTime_, moveTime)
	ARGUMENT_INITIALIZE(ballInfo_.strength_.y, strengthY);
	ARGUMENT_INITIALIZE(ballInfo_.strength_.x, strengthX);
	Time::Reset(ballInfo_.hTime_);

	//�l�b�g�����Ă�����{�[���̋O�����C������
	//�l�b�g��Z�ʒu��ʉ߂���Ƃ��̕b�������߂�
	float t = abs(ballInfo_.startPoint_.z / abs(XMVectorGetZ(ballInfo_.endPointDirection_)));

	//�l�b�g��Z�ʒu��ʉ߂���Ƃ���Y�ʒu�����߂�
	float y = (ballInfo_.v0_.y * sin(XMConvertToRadians(ANGLE)) * t) - (0.5f * GRAVITY * pow(t, 2));

	//����Y�̈ʒu���l�b�g�̈ʒu���Ⴂ�Ȃ�
	if (y <= 1.2f)
	{
		//���������߂�
		float differential = 1.2f - y;

		//���� + �萔��Y�̋����𑝂₷
		ballInfo_.strength_.y += differential * 2.0f;
	}

	//���n�G�t�F�N�g�\��(���������ɕ\������Ɣ���Ă��܂��̂ŁA�����グ��)
	XMFLOAT3 pos = ballInfo_.endPoint_;
	ARGUMENT_INITIALIZE(pos.y, LANDING_EFFECT_POS_Y);
	VFX::ForcedEnd(ballInfo_.hLandEffectName_);
    OtherEffectManager::LandingEffect(ballInfo_.hLandEffectName_,pos, ballInfo_.moveTime_);

	//���݂����ȃG�t�F�N�g�\��
	VFX::ForcedEnd(ballInfo_.hDropEffectName_);
	EffectManager::Draw(ballInfo_.hDropEffectName_, ballInfo_.dropEffectFilePath_, transform_->position_);

	//���̖ړI�n�Ɉړ�����悤��
	ARGUMENT_INITIALIZE(ballInfo_.ballStatus_, BallStatus::PURPOSE_MOVE);

	//�t�ɂ���
	ARGUMENT_INITIALIZE(ballInfo_.isGoToBasePoint_, !ballInfo_.isGoToBasePoint_);
}

//�{�[���g�X�A�b�v����Ƃ��̃x�N�g�������Z�b�g
void Ball::ResetBallTossUpVec() 
{
	GameManager::GetpBall()->SetTossUp(false);
	ARGUMENT_INITIALIZE(ballInfo_.tossUpVector_, TOSS_UP_VALUE);
}

//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
void Ball::TimeMethod()
{
	Enter();
}

//�w�肵��Z�ʒu��ʉ߂���Ƃ��̃{�[���̈ʒu���擾
XMFLOAT3  Ball::GetSpecifyPosZBallPosition(float zPos)
{
	//�l�b�g��Z�ʒu��ʉ߂���Ƃ��̕b�������߂�
	float t = (zPos - ballInfo_.startPoint_.z) / XMVectorGetZ(ballInfo_.endPointDirection_);

	XMFLOAT3 nowPos = VectorToFloat3(ballInfo_.startPoint_ + (ballInfo_.endPointDirection_ * t));

	//X�����̋�����0�ȊO�̂Ȃ�
	if (ballInfo_.strength_.x != ZERO)
	{
		nowPos.x = ((ballInfo_.v0_.x * sin(XMConvertToRadians(ANGLE)) * t) - (0.5f * GRAVITY * t * t)) + nowPos.x * (MAX_RATIO - t);

		//���Ȃ�
		if (signbit(ballInfo_.strength_.x))
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * t)) * ballInfo_.strength_.x * 2);
		//���Ȃ�
		else
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * t)) * ballInfo_.strength_.x / 2);
	}

	return nowPos;
}