#include "gameObject.h"
#include <assert.h>
#include "../ResourceManager/Global.h"
#include "Camera.h"

//�R���X�g���N�^�i�e�����O���Ȃ��j
GameObject::GameObject(void) :
	GameObject(nullptr, "")
{

}

//�R���X�g���N�^�i���O�Ȃ��j
GameObject::GameObject(GameObject * parent) :
	GameObject(parent, "")
{
}

//�R���X�g���N�^�i�W���j
GameObject::GameObject(GameObject * parent, const std::string& name)
	: pParent_(parent),pCollider_(nullptr),pathName_(""),



	objectName_(name)
{
	childList_.clear();
	state_ = { 0, 1, 1, 0 };

	if(parent != nullptr)
		transform_.pParent_ = &parent->transform_;

}

//�f�X�g���N�^
GameObject::~GameObject()
{
	for (auto it = colliderList_.begin(); it != colliderList_.end(); it++)
	{
		SAFE_DELETE(*it);
	}
	colliderList_.clear();
}

// �폜���邩�ǂ���
bool GameObject::IsDead()
{
	return (state_.dead != 0);
}

// �������폜����
void GameObject::KillMe()
{
	state_.dead = 1;
}

// Update������
void GameObject::Enter()
{
	state_.entered = 1;
}

// Update������
void GameObject::Leave()
{
	state_.entered = 0;
}

// Draw������
void GameObject::Visible()
{
	state_.visible = 1;
}

// Draw������
void GameObject::Invisible()
{
	state_.visible = 0;
}

// �������ς݂��ǂ���
bool GameObject::IsInitialized()
{
	return (state_.initialized != 0);
}

// �������ς݂ɂ���
void GameObject::SetInitialized()
{
	state_.initialized = 1;
}

// Update���s���Ă�����
bool GameObject::IsEntered()
{
	return (state_.entered != 0);
}

// Draw���s���Ă�����
bool GameObject::IsVisibled()
{
	return (state_.visible != 0);
}

void GameObject::SetStartUpdate()
{
	state_.startUpdate = 1;
}

bool GameObject::IsStartUpdate()
{
	return (state_.startUpdate != 1);
}

void GameObject::SetEmission(bool flag)
{
	state_.emission = flag;
}

bool GameObject::GetEmission()
{
	return (state_.emission != 0);
}

//���ԃ��\�b�h���g�p���Ă���ɐݒ�
void GameObject::SetTimeMethod(float time)
{
	//���ԃ��\�b�h���g�p���Ă���
	state_.timeMethod = 1;

	//���Ԃ�ۑ�
	time_ = (int)(time * 60.0f);
}

//���ԃ��\�b�h���g�p���Ă��邩�ǂ���
bool GameObject::GetTimeMethod()
{
	return (state_.timeMethod != 0);
}

//�������Ă��邩�ǂ����Z�b�g����
void GameObject::SetIsHit(bool flag)
{
	state_.isHit = flag;
}

//�������Ă��邩�ǂ����Q�b�g����
bool GameObject::GetIsHit()
{
	return state_.isHit;
}

//�q�I�u�W�F�N�g���X�g���擾
std::list<GameObject*>* GameObject::GetChildList()
{
	return &childList_;
}

//�e�I�u�W�F�N�g���擾
GameObject * GameObject::GetParent()
{
	return pParent_;
}

//���O�ŃI�u�W�F�N�g�������i�Ώۂ͎����̎q���ȉ��j
GameObject * GameObject::FindChildObject(const std::string & name)
{
	//�q�������Ȃ��Ȃ�I���
	if (childList_.empty())
		return nullptr;

	//�C�e���[�^
	auto it = childList_.begin();	//�擪
	auto end = childList_.end();	//����

	//�q�I�u�W�F�N�g����T��
	while (it != end) {
		//�������O�̃I�u�W�F�N�g���������炻���Ԃ�
		if ((*it)->GetObjectName() == name)
			return *it;

		//���̎q���i���j�ȍ~�ɂ��Ȃ����T��
		GameObject* obj = (*it)->FindChildObject(name);
		if (obj != nullptr)
		{
			return obj;
		}

		//���̎q��
		it++;
	}

	//������Ȃ�����
	return nullptr;
}

//�I�u�W�F�N�g�̖��O���擾
const std::string& GameObject::GetObjectName(void) const
{
	return objectName_;
}

//�q�I�u�W�F�N�g��ǉ��i���X�g�̍Ō�ցj
void GameObject::PushBackChild(GameObject * obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_back(obj);
}

//�q�I�u�W�F�N�g��ǉ��i���X�g�̐擪�ցj
void GameObject::PushFrontChild(GameObject * obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_front(obj);
}

//�q�I�u�W�F�N�g��S�č폜
void GameObject::KillAllChildren(void)
{
	//�q�������Ȃ��Ȃ�I���
	if (childList_.empty())
		return;

	//�C�e���[�^
	auto it = childList_.begin();	//�擪
	auto end = childList_.end();	//����

	//�q�I�u�W�F�N�g��1���폜
	while (it != end)
	{
		KillObjectSub(*it);
		delete *it;
		it = childList_.erase(it);
	}

	//���X�g���N���A
	childList_.clear();
}

//�R���C�_�[�̃|�W�V�����Z�b�g����
void GameObject::SetPosCollider(XMFLOAT3 position)
{
	if (pCollider_ != nullptr)
	{
		for (auto i = colliderList_.begin(); i != colliderList_.end(); i++)
		{
			if ((*i) == pCollider_)
			{
				(*i)->SetPos(position);
				break;
			}
		}
	}
}

void GameObject::SetScaleCollider(XMFLOAT3 scale)
{
	if (pCollider_ != nullptr)
	{
		for (auto i = colliderList_.begin(); i != colliderList_.end(); i++)
		{
			if ((*i) == pCollider_)
			{
				(*i)->SetSize(scale);
				break;
			}
		}
	}
}

void GameObject::SetPosScaleCollider(XMFLOAT3 scale, XMFLOAT3 position)
{
	if (pCollider_ != nullptr)
	{
		for (auto i = colliderList_.begin(); i != colliderList_.end(); i++)
		{
			if ((*i) == pCollider_)
			{
				(*i)->SetSizePos(scale,position);
				break;
			}
		}
	}
}

//�I�u�W�F�N�g�폜�i�ċA�j
void GameObject::KillObjectSub(GameObject * obj)
{
	if (!childList_.empty())
	{
		auto list = obj->GetChildList();
		auto it = list->begin();
		auto end = list->end();
		while (it != end)
		{
			KillObjectSub(*it);
			delete *it;
			it = list->erase(it);
		}
		list->clear();
	}
	obj->Release();
}

//�R���C�_�[�i�Փ˔���j��ǉ�����
void GameObject::AddCollider(Collider* collider)
{
	pCollider_ = collider;
	collider->SetGameObject(this);
	colliderList_.push_back(collider);
}

//�R���C�_�[�폜
void GameObject::KillCollider(Collider* collider)
{

	for (auto i = colliderList_.begin(); i != colliderList_.end(); i++)
	{
		if ((*i)->Getcenter().x == collider->Getcenter().x || (*i)->Getcenter().y == collider->Getcenter().y || (*i)->Getcenter().z == collider->Getcenter().z)
		{
			i = colliderList_.erase(i);
			break;
		}
	}
	
}

//�Փ˔���
void GameObject::Collision(GameObject * pTarget)
{
	//�������m�̓����蔻��͂��Ȃ�
	if (pTarget == nullptr || this == pTarget)
	{
		return;
	}

	//�������Ă��Ȃ���Ԃɂ���
	this->SetIsHit(false);

	//������pTarget�̃R���W���������g���ē����蔻��
	//1�̃I�u�W�F�N�g�������̃R���W�������������Ă�ꍇ������̂œ�d���[�v
	for (auto i = this->colliderList_.begin(); i != this->colliderList_.end(); i++)
	{
		for (auto j = pTarget->colliderList_.begin(); j != pTarget->colliderList_.end(); j++)
		{
			//���������Ȃ�
			if ((*i)->IsHit(*j))
			{
				//��������
				this->OnCollision(pTarget);

				//�������Ă����Ԃɂ���
				this->SetIsHit(true);
				pTarget->SetIsHit(true);
			}
		}
	}

	//�q�������Ȃ��Ȃ�I���
	if (pTarget->childList_.empty())
		return;

	//�q���������蔻��
	for (auto i = pTarget->childList_.begin(); i != pTarget->childList_.end(); i++)
	{
		Collision(*i);
	}
}


//�e�X�g�p�̏Փ˔���g��\��
void GameObject::CollisionDraw()
{
	Direct3D::SetShader(Direct3D::SHADER_UNLIT);

	for (auto i = this->colliderList_.begin(); i != this->colliderList_.end(); i++)
	{
		(*i)->Draw(GetWorldPosition(),GetWorldRotate());
	}

	Direct3D::SetShader(Direct3D::SHADER_3D);
}

//RootJob���擾
GameObject * GameObject::GetRootJob()
{
	if (GetParent() == nullptr)
	{
		return this;
	}
	else return GetParent()->GetRootJob();
}

//�R���C�_�[�̔��a�擾
float GameObject::GetColliderRadius()
{
	if (pCollider_ != nullptr)
	{
		for (auto i = colliderList_.begin(); i != colliderList_.end(); i++)
		{
			if ((*i) == pCollider_)
			{
				return (*i)->GetRadius();
			}
		}
	}

	return 0.0f;
}


void GameObject::UpdateSub()
{
	//null�Ȃ炱�̐揈�����Ȃ�
	if (this == nullptr) return;

	//���ԃ��\�b�h���g�p���Ă���Ȃ�
	if (this->state_.timeMethod)
	{
		//�^�C�����Z
		timeCount_++;

		//�w�肳�ꂽ���Ԃ��^�C�����傫���̂Ȃ�
		if (time_ < timeCount_)
		{
			//�g�����e�ϐ�������
			ZERO_INITIALIZE(this->state_.timeMethod);
			ZERO_INITIALIZE(time_);
			ZERO_INITIALIZE(timeCount_);

			//���\�b�h�Ăяo��
			TimeMethod();
		}
	}

	//Update��������Ȃ�
	if(this->state_.entered && !IsStartUpdate())
		Update();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->UpdateSub();
	}

	for (auto it = childList_.begin(); it != childList_.end();)
	{
		if ((*it)->IsDead() == true)
		{
			(*it)->ReleaseSub();
			SAFE_DELETE(*it);
			it = childList_.erase(it);
		}
		else
		{
			//�����蔻��
			(*it)->Collision(GetParent());
			it++;
		}
	}

	//�����N�Ƃ��������Ă��Ȃ��̂Ȃ�
	if (!(this->GetIsHit()) && pCollider_ != nullptr)
	{
		//�������Ă��Ȃ��֐����Ă�
		OutCollision();
	}
}

void GameObject::StartUpdateSub()
{
	//null�Ȃ炱�̐揈�����Ȃ�
	if (this == nullptr) return;

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->StartUpdateSub();
	}

	if (IsStartUpdate())
	{
		this->StartUpdate();
		SetStartUpdate();
	}
}

void GameObject::DrawSub()
{
	//null�Ȃ炱�̐揈�����Ȃ�
	if (this == nullptr) return;

	//�V�F�[�_��SHADER_3D�ɃZ�b�g���Ă���
	Direct3D::SetShader(Direct3D::SHADER_3D);

	//�����`�悪������Ă���̂Ȃ�
	if (this->IsVisibled())
	{
		//�`��
		Draw();
	}

	//�����[�X���͍폜
#ifdef _DEBUG
		//�R���W�����̕`��
	if (Direct3D::isDrawCollision_)
	{
		CollisionDraw();
	}
#endif
	
	//���̎q�I�u�W�F�N�g�̕`�揈��

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->DrawSub();
	}
}

void GameObject::EmissionDraw()
{
	if(this->GetEmission())
		Draw();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->EmissionDraw();
	}
}

void GameObject::ReleaseSub()
{
	for (auto it = colliderList_.begin(); it != colliderList_.end(); it++)
	{
		SAFE_DELETE(*it);
	}

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->ReleaseSub();
		SAFE_DELETE(*it);
	}

	Release();
}

//�����ł������target�̕�������
void GameObject::LookObject(XMFLOAT3 target, XMVECTOR up)
{
	target.y += 2;
	transform_.mmRotate_ = XMMatrixInverse(nullptr, XMMatrixLookAtLH(XMVectorSet(ZERO,ZERO,ZERO,ZERO), XMLoadFloat3(&target) - XMLoadFloat3(&transform_.position_), up));
}

//���[���h�s��̎擾�i�e�̉e�����󂯂��ŏI�I�ȍs��j
XMMATRIX GameObject::GetWorldMatrix(void)
{
	return transform_.GetWorldMatrix();
}


