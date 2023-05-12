#include "Ball.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Manager/BasePointManager/BasePointManager.h"
#include "../../Engine/ResourceManager/Time.h"
#include <math.h>
#include <cmath>

namespace
{
	static const int ANGLE = 45.0f;		//角度
	static const float GRAVITY = 9.8f;	//重力
}

//コンストラクタ
Ball::Ball(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), ratio(ZERO), upStrength_(ZERO), endPointDirection_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)),
	startPoint_(ZERO, ZERO, ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), vY0_(ZERO), vX0_(ZERO), pLine_(nullptr)
{
}

Ball::Ball(GameObject* parent)
	:NormalObject(parent, "Ball/Ball.fbx", "Ball"), ratio(ZERO), upStrength_(ZERO), endPointDirection_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
	startPoint_(ZERO,ZERO,ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), vY0_(ZERO), vX0_(ZERO), pLine_(nullptr)
{}

//初期化
void Ball::ChildInitialize()
{
	//各初期化
	ARGUMENT_INITIALIZE(transform_.position_,BasePointManager::GetBasePoint("Back_R", true));
	ARGUMENT_INITIALIZE(startPoint_,BasePointManager::GetBasePoint("Back_R", true));
	ARGUMENT_INITIALIZE(endPoint_,BasePointManager::GetBasePoint("Back_R", false));
	ARGUMENT_INITIALIZE(endPointDirection_,endPoint_ - startPoint_);
	ARGUMENT_INITIALIZE(upStrength_, Random(1, 5));
	ARGUMENT_INITIALIZE(moveTime_, Random(1, 2));
	ARGUMENT_INITIALIZE(hTime_, Time::Add());
	ARGUMENT_INITIALIZE(vY0_, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(vX0_, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(pLine_, new PolyLine);
	pLine_->Load("Image/Effect/tex.png");
	pLine_->AddPosition(transform_.position_);

	Time::UnLock(hTime_);
}

//更新
void Ball::ChildUpdate()
{
	//どのくらいの割合時間がたったか求める(0～1)
	ARGUMENT_INITIALIZE(ratio, (Time::GetTimef(hTime_) / moveTime_));

	//0～1の範囲におさめる
	ARGUMENT_INITIALIZE(ratio, std::min<float>(ratio, 1.0f));

	//現在の位置
	XMFLOAT3 nowPos = VectorToFloat3(startPoint_ + (endPointDirection_ * ratio));
	nowPos.y = ((vY0_ *  sin(XMConvertToRadians(ANGLE)) * ratio) - (0.5f * GRAVITY * ratio * ratio)) * upStrength_;
	nowPos.x = ((vX0_ * sin(XMConvertToRadians(ANGLE)) * ratio) - (0.5f * GRAVITY * ratio * ratio)) + nowPos.x * (1.0f - ratio);

	ARGUMENT_INITIALIZE(transform_.position_, nowPos);
	pLine_->AddPosition(transform_.position_);

	//もし目標地点までの移動が終わったのなら
	if (ratio >= 1.0f) Reset();
}

//描画
void Ball::ChildDraw()
{
	pLine_->Draw();
}

//リセット(始点終点すべて再設定)
void Ball::Reset()
{
	static bool flag = false;

	if (flag)
	{
		ARGUMENT_INITIALIZE(transform_.position_, BasePointManager::GetBasePoint("Back_R", true));
		ARGUMENT_INITIALIZE(startPoint_, BasePointManager::GetBasePoint("Back_R", true));
		ARGUMENT_INITIALIZE(endPoint_, BasePointManager::GetBasePoint("Back_R", false));
		ARGUMENT_INITIALIZE(endPointDirection_, endPoint_ - startPoint_);
		ARGUMENT_INITIALIZE(vY0_, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(vX0_, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(moveTime_, Random(1, 2))
		ARGUMENT_INITIALIZE(upStrength_, Random(1, 5));
		Time::Reset(hTime_);

		flag = false;
	}
	else
	{
		ARGUMENT_INITIALIZE(transform_.position_, BasePointManager::GetBasePoint("Back_R", false));
		ARGUMENT_INITIALIZE(startPoint_, BasePointManager::GetBasePoint("Back_R", false));
		ARGUMENT_INITIALIZE(endPoint_, BasePointManager::GetBasePoint("Back_R", true));
		ARGUMENT_INITIALIZE(endPointDirection_, endPoint_ - startPoint_);
		ARGUMENT_INITIALIZE(vY0_, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(vX0_, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(moveTime_, Random(1, 2))
		ARGUMENT_INITIALIZE(upStrength_, Random(1, 5));
		Time::Reset(hTime_);

		flag = true;
	}
}