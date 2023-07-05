#include "EasingMove.h"
#include "../ResourceManager/Easing.h"
#include "../ResourceManager/Time.h"

//コンストラクタ
EasingMove::EasingMove()
	:targetPos_(nullptr), beforePos_(XMFLOAT3(ZERO, ZERO, ZERO)), afterPos_(XMFLOAT3(ZERO, ZERO, ZERO)), moveTime_(ZERO), easingFunc(Easing::InBack), nowTime_(ZERO), timerhNum_((int)ZERO), isSet_(false), endEasingCount_(ZERO), beforeEndEasingCount_(ZERO)
{
	//タイマー作成
	ARGUMENT_INITIALIZE(timerhNum_, Time::Add());
}

//コンストラクタ
EasingMove::EasingMove(XMFLOAT3* targetPos, XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float))
	:targetPos_(targetPos), beforePos_(beforePos), afterPos_(afterPos), moveTime_(moveTime), easingFunc(func), nowTime_(ZERO), timerhNum_((int)ZERO), isSet_(true), endEasingCount_(ZERO), beforeEndEasingCount_(ZERO)
{
	//タイマー作成
	ARGUMENT_INITIALIZE(timerhNum_,Time::Add());
}


//イージングしながら移動
bool EasingMove::Move()
{
	if (!isSet_) return false;

	//タイムがロックされていたらアンロック
	if (Time::isLock(timerhNum_)) Time::UnLock(timerhNum_);

	//どのくらいの割合時間がたったか求める(0～1)
	ARGUMENT_INITIALIZE(nowTime_, (Time::GetTimef(timerhNum_) / moveTime_));

	//もし最後まで終わっていたのならtrueを返す
	if (nowTime_ > 1)
	{
		ARGUMENT_INITIALIZE(endEasingCount_, beforeEndEasingCount_ + 1);
		return true;
	}

	(*targetPos_) = beforePos_;
	float x = afterPos_.x - beforePos_.x;
	float y = afterPos_.y - beforePos_.y;
	float z = afterPos_.z - beforePos_.z;
	(*targetPos_).x += (x * (*easingFunc)(nowTime_));
	(*targetPos_).y += (y * (*easingFunc)(nowTime_));
	(*targetPos_).y += (z * (*easingFunc)(nowTime_));

	ARGUMENT_INITIALIZE(beforeEndEasingCount_, endEasingCount_);

	return false;
}

//リセット
void EasingMove::Reset(XMFLOAT3* targetPos,XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float))
{
	//各変数初期化
	ARGUMENT_INITIALIZE(targetPos_, targetPos);
	ARGUMENT_INITIALIZE(beforePos_,beforePos);
	ARGUMENT_INITIALIZE(afterPos_,afterPos);
	ARGUMENT_INITIALIZE(moveTime_,moveTime);
	ARGUMENT_INITIALIZE(easingFunc,func);
	ARGUMENT_INITIALIZE(nowTime_,ZERO);
	ARGUMENT_INITIALIZE(isSet_,true);

	//タイム初期化
	Time::Reset(timerhNum_);
	Time::Lock(timerhNum_);
}

//まだ動いているのか取得
bool EasingMove::IsMove()
{
	return (isSet_ && nowTime_ < 1);
}

/// <summary>
/// 初期化
/// </summary>
void EasingMove::Initialize()
{
	//情報初期化
	ARGUMENT_INITIALIZE(nowTime_, ZERO);
	ARGUMENT_INITIALIZE(isSet_, false);

	//タイム初期化
	Time::Reset(timerhNum_);
	Time::Lock(timerhNum_);
}


