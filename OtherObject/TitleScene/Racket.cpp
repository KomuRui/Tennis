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
	:NormalObject(parent, modelPath, name), type_(Type::FLAT), colliderPos_(ZERO, ZERO, ZERO)
{
}

Racket::Racket(GameObject* parent)
	:NormalObject(parent, "Racket/Normal.fbx", "Racket"), type_(Type::FLAT), colliderPos_(ZERO, ZERO, ZERO)
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

//�����蔻��
void Racket::OnCollision(GameObject* pTarget)
{
	//�{�[���ɓ������ĂȂ����A�ł�������Ă��Ȃ��̂Ȃ炱�̐�̏����͂��Ȃ�
	if (pTarget->GetObjectName() != "Ball" || !((PlayerBase*)GetParent())->pState_->IsHitMove()) return;

	//�q�b�g�X�g�b�v���o(�������~�߂�)
	Leave();
	pTarget->Leave();

	//Player���G��0.1�b��ɓ����o��
	SetTimeMethod(0.1f);
	pTarget->SetTimeMethod(0.1f);

	//�{�[���̋O�ՐF���w��
	((Ball*)pTarget)->SetBallLineColor(lineColor_[type_]);

	//�{�[�������̃R�[�g��
	((Ball*)pTarget)->Reset(false);

	//�{�[���̃|�W�V�������C��
	XMFLOAT3 pos = VectorToFloat3(colliderPos_ + GetParent()->GetPosition());
	ARGUMENT_INITIALIZE(pos.y, COLLIDER_SIZE_Y / 2.0f);
	((Ball*)pTarget)->SetPosition(pos);

	//�G�t�F�N�g�\��
	EffectManager::Draw("Effect/TopSpinEffect.txt", pos);
}

//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
void Racket::TimeMethod()
{
	Enter();
}