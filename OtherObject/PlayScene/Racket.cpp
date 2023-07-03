#include "Racket.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Manager/EffectManager/EffectManager.h"
#include "../../Manager/BasePointManager/BasePointManager.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/GUI/ImGuiSet.h"
#include "Ball.h"
#include "Referee.h"

//�萔
namespace
{		
	static const XMFLOAT3 RACKET_START_ROTATION_ANGLE = { 0,-185,0 };  //���P�b�g�̊J�n�p�x
	static const float RATIO_MIN_VALUE = 0.25f;                        //�����̍ŏ��l

	////////////////�R���C�_�[///////////////////

	static const int      BASE_ADD_ANGLE_VALUE = -80;    //�x�[�X�ɉ��Z����p�x�̒l
	static const float    COLLIDER_SIZE_X = 2.0f;        //�R���C�_�[�̃T�C�Y
	static const float    COLLIDER_SIZE_Y = 2.0f;        //�R���C�_�[�̃T�C�Y
	static const float    COLLIDER_SIZE_Z = 2.0f;        //�R���C�_�[�̃T�C�Y
}

//�R���X�g���N�^
Racket::Racket(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), type_(Type::FLAT), stroke_(Stroke::FOREHAND), colliderPos_(ZERO, ZERO, ZERO), ratio_(1.0)
{
}

Racket::Racket(GameObject* parent)
	:NormalObject(parent, "Racket/Normal.fbx", "Racket"), type_(Type::FLAT), stroke_(Stroke::FOREHAND), colliderPos_(ZERO, ZERO, ZERO), ratio_(1.0)
{}

//�f�X�g���N�^
Racket::~Racket()
{
}

//������
void Racket::ChildInitialize()
{
	//�p�x�C��
	ARGUMENT_INITIALIZE(transform_->rotate_, RACKET_START_ROTATION_ANGLE);

	//���邳�ő�l�ɐݒ�
	//ModelManager::SetBrightness(hModel_, 1.0f);

	ModelManager::SetMyShadowApply(hModel_, false);
	
	//���킲�Ƃ̃{�[���̐F��ݒ�
	ARGUMENT_INITIALIZE(lineColor_[Type::FLAT], XMFLOAT4(1, 0.5f, 1, 1));
	ARGUMENT_INITIALIZE(lineColor_[Type::LOB], XMFLOAT4(1, 1, ZERO, 1));
	ARGUMENT_INITIALIZE(lineColor_[Type::SLICE], XMFLOAT4(ZERO, 0.5f, 1, 1));
	ARGUMENT_INITIALIZE(lineColor_[Type::TOP_SPIN], XMFLOAT4(1, ZERO, ZERO, 1));

	//���킲�Ƃ̃G�t�F�N�g�̃t�@�C���p�X��ݒ�
	ARGUMENT_INITIALIZE(hitEffectFilePath_[Type::FLAT], "Effect/FlatEffect.txt");
	ARGUMENT_INITIALIZE(hitEffectFilePath_[Type::LOB], "Effect/LobEffect.txt");
	ARGUMENT_INITIALIZE(hitEffectFilePath_[Type::SLICE], "Effect/SliceEffect.txt");
	ARGUMENT_INITIALIZE(hitEffectFilePath_[Type::TOP_SPIN], "Effect/TopSpinEffect.txt");

	//���킲�Ƃ̃G�t�F�N�g�̃t�@�C���p�X��ݒ�
	ARGUMENT_INITIALIZE(dropEffectFilePath_[Type::FLAT], "Effect/FlatDrop.txt");
	ARGUMENT_INITIALIZE(dropEffectFilePath_[Type::LOB], "Effect/LobDrop.txt");
	ARGUMENT_INITIALIZE(dropEffectFilePath_[Type::SLICE], "Effect/SliceDrop.txt");
	ARGUMENT_INITIALIZE(dropEffectFilePath_[Type::TOP_SPIN], "Effect/TopSpinDrop.txt");

	//�ł��̋������i�[����p
	HitStrength h;

	//�t���b�g
	ARGUMENT_INITIALIZE(h.strength_.x, ZERO);
	ARGUMENT_INITIALIZE(h.strength_.y, 1.0f);
	ARGUMENT_INITIALIZE(h.moveTime_, 1.0f);
	ARGUMENT_INITIALIZE(hitStrength_[Type::FLAT],h);
	
	//���u
	ARGUMENT_INITIALIZE(h.strength_.y, 4.0f);
	ARGUMENT_INITIALIZE(h.moveTime_, 1.6f);
	ARGUMENT_INITIALIZE(hitStrength_[Type::LOB],h);

	//�g�b�v�X�s��
	ARGUMENT_INITIALIZE(h.strength_.y, 1.8f);
	ARGUMENT_INITIALIZE(h.moveTime_, 0.9f);
	ARGUMENT_INITIALIZE(hitStrength_[Type::TOP_SPIN],h);

	//�X���C�X
	ARGUMENT_INITIALIZE(h.strength_.x, 1.0f);
	ARGUMENT_INITIALIZE(h.strength_.y, 1.4f);
	ARGUMENT_INITIALIZE(h.moveTime_, 1.0f);
	ARGUMENT_INITIALIZE(hitStrength_[Type::SLICE],h);

	//Maya�Ō��_��0,0,0�ɐݒ肵�����߂�
	ARGUMENT_INITIALIZE(transform_->position_, XMFLOAT3(0.643f,0.835f,0.011f));

	//�ǂ����̃R�[�g�Ɍ��������ۑ�
	if (((PlayerBase*)GetParent())->GetTennisCourtName() == TennisCourtName::Z_PLUS_COURT)
		goTennisCourtName_ = TennisCourtName::Z_MINUS_COURT;
	else
		goTennisCourtName_ = TennisCourtName::Z_PLUS_COURT;

	//�����蔻��
	box1_ = AddComponent<BoxCollider>();
	box1_->SetPos({ ZERO,ZERO,ZERO });
	box1_->SetSize({ COLLIDER_SIZE_X,COLLIDER_SIZE_Y,COLLIDER_SIZE_Z });
	box1_->SetHitFunc(&Racket::HitColliderFunc);

	//�e
	SetShadow(true);
}

//�X�V
void Racket::ChildUpdate()
{
	//���P�b�g�̒[�̃|�W�V���������߂�
	XMFLOAT3 edgePos = VectorToFloat3(ModelManager::GetBonePosition(hModel_, "Edge") - GetParent()->GetComponent<Transform>()->GetPosition() - transform_->position_);
	
	//��]�s��
	XMFLOAT3 rotate = GetComponent<Transform>()->GetWorldRotate();
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate.z));
	XMMATRIX matRotate_ = rotateZ * rotateX * rotateY;

	//�R���C�_�[�̃|�W�V�������߂ĐV�����ݒ�(���̃|�W�V�������������̂ŗ͂����ŉ�])
	colliderPos_ = VectorToFloat3(ModelManager::GetBonePosition(hModel_, "Base") - GetParent()->GetComponent<Transform>()->GetPosition() - transform_->position_);
	colliderPos_ = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos_), XMMatrixInverse(nullptr, matRotate_ *  XMMatrixTranslation(edgePos.x, ZERO, edgePos.z)) *  XMMatrixRotationY(XMConvertToRadians(BASE_ADD_ANGLE_VALUE))));
	colliderPos_ = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos_), matRotate_ * XMMatrixTranslation(edgePos.x, ZERO, edgePos.z)));
	box1_->SetPos(colliderPos_);

}

//�����蔻��
void Racket::HitColliderFunc(GameObject* pTarget)
{
	//�{�[���ɓ������ĂȂ����A�ł�������Ă��Ȃ��̂Ȃ炱�̐�̏����͂��Ȃ�
	if (pTarget->GetObjectName() != "Ball" || !((PlayerBase*)GetParent())->GetState()->IsHitMove() || goTennisCourtName_ != ((Ball*)pTarget)->GetGoTennisCourtName()) return;

	//�v���C���[���{�[���������Ă��邩�����[���Ȃ炱�̐揈�����Ȃ�
	if (((Ball*)pTarget)->GetBallStatus() == BallStatus::PLAYER_HAV_BALL && GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_RALLY) return;

	//�q�b�g�X�g�b�v���o(�������~�߂�)
	Leave();
	((Ball*)pTarget)->Leave();

	//�������Œ�l�Ȃ�
	if (ratio_ == RATIO_MIN_VALUE)
	{
		((Ball*)pTarget)->SetUsePowerEffect(true);

		//Player���G��1.0�b��ɓ����o��
		SetTimeMethod(1.0f);
		((Ball*)pTarget)->SetTimeMethod(1.0f);
	}
	else
	{
		((Ball*)pTarget)->SetUsePowerEffect(false);

		//Player���G��0.1�b��ɓ����o��
		SetTimeMethod(0.1f);
		((Ball*)pTarget)->SetTimeMethod(0.1f);
	}

	//�ۑ����Ă���
	float s = hitStrength_[type_].strength_.x;

	//�ړ�����
	float moveTime = hitStrength_[type_].moveTime_;

	//�X���C�X�Ȃ�
	if (Type::SLICE == type_)
	{
		hitStrength_[type_].strength_.x *= 1 + ((1 - ratio_) * 2.0f);
	}
	else
	{
		//�ŏI�I�Ȉړ����Ԃ����߂�
		moveTime *= ratio_;
	}

	//�o�b�N�n���h�Ȃ�X�̋������t�ɂ���
	if (stroke_ == Stroke::BACKHAND)
		hitStrength_[type_].strength_.x *= -1;


	//�T�[�u���V�[�u���̎������ړ����Ԃ𔼕��ɂ���
	if (GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_SERVE_RECEIVE)
	{
		hitStrength_[type_].strength_.y *= 0.5f;
		moveTime *= 0.5f;
	}

	//�{�[���̋O�ՐF���w��
	((Ball*)pTarget)->SetBallLineColor(lineColor_[type_]);
	((Ball*)pTarget)->SetBallDropEffectFilePath(dropEffectFilePath_[type_]);

	//�{�[�������̃R�[�g��
	((Ball*)pTarget)->Reset(hitStrength_[type_].strength_.x, hitStrength_[type_].strength_.y, moveTime, BasePointManager::GetInputBasePoint((PlayerBase*)GetParent()));

	//�G�t�F�N�g�\��
	EffectManager::Draw("HitEffect",hitEffectFilePath_[type_], ((Ball*)pTarget)->GetComponent<Transform>()->GetPosition());

	//���ɖ߂�
	ARGUMENT_INITIALIZE(hitStrength_[type_].strength_.x,s);
}

//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
void Racket::TimeMethod()
{
	Enter();
}

//�����_���ɑł��̋������擾
HitStrength Racket::GetRamdomHitStrength() {


	//�{�[���̃|�C���^��ۑ����Ă���
	Ball* pBall = ((Ball*)FindObject("Ball"));

	//�����_���Ȑ����擾
	int num = Random(ZERO, static_cast<int>(Type::MAX) - 1);

	//�����ɂ���ĕԂ��l��ύX
	switch (num)
	{

	//�t���b�g
	case static_cast<int>(Type::FLAT):

		pBall->SetBallLineColor(lineColor_[Type::FLAT]);
		return hitStrength_[Type::FLAT];

	//���u
	case static_cast<int>(Type::LOB):

		pBall->SetBallLineColor(lineColor_[Type::LOB]);
		return hitStrength_[Type::LOB];

	//�X���C�X
	case static_cast<int>(Type::SLICE):

		pBall->SetBallLineColor(lineColor_[Type::SLICE]);
		return hitStrength_[Type::SLICE];

	//�g�b�v�X�s��
	case static_cast<int>(Type::TOP_SPIN):

		pBall->SetBallLineColor(lineColor_[Type::TOP_SPIN]);
		return hitStrength_[Type::TOP_SPIN];
	default:

		pBall->SetBallLineColor(lineColor_[Type::FLAT]);
		return hitStrength_[Type::FLAT];
	}
}