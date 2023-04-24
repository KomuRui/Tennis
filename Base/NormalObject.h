#pragma once
#include "../Engine/GameObject/GameObject.h"

/// <summary>
/// ����3D�I�u�W�F�N�g��\��������N���X
/// </summary>
class NormalObject : public GameObject
{
protected:

	///////////////�K�v�ȏ��///////////////////

	int hModel_;                     //���f���ԍ�
	std::string modelNamePath_;      //�t�@�C���l�[���p�X

public:

	//�R���X�g���N�^
	NormalObject(GameObject* parent, std::string modelPath, std::string name);

	//�f�X�g���N�^
	virtual ~NormalObject() {};
	
	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	/// <summary>
	/// �p����p��Update
	/// </summary>
	virtual void ChildUpdate() {};

	/// <summary>
	/// �p����p�̏�����
	/// </summary>
	virtual void ChildInitialize() {};

	/// <summary>
	/// �p����p�̕`��
	/// </summary>
	virtual void ChildDraw() {};

	/// <summary>
	/// �p����p�̍X�V�̑O�Ɉ�x�����Ă΂��֐�
	/// </summary>
	virtual void ChildStartUpdate() {};

	/// <summary>
	/// �p����p�̊J��
	/// </summary>
	virtual void ChildRelease() {};

	/// <summary>
	/// �p����p�̃R���C�_�[�ɓ����������ɌĂ΂��֐�
	/// </summary>
	/// <param name="pTarget">���������I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnCollision(GameObject* pTarget) override {};

	/// <summary>
	/// �p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	/// </summary>
	virtual void TimeMethod() override {};


	////////////////////////////�Q�b�^�[�E�Z�b�^�[////////////////////////////////

	int GetModelNum() { return hModel_; }
};

