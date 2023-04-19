#pragma once
#include "Engine/GameObject/GameObject.h"
#include <vector>

//�O���錾
class CreateStage;

/// <summary>
/// �e�X�e�[�W�N���X�̂��ƂƂȂ�N���X
/// </summary>
class Stage : public GameObject
{
protected:

	/////////////////////////Stage�ɕK�v�ȏ��/////////////////////////////////
	
	//���f���̎��
	enum StageCategory
	{
		Base = 0,      //�X�e�[�W�̃��f��
		Space,		   //�w�i�̉F�����f��
		PolyModel,     //���̂ɕ��̂��悹�邽�߂ɋ^�����f��
		MAX
	};

	//���f���ԍ�
	int hModel_[MAX];

	//�X�e�[�W���쐬����p�̕ϐ�
	CreateStage* pCreateStage_;

	//�w�i���f���p�̃g�����X�t�H�[��
	Transform tSpace_;

	//��p
	int fieldAngle_;

	//���C�g�̋���
	int lightIntensity_;

	/////////////////////////���̃N���X�ŕK�v�ȏ��/////////////////////////////////

	//Player�̏����ʒu
	XMFLOAT3 pos_;

	//3D�̃��f�����g�p���Ă��邩�ǂ���
	bool threeDflag_;

	//���̃��f�����g�p���Ă��邩�ǂ���
	bool circleFlag_;

public:

	//�R���X�g���N�^
	Stage(GameObject* parent,std::string name);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	virtual void Initialize() override {};

	//�X�V�̑O�Ɉ��Ă΂��֐�
	virtual void StartUpdate() override {};

	//�X�V
	virtual void Update() override {};

	//�`��
	virtual void Draw() override {};

	//�J��
	virtual void Release() override {};

	//////////////////////////////�֐�////////////////////////////////////

	/// <summary>
	/// �X�e�[�W���쐬����p�̕ϐ�
	/// </summary>
	/// <returns>�X�e�[�W���쐬����p�̕ϐ����擾</returns>
	CreateStage* GetCreateStage() { return pCreateStage_; }

	////////////////////////�Q�b�g�E�Z�b�g�֐�///////////////////////////

	//���f���ԍ��̃Q�b�g�֐�
	int GethModel() { return hModel_[Base]; }

	//���̂ɕ��̂��悹�邽�߂ɋ^�����f���ԍ��̃Q�b�g�֐�
	int GetPolyModell() { return hModel_[PolyModel]; }

	//Pos�̃Q�b�g�֐�
	XMFLOAT3 GetPos() { return pos_; }

	//3D�̓���������������
	bool GetthreeDflag() { return threeDflag_; }

	//���̏�œ���������������
	bool GetCircleflag() { return circleFlag_; }
};

