#include "Racket.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Engine/Collider/SphereCollider.h"
#include "../../Engine/Collider/BoxCollider.h"


//�萔
namespace
{		
	////////////////�R���C�_�[///////////////////

	static const int      BASE_ADD_ANGLE_VALUE = -110;   //�x�[�X�ɉ��Z����p�x�̒l
	static const int      EDGE_ADD_ANGLE_VALUE = -180;   //�[�ɉ��Z����p�x�̒l
	static const float    COLLIDER_SIZE_X = 1.0f;        //�R���C�_�[�̃T�C�Y
	static const float    COLLIDER_SIZE_Y = 1.5f;        //�R���C�_�[�̃T�C�Y
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
	

	ARGUMENT_INITIALIZE(transform_.position_, XMFLOAT3(0.643,0.835,0.011));
		
	//�����蔻��
	BoxCollider * collision = new BoxCollider({ ZERO,ZERO,ZERO }, { COLLIDER_SIZE_X,COLLIDER_SIZE_Y,COLLIDER_SIZE_Z });
	AddCollider(collision);
}

//�X�V
void Racket::ChildUpdate()
{
	//���P�b�g�̒[�̃|�W�V���������߂�(���̃|�W�V�������������̂ŗ͂����ŉ�])
	XMFLOAT3 edgePos = VectorToFloat3(Model::GetBonePosition(hModel_, "Edge") - GetParent()->GetPosition());
	edgePos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&edgePos), XMMatrixRotationY(XMConvertToRadians(1))));

	//�R���C�_�[�̃|�W�V�������߂ĐV�����ݒ�(���̃|�W�V�������������̂ŗ͂����ŉ�])
	XMFLOAT3 colliderPos = VectorToFloat3(Model::GetBonePosition(hModel_, "Base") - GetParent()->GetPosition());
	colliderPos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos), XMMatrixRotationY(XMConvertToRadians(BASE_ADD_ANGLE_VALUE))));
	SetPosCollider(colliderPos);
}
