#pragma once
#include <DirectXMath.h>
#include <list>
#include <string>
#include <assert.h>
#include "../Collider/SphereCollider.h"
#include "../Collider/BoxCollider.h"
#include "Transform.h"
#include "../ResourceManager/Global.h"
#include "../DirectX/Input.h"

using namespace DirectX;

//-----------------------------------------------------------
//�S�ẴQ�[���I�u�W�F�N�g�i�V�[�����܂߂āj���p������C���^�[�t�F�[�X
// �Q�[���I�u�W�F�N�g�́A�e�q�\���ɂȂ��Ă��āA
// �}�g���N�X�̉e�����󂯂邱�ƂɂȂ�
//-----------------------------------------------------------
class GameObject
{
protected:
	
	//�ʒu������Ȃǂ��Ǘ�����I�u�W�F�N�g
	Transform				transform_;

	//�I�u�W�F�N�g�̖��O
	std::string				objectName_;

	//�����̃R���C�_�[
	Collider*               pCollider_;

	//�Փ˔��胊�X�g
	std::list<Collider*>	colliderList_;	

	//���f����摜�̃p�X����ۑ����Ă���
	std::string					pathName_;

public:
	//�R���X�g���N�^
	GameObject();
	GameObject(GameObject* parent);
	GameObject(GameObject* parent, const std::string& name);

	//�f�X�g���N�^
	virtual ~GameObject();

	//�e�I�u�W�F�N�g�ŕK�����֐�
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void StartUpdate(void) = 0;
	virtual void Draw() = 0;
	virtual void Release(void) = 0;

	//�����̊Y���֐���ǂ񂾌�A�q���̊֐����Ă�
	void UpdateSub();
	void StartUpdateSub();
	void DrawSub();
	void ReleaseSub();

	//Emission��K�p���������I�u�W�F�N�g�̕`��
	void EmissionDraw();

	//���[���h�s��̎擾�i�e�̉e�����󂯂��ŏI�I�ȍs��j
	//�ߒl�F���[���h�s��
	XMMATRIX GetWorldMatrix();



	//�e�t���O�̐���
	bool IsDead();					// �폜���邩�ǂ���
	void KillMe();					// �������폜����
	void Enter();					// Update������
	void Leave();					// Update������
	void Visible();					// Draw������
	void Invisible();				// Draw������
	bool IsInitialized();			// �������ς݂��ǂ���
	void SetInitialized();			// �������ς݂ɂ���
	bool IsEntered();				// Update���s���Ă�����
	bool IsVisibled();				// Draw���s���Ă�����
	void SetStartUpdate();			// StartUpdate�ς݂ɂ���
	bool IsStartUpdate();			// StartUpdate���s���Ă�����
	void SetEmission(bool flag);    // Emission���Z�b�g����
	bool GetEmission();				// Emission�Q�b�g
	void SetTimeMethod(float time); // ���ԃ��\�b�h���g�p���Ă���ɕύX
	bool GetTimeMethod();		    // ���ԃ��\�b�h���g�p���Ă��邩�ǂ���
	void SetIsHit(bool flag);       // �������Ă��邩�ǂ����Z�b�g����
	bool GetIsHit();                // �������Ă��邩�ǂ����Q�b�g����

	//�q�I�u�W�F�N�g���X�g���擾
	//�ߒl�F�q�I�u�W�F�N�g���X�g
	std::list<GameObject*>* GetChildList();

	//�e�I�u�W�F�N�g���擾
	//�ߒl�F�e�I�u�W�F�N�g�̃A�h���X
	GameObject* GetParent();

	//���O�ŃI�u�W�F�N�g�������i�Ώۂ͎����̎q���ȉ��j
	//�����Fname	�������閼�O
	//�ߒl�F�������I�u�W�F�N�g�̃A�h���X�i������Ȃ����nullptr�j
	GameObject* FindChildObject(const std::string& name);

	//���O�ŃI�u�W�F�N�g�������i�Ώۂ͑S�́j
	//�����F�������閼�O
	//�ߒl�F�������I�u�W�F�N�g�̃A�h���X
	GameObject* FindObject(const std::string& name) { return GetRootJob()->FindChildObject(name); }

	//�I�u�W�F�N�g�̖��O���擾
	//�ߒl�F���O
	const std::string& GetObjectName(void) const;

	/// <summary>
	/// �I�u�W�F�N�g�̖��O�Z�b�g
	/// </summary>
	void SetObjectName(std::string s) { objectName_ = s; }

	//�q�I�u�W�F�N�g��ǉ��i���X�g�̍Ō�ցj
	//�����F�ǉ�����I�u�W�F�N�g
	void PushBackChild(GameObject* obj);

	//�q�I�u�W�F�N�g��ǉ��i���X�g�̐擪�ցj
	//�����Fobj �ǉ�����I�u�W�F�N�g
	void PushFrontChild(GameObject* obj);

	//�q�I�u�W�F�N�g��S�č폜
	void KillAllChildren();

	//�R���C�_�[�i�Փ˔���j��ǉ�����
	void AddCollider(Collider * collider);

	//�R���C�_�[�폜
	void KillCollider(Collider* collider);

	//�����ƏՓ˂����ꍇ�ɌĂ΂��i�I�[�o�[���C�h�p�j
	//�����FpTarget	�Փ˂�������
	virtual void OnCollision(GameObject* pTarget) {};

	//�N�Ƃ��Փ˂��Ă��Ȃ��ꍇ�ɌĂ΂��i�I�[�o�[���C�h�p�j
	virtual void OutCollision() {};

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	virtual void TimeMethod() {};

	//�Փ˔���
	//�����FpTarget	�Փ˂��Ă邩���ׂ鑊��
	void Collision(GameObject* pTarget);

	//�e�X�g�p�̏Փ˔���g��\��
	void CollisionDraw();

    //�����ł������target�̕�������
	void LookObject(XMFLOAT3 target,XMVECTOR up);

	//RootJob���擾
	GameObject* GetRootJob();

	//�e�A�N�Z�X�֐�
	XMFLOAT3 GetPosition() { return transform_.position_; }
	XMFLOAT3 GetRotate() { return transform_.rotate_; }
	XMFLOAT3 GetScale() { return transform_.scale_; }
	XMFLOAT3 GetWorldPosition() { return Float3Add(GetParent()->transform_.position_ , transform_.position_); }
	XMFLOAT3 GetWorldRotate() { return Float3Add(GetParent()->transform_.rotate_, transform_.rotate_); }
	XMFLOAT3 GetWorldScale() { return Float3Add(GetParent()->transform_.scale_, transform_.scale_); }
	Transform* GetTransform() { return &transform_; }
	std::string GetPathName() { return pathName_; }
	float    GetColliderRadius();
	void SetPosition(XMFLOAT3 position) { transform_.position_ = position; }
	void SetPosition(float x, float y, float z) { SetPosition(XMFLOAT3( x, y, z )); }
	void SetPositionX(float x) { SetPosition(x, transform_.position_.y, transform_.position_.z); }
	void SetPositionY(float y) { SetPosition(transform_.position_.x, y, transform_.position_.z); }
	void SetPositionZ(float z) { SetPosition(transform_.position_.x, transform_.position_.y, z); }
	void SetRotate(XMFLOAT3 rotate) { transform_.rotate_ = rotate; }
	void SetRotate(float x, float y, float z) { SetRotate(XMFLOAT3( x, y, z )); }
	void SetRotateX(float x) { SetRotate(x, transform_.rotate_.y, transform_.rotate_.z); }
	void SetRotateY(float y) { SetRotate(transform_.rotate_.x, y, transform_.rotate_.z); }
	void SetRotateZ(float z) { SetRotate(transform_.rotate_.x, transform_.rotate_.y, z); }
	void SetScale(XMFLOAT3 scale) { transform_.scale_ = scale; }
	void SetScale(float x, float y, float z) { SetScale(XMFLOAT3(x, y, z)); }
	void SetPosCollider(XMFLOAT3 position);
	void SetScaleCollider(XMFLOAT3 scale);
	void SetPosScaleCollider(XMFLOAT3 scale, XMFLOAT3 position);
	void SetTransform(Transform t) { transform_ = t; }
	
private:

	//�I�u�W�F�N�g�폜�i�ċA�j
	//�����Fobj�@�폜����I�u�W�F�N�g
	void KillObjectSub(GameObject* obj);


	//�t���O
	struct OBJECT_STATE
	{
		unsigned initialized : 1;	//�������ς݂�
		unsigned entered : 1;		//�X�V���邩
		unsigned visible : 1;		//�`�悷�邩
		unsigned dead : 1;			//�폜���邩
		unsigned startUpdate : 1;   //�ŏ��̍X�V���Ă��邩
		unsigned emission : 1;      //Emission�\��
		unsigned timeMethod : 1;    //�^�C�����\�b�h���g�p���Ă��邩�ǂ���
		unsigned isHit : 1;         //�������Ă��邩�ǂ���
	};
	OBJECT_STATE state_;

	//���ԃ��\�b�h���Ăяo�����߂ɕK�v�Ȏ��ԕϐ�����
	int time_;
	int timeCount_;

	//�e�I�u�W�F�N�g
	GameObject* pParent_;

	//�q�I�u�W�F�N�g���X�g
	std::list<GameObject*> childList_;
};


//�I�u�W�F�N�g���쐬����e���v���[�g(�Ŕp)
template <class T>
T* Instantiate(GameObject* pParent, std::string fileName, std::string Name)
{
	T* pNewObject = new T(pParent,fileName, Name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

//�I�u�W�F�N�g���쐬����e���v���[�g
template <class T>
T* Instantiate(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

//�I�u�W�F�N�g���쐬����e���v���[�g
template <class T>
T* InstantiateFront(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushFrontChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

//�I�u�W�F�N�g���쐬����e���v���[�g
template <class T>
T* InstantiateParentFront(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->GetParent()->PushFrontChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

//�I�u�W�F�N�g���쐬����e���v���[�g
template <class T>
T* InstantiateParentPush(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->GetParent()->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

