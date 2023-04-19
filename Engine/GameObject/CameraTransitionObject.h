#pragma once
#include "GameObject.h"
#include "../ResourceManager/CreateStage.h"

//�e�X�e�[�W�ŏꏊ���ƂɃJ�����J�ڂ��邽�߂ɕK�v�ȃI�u�W�F�N�g
class CameraTransitionObject : public GameObject
{
private:

	//�K�v�ȏ��
	StageCameraTransition info_;

	//�N���Ɠ������Ă��邩
	bool isHit_;

	//�J�������������ǂ���
	bool isCameraMove_;

public:

	//�R���X�g���N�^
	CameraTransitionObject(GameObject* parent, const StageCameraTransition& camInfo);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

    //������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override {};

	//�X�V
	void Update() override {};

	//�`��
	void Draw() override {};

	//�J��
	void Release() override {};

	//�����蔻��(�Ȃɂ��Ɠ���������)
	void OnCollision(GameObject* pTarget) override;

	//�����蔻��(�N�Ƃ��������Ă��Ȃ���)
	void OutCollision() override;

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	/// <summary>
	/// �J�����𓮂������ǂ����Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ瓮����,false�Ȃ瓮�����Ȃ�</param>
	void SetCamMoveFlag(const bool& flag) { isCameraMove_ = flag; }
};

