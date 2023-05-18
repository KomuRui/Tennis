#include "Racket.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Engine/Collider/SphereCollider.h"
#include "../../Engine/Collider/BoxCollider.h"
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
	:NormalObject(parent, modelPath, name)
{
}

Racket::Racket(GameObject* parent)
	:NormalObject(parent, "Racket/Normal.fbx", "Racket")
{}

//������
void Racket::ChildInitialize()
{
	//���邳�ő�l�ɐݒ�
	Model::SetBrightness(hModel_, 1.0f);
	
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
	XMFLOAT3 colliderPos = VectorToFloat3(Model::GetBonePosition(hModel_, "Base") - GetParent()->GetPosition() - transform_.position_);
	colliderPos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos), XMMatrixInverse(nullptr, XMMatrixTranslation(edgePos.x, ZERO, edgePos.z)) *  XMMatrixRotationY(XMConvertToRadians(BASE_ADD_ANGLE_VALUE))));
	colliderPos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos), XMMatrixTranslation(edgePos.x, ZERO, edgePos.z)));
	SetPosCollider(colliderPos);
}

//�����蔻��
void Racket::OnCollision(GameObject* pTarget)
{
	//�{�[���ɓ������ĂȂ����A�ł�������Ă��Ȃ��̂Ȃ炱�̐�̏����͂��Ȃ�
	if (pTarget->GetObjectName() != "Ball" || !((PlayerBase*)GetParent())->pState_->IsHitMove()) return;

	//�{�[�������̃R�[�g��
	((Ball*)pTarget)->Reset(false);
}