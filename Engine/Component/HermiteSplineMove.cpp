#include "HermiteSplineMove.h"
#include "../ResourceManager/Time.h"

//定数
namespace
{
	static const int MIN_DATA_VALUE = 2; //最低データ値
}

//コンストラクタ
HermiteSplineMove::HermiteSplineMove()
	:isMove_(false), nowLookValue_(ZERO), timerhNum_(-1), moveTime_(2.0f), nowTime_(ZERO), isFinish_(false)
{
	//タイマー作成
	ARGUMENT_INITIALIZE(timerhNum_, Time::Add());
	Time::Lock(timerhNum_);
}

//デストラクタ
HermiteSplineMove::~HermiteSplineMove()
{
}

//更新
XMFLOAT3 HermiteSplineMove::Updata()
{
	//エラー値か動かないのならこの先処理しない
	if (!isMove_ || pathData_.size() < MIN_DATA_VALUE) return XMFLOAT3(ZERO,ZERO,ZERO);

	XMVECTOR pos0 = XMLoadFloat3(&pathData_.at(nowLookValue_).first);
	XMVECTOR tan0 = XMLoadFloat3(new XMFLOAT3((pathData_.at(nowLookValue_ + 1).first.x - pathData_.at(nowLookValue_).first.x), (pathData_.at(nowLookValue_ + 1).first.y - pathData_.at(nowLookValue_).first.y), (pathData_.at(nowLookValue_ + 1).first.z - pathData_.at(nowLookValue_).first.z)));
	XMVECTOR pos1 = XMLoadFloat3(&pathData_.at(nowLookValue_ + 1).first);
	XMVECTOR tan1 = { ZERO,ZERO,ZERO,ZERO };

	//もし現在見ている値の次がパスデータの最後の値を見ていないのなら
	if (nowLookValue_ + 1 != pathData_.size() - 1)
	{
		XMFLOAT3 tan = { ZERO,ZERO,ZERO };
		tan.x = (pathData_.at(nowLookValue_ + 2).first.x - pathData_.at(nowLookValue_ + 1).first.x);
		tan.y = (pathData_.at(nowLookValue_ + 2).first.y - pathData_.at(nowLookValue_ + 1).first.y);
		tan.z = (pathData_.at(nowLookValue_ + 2).first.z - pathData_.at(nowLookValue_ + 1).first.z);
		pathData_.at(nowLookValue_ + 1).second = tan;
		tan1 = XMLoadFloat3(&tan);
	}

	//タイムがロックされていたらアンロック
	if (Time::isLock(timerhNum_)) Time::UnLock(timerhNum_);

	//どのくらいの割合時間がたったか求める(0～1)
	ARGUMENT_INITIALIZE(nowTime_, (Time::GetTimef(timerhNum_) / moveTime_));

	//もし最後まで終わっていたのなら次のパスに移動
	if (nowTime_ > 1)
	{
		//最後なら最初に戻す
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

//最初から開始
void HermiteSplineMove::ReStart()
{
	ARGUMENT_INITIALIZE(nowLookValue_, ZERO);
	ARGUMENT_INITIALIZE(nowTime_, ZERO);
	ARGUMENT_INITIALIZE(isFinish_,false);
	ARGUMENT_INITIALIZE(isMove_,true);
	Time::Reset(timerhNum_);
}