#pragma once
#include "../Base/NormalObject.h"
#include "../Engine/GameObject/GameObject.h"
#include "../State/PlayerState/PlayerStateManager.h"
#include "../Engine/ResourceManager/ModelManager.h"
#include "../Engine/Component/Transform/Transform.h"
#include "../OtherObject/PlayScene/TennisCourt.h"
#include "../Engine/Component/HermiteSplineMove.h"

class Racket;

/// <summary>
/// Player�̊��N���X
/// </summary>
class PlayerBase : public NormalObject
{
protected:

	///////////////�L�����̕K�v�ȏ��///////////////////

	Racket* pRacket_;                   //���P�b�g
	PlayerStateManager* pState_;        //Player�̏�Ԃ�\���ϐ�
	TennisCourtName nowMyCourtName_;    //���g������R�[�g�̖��O
	XMFLOAT3 initialPosition_;          //Player�̏����ʒu 
	float power_;                       //�p���[
	float technique_;                   //�e�N�j�b�N

	/////////////////////�J����//////////////////////

	
	vector<std::unique_ptr<HermiteSplineMove>> hermiteMoveTable_; //�G���~�[�g�X�v���C�����g���ăJ�����𓮂���(�A�����ē�����ύX�������̂�vector�ɂ��Ă���)
	int nowLookNum_;    //���݌��Ă���ԍ�                       

	XMVECTOR camVec_;   //Player����J�����܂ł̃x�N�g��
	XMVECTOR camVec2_;  //Player����J�����܂ł̃x�N�g��

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	PlayerBase(GameObject* parent, std::string modelFilePath_, std::string name);


	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	///////////////////////////�֐�////////////////////////////

	/// <summary>
	/// �J�����̏���
	/// </summary>
	void CameraBehavior();

	/// <summary>
	///�Q�[���X�^�[�g���̃J���� 
	/// </summary>
	void GameStartCamera();

	/// <summary>
	/// �T�[�u���V�[�u���̃J�����̏���
	/// </summary>
	void ServeReceiveCameraBehavior();

	/// <summary>
	/// �f�[�^�Z�b�g
	/// </summary>
	void SetData(string posFileName);

	/////////////////////�Z�b�g�Q�b�g�֐�//////////////////////

	/// <summary>
	/// ���g������e�j�X�R�[�g�̖��O��ݒ�
	/// </summary>
	/// <param name="n">�e�j�X�R�[�g�̖��O</param>
	void SetTennisCourtName(TennisCourtName n) { nowMyCourtName_ = n; }

	/// <summary>
	/// ���g������e�j�X�R�[�g�̖��O���擾
	/// </summary>
	/// <returns>���g������e�j�X�R�[�g�̖��O</returns>
	TennisCourtName GetTennisCourtName() { return nowMyCourtName_; }

	/// <summary>
	/// ���f���ԍ��擾
	/// </summary>
	/// <returns>���f���ԍ�</returns>
	int GetModelNum() { return hModel_; } 

	/// <summary>
	/// ���P�b�g�擾
	/// </summary>
	/// <returns>���P�b�g</returns>
	Racket* GetRacket() { return pRacket_; }

	/// <summary>
	/// ��Ԃ��擾
	/// </summary>
	/// <returns>���</returns>
	PlayerStateManager* GetState() { return pState_; }

	/// <summary>
	/// �e�N�j�b�N���擾
	/// </summary>
	/// <returns>�e�N�j�b�N</returns>
	float GetTechnique() { return technique_; }

	/// <summary>
	/// �p���[���擾
	/// </summary>
	/// <returns>�p���[</returns>
	float GetPower() { return power_; }
};

