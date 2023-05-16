#include "Racket.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Engine/Collider/SphereCollider.h"


//�萔
namespace
{		
	////////////////�R���C�_�[///////////////////

	static const float    COLLIDER_SIZE = 0.3f;               //�R���C�_�[�̃T�C�Y
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
	
	XMFLOAT3 a = Model::GetBonePosition(hModel_, "Base");
	a.z += 1.1f;
	//�����蔻��
	SphereCollider* collision = new SphereCollider(a, COLLIDER_SIZE);
	AddCollider(collision);

}

//�X�V
void Racket::ChildUpdate()
{
}
