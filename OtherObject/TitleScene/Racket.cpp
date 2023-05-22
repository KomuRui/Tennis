#include "Racket.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Engine/Collider/SphereCollider.h"
#include "../../Engine/Collider/BoxCollider.h"
#include "../../Manager/EffectManager/EffectManager.h"
#include "../../Player/PlayerBase.h"
#include "Ball.h"

//�萔
namespace
{		
	static const int RACKET_START_ROTATION_ANGLE = -185; //���P�b�g�̊J�n�p�x

	////////////////�R���C�_�[///////////////////

	static const int      BASE_ADD_ANGLE_VALUE = -80;    //�x�[�X�ɉ��Z����p�x�̒l
	static const float    COLLIDER_SIZE_X = 1.5f;        //�R���C�_�[�̃T�C�Y
	static const float    COLLIDER_SIZE_Y = 2.0f;        //�R���C�_�[�̃T�C�Y
	static const float    COLLIDER_SIZE_Z = 1.0f;        //�R���C�_�[�̃T�C�Y
}

//�R���X�g���N�^
Racket::Racket(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), type_(Type::FLAT), stroke_(Stroke::FOREHAND), colliderPos_(ZERO, ZERO, ZERO)
{
}

Racket::Racket(GameObject* parent)
	:NormalObject(parent, "Racket/Normal.fbx", "Racket"), type_(Type::FLAT), stroke_(Stroke::FOREHAND), colliderPos_(ZERO, ZERO, ZERO)
{}

//������
void Racket::ChildInitialize()
{
	//���邳�ő�l�ɐݒ�
	Model::SetBrightness(hModel_, 1.0f);
	
	//���킲�Ƃ̃{�[���̐F��ݒ�
	ARGUMENT_INITIALIZE(lineColor_[Type::FLAT], XMFLOAT4(1, ZERO, 1, 1));
	ARGUMENT_INITIALIZE(lineColor_[Type::LOB], XMFLOAT4(1, 1, ZERO, 1));
	ARGUMENT_INITIALIZE(lineColor_[Type::SLICE], XMFLOAT4(ZERO, 1, 1, 1));
	ARGUMENT_INITIALIZE(lineColor_[Type::TOP_SPIN], XMFLOAT4(1, ZERO, ZERO, 1));

	//���킲�Ƃ̃G�t�F�N�g�̃t�@�C���p�X��ݒ�
	ARGUMENT_INITIALIZE(effectFilePath_[Type::FLAT], "Effect/FlatEffect.txt");
	ARGUMENT_INITIALIZE(effectFilePath_[Type::LOB], "Effect/LobEffect.txt");
	ARGUMENT_INITIALIZE(effectFilePath_[Type::SLICE], "Effect/SliceEffect.txt");
	ARGUMENT_INITIALIZE(effectFilePath_[Type::TOP_SPIN], "Effect/TopSpinEffect.txt");

	//���킲�Ƃ̃G�t�F�N�g�̃t�@�C���p�X��ݒ�
	HitStrength h;

	//�t���b�g
	ARGUMENT_INITIALIZE(h.strength_.x, ZERO);
	ARGUMENT_INITIALIZE(h.strength_.y, 1.0f);
	ARGUMENT_INITIALIZE(h.moveTime_, 0.7f);
	ARGUMENT_INITIALIZE(hitStrength_[Type::FLAT],h);
	
	//���u
	ARGUMENT_INITIALIZE(h.strength_.y, 4.0f);
	ARGUMENT_INITIALIZE(h.moveTime_, 1.4f);
	ARGUMENT_INITIALIZE(hitStrength_[Type::LOB],h);

	//�g�b�v�X�s��
	ARGUMENT_INITIALIZE(h.strength_.y, 1.8f);
	ARGUMENT_INITIALIZE(h.moveTime_, 0.6f);
	ARGUMENT_INITIALIZE(hitStrength_[Type::TOP_SPIN],h);

	//�X���C�X
	ARGUMENT_INITIALIZE(h.strength_.x, 1.0f);
	ARGUMENT_INITIALIZE(h.strength_.y, 1.4f);
	ARGUMENT_INITIALIZE(h.moveTime_, 0.7f);
	ARGUMENT_INITIALIZE(hitStrength_[Type::SLICE],h);

	//Maya�Ō��_��0,0,0�ɐݒ肵�����߂�
	ARGUMENT_INITIALIZE(transform_.position_, XMFLOAT3(0.643f,0.835f,0.011f));
		
	//�J�n�p�x��ݒ�
	SetRotateY(RACKET_START_ROTATION_ANGLE);

	//�����蔻��
	BoxCollider * collision = new BoxCollider({ ZERO,ZERO,ZERO }, { COLLIDER_SIZE_X,COLLIDER_SIZE_Y,COLLIDER_SIZE_Z });
	AddCollider(collision);
}

//�X�V
void Racket::ChildUpdate()
{
	//���P�b�g�̒[�̃|�W�V���������߂�
	XMFLOAT3 edgePos = VectorToFloat3(Model::GetBonePosition(hModel_, "Edge") - GetParent()->GetPosition() - transform_.position_);
	
	//�R���C�_�[�̃|�W�V�������߂ĐV�����ݒ�(���̃|�W�V�������������̂ŗ͂����ŉ�])
	colliderPos_ = VectorToFloat3(Model::GetBonePosition(hModel_, "Base") - GetParent()->GetPosition() - transform_.position_);
	colliderPos_ = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos_), XMMatrixInverse(nullptr, XMMatrixTranslation(edgePos.x, ZERO, edgePos.z)) *  XMMatrixRotationY(XMConvertToRadians(BASE_ADD_ANGLE_VALUE))));
	colliderPos_ = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos_), XMMatrixTranslation(edgePos.x, ZERO, edgePos.z)));
	SetPosCollider(colliderPos_);
}

//���͂ɑ΂����_�̃|�C���g�̖��O���擾
string Racket::GetInputBasePoint()
{
	//�ŏI�I�ɕԂ�������
	string name = "";

	//L�X�e�B�b�N�̌X�����擾
	XMFLOAT3 stickL = Input::GetPadStickL();

	if (stickL.y > 0.1f)
		name += "Back_";
	else if (stickL.y < -0.1f)
		name += "Front_";
	else
		name += "Center_";

	if (stickL.x > 0.1f)
		name += "L";
	else if (stickL.x < -0.1f)
		name += "R";
	else
		name += "C";

	return name;
}

//�����蔻��
void Racket::OnCollision(GameObject* pTarget)
{
	//�{�[���ɓ������ĂȂ����A�ł�������Ă��Ȃ��̂Ȃ炱�̐�̏����͂��Ȃ�
	if (pTarget->GetObjectName() != "Ball" || !((PlayerBase*)GetParent())->pState_->IsHitMove() || ((Ball*)pTarget)->isGoToPlayerBasePoint()) return;

	//�q�b�g�X�g�b�v���o(�������~�߂�)
	Leave();
	pTarget->Leave();

	//Player���G��0.1�b��ɓ����o��
	SetTimeMethod(0.1f);
	pTarget->SetTimeMethod(0.1f);

	//�ۑ����Ă���
	float s = hitStrength_[type_].strength_.x;

	//�o�b�N�n���h�Ȃ�X�̋������t�ɂ���
	if (stroke_ == Stroke::BACKHAND)
		hitStrength_[type_].strength_.x *= -1;

	//�{�[���̋O�ՐF���w��
	((Ball*)pTarget)->SetBallLineColor(lineColor_[type_]);

	//�{�[�������̃R�[�g��
	((Ball*)pTarget)->Reset(hitStrength_[type_].strength_.x, hitStrength_[type_].strength_.y, hitStrength_[type_].moveTime_,false, GetInputBasePoint());

	//�G�t�F�N�g�\��
	EffectManager::Draw(effectFilePath_[type_], ((Ball*)pTarget)->GetPosition());

	//���ɖ߂�
	ARGUMENT_INITIALIZE(hitStrength_[type_].strength_.x,s);
}

//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
void Racket::TimeMethod()
{
	Enter();
}