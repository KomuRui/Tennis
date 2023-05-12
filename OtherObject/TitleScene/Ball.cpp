#include "Ball.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Manager/BasePointManager/BasePointManager.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"
#include "../../Engine/ResourceManager/VFX.h"
#include <math.h>
#include <cmath>

namespace
{
	static const int ANGLE = 45.0f;		//角度
	static const float GRAVITY = 9.8f;	//重力
}

//コンストラクタ
Ball::Ball(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), ratio_(ZERO), strength_(ZERO,ZERO), endPointDirection_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)),
	startPoint_(ZERO, ZERO, ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), v0_(ZERO,ZERO), pLine_(nullptr),
	hEffect_(ZERO), flag(false), ballStatus_(BallStatus::PURPOSE_MOVE)
{
}

Ball::Ball(GameObject* parent)
	:NormalObject(parent, "Ball/Ball.fbx", "Ball"), ratio_(ZERO), strength_(ZERO, ZERO), endPointDirection_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
	startPoint_(ZERO,ZERO,ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), v0_(ZERO, ZERO), pLine_(nullptr),
    hEffect_(ZERO), flag(false), ballStatus_(BallStatus::PURPOSE_MOVE)
{}

//初期化
void Ball::ChildInitialize()
{
	//各初期化
	XMFLOAT3 s = BasePointManager::GetRandomBasePoint(true);
	ARGUMENT_INITIALIZE(transform_.position_,s);
	ARGUMENT_INITIALIZE(startPoint_,s);
	ARGUMENT_INITIALIZE(endPoint_,BasePointManager::GetRandomBasePoint(false));
	ARGUMENT_INITIALIZE(endPointDirection_,endPoint_ - startPoint_);
	ARGUMENT_INITIALIZE(strength_.x, Random(1, 5));
	ARGUMENT_INITIALIZE(strength_.y, Random(1, 5));
	ARGUMENT_INITIALIZE(moveTime_, Random(1, 2));
	ARGUMENT_INITIALIZE(hTime_, Time::Add());
	ARGUMENT_INITIALIZE(v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(v0_.x, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(pLine_, new PolyLine);
	pLine_->Load("Image/Effect/tex.png");
	pLine_->AddPosition(transform_.position_);

	//着地エフェクト表示(同じ高さに表示すると被ってしまうので、少し上げる)
	XMFLOAT3 pos = endPoint_;
	pos.y += 0.1f;
	ARGUMENT_INITIALIZE(hEffect_,OtherEffectManager::LandingEffect(pos, moveTime_));

	//アンビエント
	Model::SetAmbient(hModel_, XMFLOAT4(1.0f, 1.0f, ZERO, ZERO));

	//タイムスタート
	Time::UnLock(hTime_);
}

//更新
void Ball::ChildUpdate()
{
	//状態ごとに分ける
	switch (ballStatus_)
	{
	//目的地まで移動
	case BallStatus::PURPOSE_MOVE:
		MoveToPurpose();
		break;

	//バウンド移動
	case BallStatus::BOUND_MOVE:
		BoundMove();
		break;

	default:
		break;
	}
}

//描画
void Ball::ChildDraw()
{
	pLine_->Draw();
}

//目的地まで移動
void Ball::MoveToPurpose()
{
	//どのくらいの割合時間がたったか求める(0～1)
	ARGUMENT_INITIALIZE(ratio_, (Time::GetTimef(hTime_) / moveTime_));

	//0～1の範囲におさめる
	ARGUMENT_INITIALIZE(ratio_, std::min<float>(ratio_, 1.0f));

	//現在の位置
	XMFLOAT3 nowPos = VectorToFloat3(startPoint_ + (endPointDirection_ * ratio_));
	nowPos.y = ((v0_.y * sin(XMConvertToRadians(ANGLE)) * ratio_) - (0.5f * GRAVITY * ratio_ * ratio_)) * strength_.y;
	nowPos.x = ((v0_.x * sin(XMConvertToRadians(ANGLE)) * ratio_) - (0.5f * GRAVITY * ratio_ * ratio_)) + nowPos.x * (1.0f - ratio_);
	nowPos.x -= sin(XMConvertToRadians(PI_DEGREES * ratio_)) * strength_.x;

	//移動前のポジション保存
	XMFLOAT3 beforePos = transform_.position_;

	//求めたポジション設定
	ARGUMENT_INITIALIZE(transform_.position_, nowPos);
	pLine_->AddPosition(transform_.position_);

	//進行ベクトルを求める
	ARGUMENT_INITIALIZE(progressVector_, transform_.position_ - beforePos);

	//もし目標地点までの移動が終わったのなら
	if (ratio_ >= 1.0f)
	{
		//反射ベクトルを求めて進行ベクトルとする
		ARGUMENT_INITIALIZE(progressVector_, XMVector3Reflect(progressVector_, UP_VECTOR));
		
		//バウンド状態に
		ARGUMENT_INITIALIZE(ballStatus_, BallStatus::BOUND_MOVE);
		
		Time::Reset(hTime_);
		VFX::ForcedEnd(hEffect_);
		//Reset();
	}
}

//バウンド移動
void Ball::BoundMove()
{
	static int a = 1;

	ARGUMENT_INITIALIZE(transform_.position_, VectorToFloat3(transform_.position_ + XMVector3Normalize(progressVector_) * 0.2f));

	progressVector_ -= XMVectorSet(ZERO, 0.015f, ZERO, ZERO);

	pLine_->AddPosition(transform_.position_);

	if (transform_.position_.y < ZERO)
	{

		ARGUMENT_INITIALIZE(progressVector_, XMVector3Reflect(progressVector_, UP_VECTOR));
		a++;

		if (a == 3)
		{
			//バウンド状態に
			ARGUMENT_INITIALIZE(ballStatus_, BallStatus::PURPOSE_MOVE);
			a = 1;
			Time::Reset(hTime_);
			VFX::ForcedEnd(hEffect_);
			Reset();
		}
	}
}

//リセット(始点終点すべて再設定)
void Ball::Reset()
{

	if (flag)
	{
		ARGUMENT_INITIALIZE(startPoint_, transform_.position_);
		ARGUMENT_INITIALIZE(endPoint_, BasePointManager::GetRandomBasePoint(false));
		ARGUMENT_INITIALIZE(endPointDirection_, endPoint_ - startPoint_);
		ARGUMENT_INITIALIZE(v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(v0_.x, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(moveTime_, Random(1, 2))
		ARGUMENT_INITIALIZE(strength_.y, Random(1, 5));
		ARGUMENT_INITIALIZE(strength_.x, Random(1, 5));
		Time::Reset(hTime_);

		//着地エフェクト表示(同じ高さに表示すると被ってしまうので、少し上げる)
		XMFLOAT3 pos = endPoint_;
		pos.y += 0.1f;
		VFX::ForcedEnd(hEffect_);
		ARGUMENT_INITIALIZE(hEffect_, OtherEffectManager::LandingEffect(pos, moveTime_));

		flag = false;
	}
	else
	{
		ARGUMENT_INITIALIZE(startPoint_, transform_.position_);
		ARGUMENT_INITIALIZE(endPoint_, BasePointManager::GetRandomBasePoint(true));
		ARGUMENT_INITIALIZE(endPointDirection_, endPoint_ - startPoint_);
		ARGUMENT_INITIALIZE(v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(v0_.x, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
		ARGUMENT_INITIALIZE(moveTime_, Random(1, 2))
		ARGUMENT_INITIALIZE(strength_.y, Random(1, 5));
		ARGUMENT_INITIALIZE(strength_.x, Random(1, 5));
		Time::Reset(hTime_);

		//着地エフェクト表示(同じ高さに表示すると被ってしまうので、少し上げる)
		XMFLOAT3 pos = endPoint_;
		pos.y += 0.1f;
		VFX::ForcedEnd(hEffect_);
		ARGUMENT_INITIALIZE(hEffect_, OtherEffectManager::LandingEffect(pos, moveTime_));

		flag = true;
	}
}