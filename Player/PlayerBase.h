#pragma once
#include "../Base/Mob.h"
#include "../Engine/GameObject/GameObject.h"
#include "../State/PlayerState/PlayerStateManager.h"
#include "../Engine/ResourceManager/Model.h"

/// <summary>
/// Player�̊��N���X
/// </summary>
class PlayerBase : public Mob
{
protected:

	///////////////�L�����̕K�v�ȏ��///////////////////


	XMMATRIX mPreviousAngle_;          //�W�����v���Ă���Ƃ��̉�]�s��
	float jampRotationPreviousAngle_;  //�W�����v���Ă���Ƃ��̊p�x
	float acceleration_;               //�d�͂̉����x
	float normalInterpolation_;        //�@�����Ԃ���Ƃ��̕�ԌW��
	bool  isCheckNormal_;              //�@���𒲂ׂ邩�ǂ���
	bool  isBeforeLand_;               //�O�񒅒n���Ă������ǂ���

	/////////////////////�J����//////////////////////

	enum Cam
	{
		LONG,          //������
		SHORT,         //�ߋ���
		MAX_CAM_SIZE
	};

	XMVECTOR camVecTotal_[MAX_CAM_SIZE];//�S��ނ̃J�����̋���
	XMVECTOR camVec_;                   //Player����J�����܂ł̋���
	XMMATRIX camMat_;                   //�J�����̊p�x��ύX���邽�߂̃}�g���N�X
	XMVECTOR vCam_;                     //�J�����̈ʒu�܂ł̃x�N�g��
									    
	int   camStatus_;                   //�J�����̏��
	float camAngle_;                    //�J�����̊p�x
	bool  isMoveCamPos_;                //�J�����̃|�W�V�����������ǂ���
	bool  isLockcam_;                   //�J�����Œ肳��Ă���̂Ȃ�


public:

	/// <summary>
	/// Player�̏�Ԃ�\���ϐ�
	/// </summary>
	PlayerStateManager* pState_;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	PlayerBase(GameObject* parent);


	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void ChildInitialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void ChildStartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void ChildDraw() override {};

	//�X�e�[�W�ɍ��킹�ĉ�]
	virtual void RotationInStage() override {};

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	//�����蔻��
	virtual void OnCollision(GameObject* pTarget) override;

	///////////////////////////�֐�////////////////////////////

	/// <summary>
	/// �p����p�̍X�V
	/// </summary>
	virtual void ChildPlayerUpdate() {};

	/// <summary>
	/// �p����p�̏�����
	/// </summary>
	virtual void ChildPlayerInitialize() {};

	/// <summary>
	/// �p����p�̃X�^�[�g�A�b�v�f�[�g
	/// </summary>
	virtual void ChildPlayerStartUpdate() {};

	/// <summary>
	/// �J�����̏���
	/// </summary>
	void CameraBehavior();

	/// <summary>
	/// Player�̃J�����̏���(2D��3D�ŃJ�����̓������Ⴄ�̂�virtual�ɂ���)
	/// </summary>
	virtual void PlayerCameraBehavior(XMFLOAT3* pos, XMFLOAT3* tar) {};

	/// <summary>
	/// �J���������b�N����Ă������̃J�����̏���
	/// </summary>
	void CameraLockBehavior(XMFLOAT3 *pos, XMFLOAT3 *tar);

	/// <summary>
	/// �^���̖@���𒲂ׂăL�����̏㎲�����肷��
	/// </summary>
	void CheckUnderNormal();

	/////////////////////�Z�b�g�Q�b�g�֐�//////////////////////

	/// <summary>
	/// �J�����̈ʒu�𓮂������Z�b�g
	/// </summary>
	void SetCamPosNotMove() { isMoveCamPos_ = false; }

	/// <summary>
	/// �L���������̖@�����ׂ邩�ǂ������Z�b�g
	/// </summary>
	/// <param name="flag">���ׂ�Ȃ�true,���ׂȂ��Ȃ�false</param>
	void SetCheckNormal(const bool& flag) { isCheckNormal_ = flag; }

	/// <summary>
	/// �J�������삵�Ă��邩�ǂ���
	/// </summary>
	/// <returns>���삵�Ă�Ȃ�true,���ĂȂ��Ȃ�false</returns>
	bool IsCamBehavior() { return isLockcam_; }

	/// <summary>
	/// �d�͂��Z�b�g
	/// </summary>
	/// <param name="acceleration">�Z�b�g�������d�͂̒l</param>
	void SetAcceleration(const float& acceleration) { acceleration_ = acceleration; }

	/// <summary>
	/// �W�����v�������̎��̊p�x�ݒ�
	/// </summary>
	/// <param name="angle">�Z�b�g�������W�����v�������̎��̊p�x</param>
	void SetJampRotationPreviousAngle(const float& angle) { jampRotationPreviousAngle_ = angle; }

	/// <summary>
	/// �W�����v���Ă鎞��Player�̉�]�}�g���N�X�Q�b�g
	/// </summary>
	/// <returns>�W�����v���Ă鎞��Player�̉�]�}�g���N�X</returns>
	XMMATRIX GetmPreviousAngle() { return mPreviousAngle_; }

	/// <summary>
	/// �J�����̊p�x�Q�b�g
	/// </summary>
	/// <returns>�J�����̊p�x</returns>
	float GetCamAngle() { return camAngle_; }

	/// <summary>
	/// �J�������삷�邩�ǂ������Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ瓮�삳����,false�Ȃ瓮�삳���Ȃ�</param>
	void SetCamFlag(const bool& flag) { isLockcam_ = flag; }

	/// <summary>
	/// �J�����̃A���O���ߋ����ɃZ�b�g
	/// </summary>
	void SetCamShort() { camStatus_ = SHORT; camVec_ = camVecTotal_[camStatus_]; CameraBehavior(); }

	/// <summary>
	/// �J�����̃A���O���������ɃZ�b�g
	/// </summary>
	void SetCamLong() { camStatus_ = LONG;  camVec_ = camVecTotal_[camStatus_]; CameraBehavior(); }

	/// <summary>
	/// �J�����܂ł̃x�N�g�����Z�b�g
	/// </summary>
	void SetCamVec(const XMVECTOR& v) { vCam_ = v; }

};

