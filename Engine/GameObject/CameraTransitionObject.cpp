#include "CameraTransitionObject.h"
#include "../Collider/BoxCollider.h"
#include "Camera.h"
#include "../../Manager/GameManager/GameManager.h"

//�萔
namespace
{
	static const float INTERPOLATION_COEFFICIENT = 0.1f; //��ԌW��
	static const float TIMEMETHOD_CALLING_TIME = 1.0f;   //�^�C�����\�b�h���ĂԎ���
}

//�R���X�g���N�^
CameraTransitionObject::CameraTransitionObject(GameObject* parent, const StageCameraTransition& camInfo)
	:GameObject(parent,"CameraTransitionObject"), isHit_(false), isCameraMove_(true)
{
	//�e�ϐ�������
	ARGUMENT_INITIALIZE(info_, camInfo);
}

//������
void CameraTransitionObject::Initialize()
{
	//���`�̓����蔻��쐬
	BoxCollider* collision = new BoxCollider(XMFLOAT3(ZERO,ZERO, ZERO), info_.CollisionSize);
	AddCollider(collision);
}

//�����蔻��
void CameraTransitionObject::OnCollision(GameObject* pTarget)
{
	//�����������肪Player�ȊO�Ȃ�
	if (pTarget->GetObjectName() != "Player") return;

	//�܂��������Ă��Ȃ��̂Ȃ�
	if (!isHit_)
	{
		//1.0�b��Ƀ��\�b�h���Ă�
		//�����ł�Player�����V���ɃZ�b�g�����J�������猩���ړ������������̂�...
		//�����؂�ւ���Ƒ��삵���炢�̂ŏ����Ԃ������Ă���...
		SetTimeMethod(TIMEMETHOD_CALLING_TIME);
		ARGUMENT_INITIALIZE(isHit_, true);
	}

	//�J�����������Ȃ�
	if (isCameraMove_)
	{
		//�J�����̃|�W�V�����ƃ^�[�Q�b�g�Z�b�g(��Ԃ��Ȃ���ύX)
		XMVECTOR vCamPos = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetPosition())), XMLoadFloat3(&info_.CameraPosition), INTERPOLATION_COEFFICIENT);
		XMVECTOR vCamTar = XMVectorLerp(XMLoadFloat3(new XMFLOAT3(Camera::GetTarget())), XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())), INTERPOLATION_COEFFICIENT);
		Camera::SetPosition(VectorToFloat3(vCamPos));
		Camera::SetTarget(VectorToFloat3(vCamTar));
	}
}

//�����蔻��(�N�Ƃ��������Ă��Ȃ���)
void CameraTransitionObject::OutCollision()
{
	//�������Ă����Ȃ�
	if (isHit_)
	{
		//1.0�b��Ƀ��\�b�h���Ă�
		//�����ł�Player�����V���ɃZ�b�g�����J�������猩���ړ������������̂�...
		//�����؂�ւ���Ƒ��삵���炢�̂ŏ����Ԃ������Ă���...
		SetTimeMethod(TIMEMETHOD_CALLING_TIME);

		//�������Ă��Ȃ���Ԃ�
		ARGUMENT_INITIALIZE(isHit_, false);
	}
}

//�w�肵�����ԂŌĂ΂�郁�\�b�h
void CameraTransitionObject::TimeMethod()
{
	//�J���������ύX
	GameManager::GetpPlayer()->SetCamFlag(!(GameManager::GetpPlayer()->IsCamBehavior()));
}