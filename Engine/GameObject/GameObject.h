#pragma once
#include <DirectXMath.h>
#include <list>
#include <string>
#include <assert.h>
#include "../ResourceManager/Global.h"
#include "../DirectX/Input.h"
#include "../Component/Component.h"

using namespace DirectX;

//-----------------------------------------------------------
//�S�ẴQ�[���I�u�W�F�N�g�i�V�[�����܂߂āj���p������C���^�[�t�F�[�X
// �Q�[���I�u�W�F�N�g�́A�e�q�\���ɂȂ��Ă��āA
// �}�g���N�X�̉e�����󂯂邱�ƂɂȂ�
//-----------------------------------------------------------
class GameObject
{
protected:

	//�I�u�W�F�N�g�̖��O
	std::string				objectName_;

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
	virtual void Initialize(void) {};
	virtual void Update(void) {};
	virtual void StartUpdate(void) {};
	virtual void Draw() {};
	virtual void Release(void){};

	//�����̊Y���֐���ǂ񂾌�A�q���̊֐����Ă�
	void UpdateSub();
	void StartUpdateSub();
	void DrawSub();
	void ReleaseSub();

	//��ڂ̃E�B���h�E�p
	virtual void TwoWindowDraw() {};
	void TwoWindowDrawSub();

	//�����E�������ȃI�u�W�F�N�g�p
	virtual void TransparentDraw() {};
	void TransparentDrawSub();

	//Emission��K�p���������I�u�W�F�N�g�̕`��
	void EmissionDraw();

	//�e��`�悷��Ƃ��ɌĂ�
	void ShadowDraw();

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
	void SetShadow(bool flag);      // �e���Z�b�g����
	bool GetShadow();				// �e��K�p���邩�ǂ���
	void SetTimeMethod(float time); // ���ԃ��\�b�h���g�p���Ă���ɕύX
	bool GetTimeMethod();		    // ���ԃ��\�b�h���g�p���Ă��邩�ǂ���

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

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	virtual void TimeMethod() {};

    //�����ł������target�̕�������
	void LookObject(XMFLOAT3 target,XMVECTOR up);

	//RootJob���擾
	GameObject* GetRootJob();

	//���g��e�̃��X�g�̍Ō�Ƀv�b�V������
	void MyObjectParentListEndPush();

	//�I�u�W�F�N�g�������Ă���R���|�[�l���g���擾
	template<class T>
	T* GetComponent()
	{
		for (auto com : ComponentList_) {
			T* buff = dynamic_cast<T*>(com);
			if (buff != nullptr)
				return buff;
		}
		return nullptr;
	}

	//�I�u�W�F�N�g�������Ă��铯���R���|�[�l���g�𕡐�List�Ŏ擾
	template<class T>
	list<T*> GetComponentList()
	{
		list<T*> l;
		for (auto com : ComponentList_) {
			T* buff = dynamic_cast<T*>(com);
			if (buff != nullptr)
				l.push_back(buff);
		}
		return l;
	}

	//�I�u�W�F�N�g�������Ă���R���|�[�l���g���폜
	template<class T>
	T* DeleteComponent()
	{
		for (auto com : ComponentList_) {
			T* buff = dynamic_cast<T*>(com);

			//������΍폜
			if (buff != nullptr)
			{
				ComponentList_.remove(buff);
				delete buff;
			}
		}
		return nullptr;
	}

	//�R���|�[�l���g�ǉ�
	template<class T>
	T* AddComponent()
	{
		T* buff = new T();
		buff->parent = this;
		ComponentList_.push_back(buff);
		buff->Start();
		return buff;
	}

	//�e�A�N�Z�X�֐�
	std::string GetPathName() { return pathName_; }
	
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
		unsigned shadow : 1;        //�e�\��
		unsigned timeMethod : 1;    //�^�C�����\�b�h���g�p���Ă��邩�ǂ���
	};
	OBJECT_STATE state_;

	//���ԃ��\�b�h���Ăяo�����߂ɕK�v�Ȏ��ԕϐ�����
	int time_;
	int timeCount_;

	//�e�I�u�W�F�N�g
	GameObject* pParent_;

	//�q�I�u�W�F�N�g���X�g
	std::list<GameObject*> childList_;

	//�R���|�[�l���g���X�g
	std::list<Component*> ComponentList_;
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

