#include "HermiteSplineMove.h"
#include "../ResourceManager/Time.h"

//�萔
namespace
{
	static const int MIN_DATA_VALUE = 2; //�Œ�f�[�^�l
}

//�R���X�g���N�^
HermiteSplineMove::HermiteSplineMove()
	:isMove_(false), nowLookValue_(ZERO), timerhNum_(-1), moveTime_(2.0f), nowTime_(ZERO), isFinish_(false)
{
	//�^�C�}�[�쐬
	ARGUMENT_INITIALIZE(timerhNum_, Time::Add());
	Time::Lock(timerhNum_);
}

//�f�X�g���N�^
HermiteSplineMove::~HermiteSplineMove()
{
}

//�X�V
XMFLOAT3 HermiteSplineMove::Updata()
{
	//�G���[�l�������Ȃ��̂Ȃ炱�̐揈�����Ȃ�
	if (!isMove_ || pathData_.size() < MIN_DATA_VALUE) return XMFLOAT3(ZERO,ZERO,ZERO);

	XMVECTOR pos0 = XMLoadFloat3(&pathData_.at(nowLookValue_).first);
	XMVECTOR tan0 = XMLoadFloat3(new XMFLOAT3((pathData_.at(nowLookValue_ + 1).first.x - pathData_.at(nowLookValue_).first.x), (pathData_.at(nowLookValue_ + 1).first.y - pathData_.at(nowLookValue_).first.y), (pathData_.at(nowLookValue_ + 1).first.z - pathData_.at(nowLookValue_).first.z)));
	XMVECTOR pos1 = XMLoadFloat3(&pathData_.at(nowLookValue_ + 1).first);
	XMVECTOR tan1 = { ZERO,ZERO,ZERO,ZERO };

	//�������݌��Ă���l�̎����p�X�f�[�^�̍Ō�̒l�����Ă��Ȃ��̂Ȃ�
	if (nowLookValue_ + 1 != pathData_.size() - 1)
	{
		XMFLOAT3 tan = { ZERO,ZERO,ZERO };
		tan.x = (pathData_.at(nowLookValue_ + 2).first.x - pathData_.at(nowLookValue_ + 1).first.x);
		tan.y = (pathData_.at(nowLookValue_ + 2).first.y - pathData_.at(nowLookValue_ + 1).first.y);
		tan.z = (pathData_.at(nowLookValue_ + 2).first.z - pathData_.at(nowLookValue_ + 1).first.z);
		pathData_.at(nowLookValue_ + 1).second = tan;
		tan1 = XMLoadFloat3(&tan);
	}

	//�^�C�������b�N����Ă�����A�����b�N
	if (Time::isLock(timerhNum_)) Time::UnLock(timerhNum_);

	//�ǂ̂��炢�̊������Ԃ������������߂�(0�`1)
	ARGUMENT_INITIALIZE(nowTime_, (Time::GetTimef(timerhNum_) / moveTime_));

	//�����Ō�܂ŏI����Ă����̂Ȃ玟�̃p�X�Ɉړ�
	if (nowTime_ > 1)
	{
		//�Ō�Ȃ�ŏ��ɖ߂�
		if (nowLookValue_ + 1 >= pathData_.size() - 1)
		{
			ARGUMENT_INITIALIZE(nowLookValue_,ZERO);
			ARGUMENT_INITIALIZE(isFinish_, true);
		}
		else
			nowLookValue_++;

		Time::Reset(timerhNum_);
	}

	return VectorToFloat3(XMVectorHermite(pos0, tan0, pos1, tan1, nowTime_));
}

//�ŏ�����J�n
void HermiteSplineMove::ReStart()
{
	ARGUMENT_INITIALIZE(nowLookValue_, ZERO);
	ARGUMENT_INITIALIZE(nowTime_, ZERO);
	ARGUMENT_INITIALIZE(isFinish_,false);
	ARGUMENT_INITIALIZE(isMove_,true);
	Time::Reset(timerhNum_);
}