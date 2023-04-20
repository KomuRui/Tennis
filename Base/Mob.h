#pragma once
#include "../Engine/GameObject/GameObject.h"
#include "../Engine/Collider/BoxCollider.h"
#include "../Engine/Collider/SphereCollider.h"
#include "../Engine/ResourceManager/Global.h"
#include "../Stage.h"
#include "../Engine/ResourceManager/Model.h"

/// <summary>
/// �n�`�ɍ��킹�ĉ�]���������I�u�W�F�N�g�̊��N���X(Mob,Enemy,Warp,Coin�Ȃ�...)
/// </summary>
class Mob : public GameObject
{
protected:

	///////////////�L�����̕K�v�ȏ��///////////////////
	 
	XMMATRIX totalMx_;			     //�L�����̉����̂��܂܂ł̃}�g���N�X�̑����}�g���N�X

	XMVECTOR up_;                    //�L�����̏�x�N�g��
	XMVECTOR horizontal_;            //�L�����̉�
	XMVECTOR down_;		   	         //�L�����̉��x�N�g��
	XMVECTOR vNormal_;               //�L�����̉��̃X�e�[�W�̖@��

	float angle_;                    //�L�����̏�̎��̊p�x

	int hModel_;                     //���f���ԍ�
	std::string modelNamePath_;      //�t�@�C���l�[���p�X

	///////////////�����蔻��///////////////////

	Stage* pstage_;                 //�X�e�[�W�N���X�̃|�C���^
	int      hGroundModel_;         //�X�e�[�W�̃��f���ԍ�������ϐ�

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Mob(GameObject* parent,std::string modelPath, std::string name);

	//������
	void Initialize() override;

	//�X�V
	virtual void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	/// <summary>
	/// �X�e�[�W�ɍ��킹�ĉ�]
	/// </summary>
	virtual void RotationInStage();

	/// <summary>
	/// ���g�̖@�����Z�b�g
	/// </summary>
	/// <param name="nor">�Z�b�g�������@��</param>
	void SetNormal(const XMVECTOR& nor) { vNormal_ = nor; }

	/// <summary>
	/// �L�����̏㎲���Z�b�g
	/// </summary>
	/// <param name="angle">�Z�b�g�������L�����̏㎲</param>
	void SetAngle(const float& angle) { angle_ = angle; }

	/// <summary>
	/// Player��^�t�̏�Ԃɐݒ�(�܂��������΂ɐݒ肷��ƊO�ς��O�ɂȂ��Ă��܂��̂ŏ������炷)
	/// </summary>
	void SetInverseNormalAndDown() { vNormal_ += {0, 0.1f, 0, 0}; vNormal_ = -vNormal_; down_ = -vNormal_; }

	/// <summary>
	/// ���f���p�X�l�[�����擾
	/// </summary>
	/// <returns>���f���p�X�l�[��</returns>
	std::string GetModelPathName() { return modelNamePath_; }

	/// <summary>
	/// �L�����̉��̃X�e�[�W�̖@�����Q�b�g
	/// </summary>
	/// <returns>�X�e�[�W�̖@��</returns>
	XMVECTOR GetNormal() { return vNormal_; }

	/// <summary>
	/// �L�����̏㎲�̊p�x���Q�b�g
	/// </summary>
	/// <returns>�L�����̏㎲�̊p�x</returns>
	float GetAngle() { return angle_; }

	/// <summary>
	/// �L�����̏㎲�Q�b�g
	/// </summary>
	/// <returns>�L�����̏㎲</returns>
	XMVECTOR GetUp() { return up_; }

	/// <summary>
	/// Player�̉��x�N�g���Q�b�g
	/// </summary>
	/// <returns>Player�̉��x�N�g��</returns>
	XMVECTOR GetDown() { return down_; }

	/// <summary>
	/// Player�̉�]�}�g���N�X�Q�b�g
	/// </summary>
	/// <returns>Player�̉�]�}�g���N�X</returns>
	XMMATRIX GetmmRotate() { return transform_.mmRotate_; }

	/// <summary>
	/// ���f���ԍ����Q�b�g
	/// </summary>
	/// <returns>Player�̃��f���ԍ�</returns>
	int GethModel() { return hModel_; }

	/// <summary>
	/// �A�j���[�V�������邩�ǂ����Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ�A�j���[�V��������,false�Ȃ�A�j���[�V�������Ȃ�</param>
	void SetAnimFlag(const bool& flag) { Model::SetAnimFlag(hModel_, flag); }

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
};

