#include "Posture.h"

//�萔
namespace
{
	static const float RAY_HIT_DISTANCE = 1.0f;				//���C�̓�����������
	static const float GRAVITY_STRENGTH = 0.083f;           //�d�͂̋���
	static const float NORMAL_INTERPOLATION_FACTOR = 0.045f;//�@�����Ԃ���Ƃ��̕�ԌW��
	static const int MAX_NORMAL_RADIANS = 50;               //�@���Ƃ̍ő�p�x
}

//�R���X�g���N�^
Posture::Posture()
{
	ARGUMENT_INITIALIZE(transform_,nullptr);
	ARGUMENT_INITIALIZE(down_,nullptr);
	ARGUMENT_INITIALIZE(vNormal_,nullptr);
	ARGUMENT_INITIALIZE(hGroundModel_, (int)ZERO);
}

//�X�V
void Posture::Update()
{
	//�������Ŏg���̂Ő�ɐ錾���Ă���
	RayCastData downData;
	downData.start = transform_->position_;        //���C�̃X�^�[�g�ʒu
	downData.dir = VectorToFloat3(*down_);         //���C�̕���
	Model::AllRayCast(hGroundModel_, &downData);   //���C�𔭎�(All)

	 //�^���̖@���𒲂ׂăL�����̏㎲�����肷��
	CheckUnderNormal(downData);

	//�X�e�[�W�Ƃ̓����蔻��
	StageRayCast(downData);
}

//�^���̖@���𒲂ׂăL�����̏㎲�����肷��
void Posture::CheckUnderNormal(const RayCastData& data)
{
	if (data.hit && (XMVectorGetX(*vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetY(-(*vNormal_)) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetZ(-(*vNormal_)) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data.normal)))))
	{
		//���̃L�����̏�x�N�g��vNormal�Ɖ��̖@���̓��ς����߂�
		float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data.normal)), XMVector3Normalize(*vNormal_)));

		//�p�x��50�x�ȓ��Ɏ��܂��Ă�����(�ǂƂ��ɏ�点�Ȃ�����)
		if (acos(dotX) < XMConvertToRadians(MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-MAX_NORMAL_RADIANS))
		{
			//������ƕ��
			*vNormal_ = XMVector3Normalize((XMVectorLerp(XMVector3Normalize(*vNormal_), XMLoadFloat3(&data.normal), NORMAL_INTERPOLATION_FACTOR)));
			*down_ = -(*vNormal_);
		}
	}
}

//���C�œ����蔻��(3D�p)
void Posture::StageRayCast(const RayCastData& data)
{
	//////////////////////////////�͂ݏo������������//////////////////////////////////////

	//���̋�����1.0�ȏォ�d�͓K�p����Ȃ�
	if (data.dist >= RAY_HIT_DISTANCE)
	{
		transform_->position_ = Float3Add(transform_->position_, VectorToFloat3((-(*vNormal_)) * GRAVITY_STRENGTH));
	}
}
