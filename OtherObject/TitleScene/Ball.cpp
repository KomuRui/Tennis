#include "Ball.h"
#include "../../Engine/System.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/Collider/SphereColliderA.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include <math.h>
#include <cmath>

namespace
{
	static const int ANGLE = 45;			        //角度
	static const int ADD_ANGLE_VALUE = 15;          //加算する角度の値
	static const float GRAVITY = 9.8f;		        //重力
	static const float MAX_RATIO = 1.0f;	        //最大の割合
	static const float LANDING_EFFECT_POS_Y = 0.1f; //着地エフェクトのYポジション
	static const float MAX_POS_X = 4.34f;           //最大X値
	static const float MAX_POS_Z = 11.9f;           //最大Z値
	static const float MIN_POS_X = -4.34f;          //最小X値
	static const float MIN_POS_Z = -11.9f;          //最小Z値

	static const XMFLOAT4 AMBIENT_COLOR = { 1.0f, 1.0f, ZERO, ZERO }; //アンビエント色
}

//コンストラクタ
Ball::Ball(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), ratio_(ZERO), strength_(ZERO,ZERO), endPointDirection_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)),
	startPoint_(ZERO, ZERO, ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), v0_(ZERO,ZERO), pLine_(nullptr),
	hLandEffectName_("LandEffect"), hDropEffectName_("DropEffect"), isGoToBasePoint_(true), ballStatus_(BallStatus::PURPOSE_MOVE), boundCount_(ZERO), hShadowModel_(ZERO), dropEffectFilePath_("Effect/SliceDrop.txt")
{
}

Ball::Ball(GameObject* parent)
	:NormalObject(parent, "Ball/Ball.fbx", "Ball"), ratio_(ZERO), strength_(ZERO, ZERO), endPointDirection_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
	startPoint_(ZERO,ZERO,ZERO), endPoint_(ZERO, ZERO, ZERO), hTime_(ZERO), moveTime_(1.0f), v0_(ZERO, ZERO), pLine_(nullptr),
	hLandEffectName_("LandEffect"), hDropEffectName_("DropEffect"), isGoToBasePoint_(true), ballStatus_(BallStatus::PURPOSE_MOVE), boundCount_(ZERO), hShadowModel_(ZERO), dropEffectFilePath_("Effect/SliceDrop.txt")
{}

//初期化
void Ball::ChildInitialize()
{
	//各初期化
	ARGUMENT_INITIALIZE(transform_->position_, BasePointManager::GetRandomBasePoint(true));
	ARGUMENT_INITIALIZE(startPoint_, transform_->position_);
	ARGUMENT_INITIALIZE(endPoint_,BasePointManager::GetRandomBasePoint(false));
	ARGUMENT_INITIALIZE(endPointDirection_,endPoint_ - startPoint_);
	ARGUMENT_INITIALIZE(strength_.x, Random(1, 5));
	ARGUMENT_INITIALIZE(strength_.y, Random(2, 5));
	ARGUMENT_INITIALIZE(moveTime_, 0.7f);
	ARGUMENT_INITIALIZE(hTime_, Time::Add());
	ARGUMENT_INITIALIZE(v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(v0_.x, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(pLine_, new PolyLine);
	pLine_->Load("Image/Effect/circle_Wh.png");
	pLine_->AddPosition(transform_->position_);

	//影のモデルロード
	ARGUMENT_INITIALIZE(hShadowModel_, ModelManager::Load("Ball/BallShadow.fbx"));
	assert(hShadowModel_ >= ZERO);
	ARGUMENT_INITIALIZE(tShadow_.position_, transform_->position_);
	ARGUMENT_INITIALIZE(tShadow_.position_.y, 0.2f);
	SetShadow(false);

	//着地エフェクト表示(同じ高さに表示すると被ってしまうので、少し上げる)
	XMFLOAT3 pos = endPoint_;
	ARGUMENT_INITIALIZE(pos.y, LANDING_EFFECT_POS_Y);
	OtherEffectManager::LandingEffect(hLandEffectName_,pos, moveTime_);

	//雫みたいなエフェクト表示
	EffectManager::Draw(hDropEffectName_,dropEffectFilePath_, transform_->position_);

	//当たり判定
	SphereColliderA* collision = new SphereColliderA({ ZERO,ZERO,ZERO },0.1f);
	AddCollider(collision);

	//アンビエント
	ModelManager::SetAmbient(hModel_, AMBIENT_COLOR);

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

	//影のポジション更新
	ARGUMENT_INITIALIZE(tShadow_.position_, transform_->position_);
	ARGUMENT_INITIALIZE(tShadow_.position_.y, 0.01f);
}

//描画
void Ball::ChildDraw()
{
	//影描画
	ModelManager::SetTransform(hShadowModel_, &tShadow_);
	ModelManager::Draw(hShadowModel_);

	//ポリライン描画
	pLine_->Draw();
}

//目的地まで移動
void Ball::MoveToPurpose()
{
	//どのくらいの割合時間がたったか求める(0～1)
	ARGUMENT_INITIALIZE(ratio_, (Time::GetTimef(hTime_) / moveTime_));

	//0～1の範囲におさめる
	ARGUMENT_INITIALIZE(ratio_, std::min<float>(ratio_, MAX_RATIO));

	//現在の位置
	XMFLOAT3 nowPos = VectorToFloat3(startPoint_ + (endPointDirection_ * ratio_));
	nowPos.y = ((v0_.y * sin(XMConvertToRadians(ANGLE)) * ratio_) - (0.5f * GRAVITY * ratio_ * ratio_)) * strength_.y;
	nowPos.y += startPoint_.y * (MAX_RATIO - ratio_);

	//X方向の強さが0以外のなら
	if (strength_.x != ZERO)
	{
		nowPos.x = ((v0_.x * sin(XMConvertToRadians(ANGLE)) * ratio_) - (0.5f * GRAVITY * ratio_ * ratio_)) + nowPos.x * (MAX_RATIO - ratio_);
		
		//負なら
		if(signbit(strength_.x))
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * ratio_)) * strength_.x * 2);
		//正なら
		else 
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * ratio_)) * strength_.x / 2);
	}

	//移動前のポジション保存
	XMFLOAT3 beforePos = transform_->position_;

	//求めたポジション設定
	ARGUMENT_INITIALIZE(transform_->position_, nowPos);
	pLine_->AddPosition(transform_->position_);

	//エフェクトのポジション更新
	ARGUMENT_INITIALIZE(VFX::GetEmitter(hDropEffectName_)->data.position,transform_->position_);

	//進行ベクトルを求める
	ARGUMENT_INITIALIZE(progressVector_, transform_->position_ - beforePos);

	//もし目標地点までの移動が終わったのなら
	if (ratio_ >= MAX_RATIO)
	{
		//反射ベクトルを求めて進行ベクトルとする
		ARGUMENT_INITIALIZE(progressVector_, XMVector3Reflect(progressVector_, UP_VECTOR));
		
		//バウンド状態に
		ARGUMENT_INITIALIZE(ballStatus_, BallStatus::BOUND_MOVE);
		
		//タイマーリセット
		Time::Reset(hTime_);

		//正反射ベクトルの角度を求めたいので正反射ベクトルのYを無視したベクトルを作る
		XMVECTOR v = { XMVectorGetX(progressVector_),ZERO,XMVectorGetZ(progressVector_),ZERO };

		//正反射ベクトルの角度で放物線を描くと低い弾道になるので、定数分角度を増やす
		ARGUMENT_INITIALIZE(firstAngle_,GetDot(progressVector_, v) + XMConvertToRadians(ADD_ANGLE_VALUE));
	}
}

//バウンド移動
void Ball::BoundMove()
{

	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + XMVector3Normalize(progressVector_) * 0.2f));

	float time = Time::GetTimef(hTime_);
	XMFLOAT3 nowPos = transform_->position_;
	nowPos.y = (v0_.y * sin(firstAngle_) * time) - (0.5f * GRAVITY * (time * time));

	transform_->position_.y = nowPos.y;

	//エフェクトのポジション更新
	pLine_->AddPosition(transform_->position_);
	ARGUMENT_INITIALIZE(VFX::GetEmitter(hDropEffectName_)->data.position, transform_->position_);


	if (transform_->position_.y < ZERO)
	{

		ARGUMENT_INITIALIZE(progressVector_, XMVector3Reflect(progressVector_, UP_VECTOR));
		
		XMVECTOR v = { XMVectorGetX(progressVector_),ZERO,XMVectorGetZ(progressVector_),ZERO };
		firstAngle_ = GetDot(progressVector_, v);
		Time::Reset(hTime_);
		v0_.y *= 0.4f;

		boundCount_++;

		if (boundCount_ == 2)
		{
			//次の目的地に移動するように
			ARGUMENT_INITIALIZE(ballStatus_, BallStatus::PURPOSE_MOVE);
			ARGUMENT_INITIALIZE(boundCount_,ZERO);

			Time::Reset(hTime_);
			VFX::ForcedEnd(hLandEffectName_);
			VFX::ForcedEnd(hDropEffectName_);

			//打つ強さをランダムに取得
			HitStrength h =  GameManager::GetpPlayer()->GetRacket()->GetRamdomHitStrength();

			//リセット
			Reset(h.strength_.x, h.strength_.y,h.moveTime_,isGoToBasePoint_,BasePointManager::GetRandomBasePointName());
		}
	}
}

//リセット(始点終点すべて再設定)
void Ball::Reset(float strengthX, float strengthY, float moveTime, bool isGotoPlayer, string basePpointName)
{
	//向かうポジションを取得(少しランダムにずらす)
	XMFLOAT3 endPos = BasePointManager::GetBasePoint(basePpointName, isGotoPlayer);
	endPos.x += ((rand() % 31 + 1) / 10) * (rand() % 3 - 1);
	endPos.z += ((rand() % 31 + 1) / 10) * (rand() % 3 - 1);

	//クランプする
	ARGUMENT_INITIALIZE(endPos.x, Clamp<float>(endPos.x, MAX_POS_X, MIN_POS_X));
	ARGUMENT_INITIALIZE(endPos.z, Clamp<float>(endPos.z, MAX_POS_Z, MIN_POS_Z));

	//各情報再設定
	ARGUMENT_INITIALIZE(startPoint_, transform_->position_);
	ARGUMENT_INITIALIZE(endPoint_, endPos);
	ARGUMENT_INITIALIZE(endPointDirection_, endPoint_ - startPoint_);
	ARGUMENT_INITIALIZE(v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(v0_.x, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(moveTime_, moveTime)
	ARGUMENT_INITIALIZE(strength_.y, strengthY);
	ARGUMENT_INITIALIZE(strength_.x, strengthX);
	Time::Reset(hTime_);

	//ネットをしていたらボールの軌道を修正する
	//ネットのZ位置を通過するときの秒数を求める
	float t = abs(startPoint_.z / abs(XMVectorGetZ(endPointDirection_)));

	//ネットのZ位置を通過するときのY位置を求める
	float y = (v0_.y * sin(XMConvertToRadians(ANGLE)) * t) - (0.5f * GRAVITY * pow(t, 2));

	//もしYの位置がネットの位置より低いなら
	if (y <= 1.2f)
	{
		//差分を求める
		float differential = 1.2f - y;

		//差分 + 定数分Yの強さを増やす
		strength_.y += differential * 2.0f;
	}

	//着地エフェクト表示(同じ高さに表示すると被ってしまうので、少し上げる)
	XMFLOAT3 pos = endPoint_;
	ARGUMENT_INITIALIZE(pos.y, LANDING_EFFECT_POS_Y);
	VFX::ForcedEnd(hLandEffectName_);
    OtherEffectManager::LandingEffect(hLandEffectName_,pos, moveTime_);

	//雫みたいなエフェクト表示
	VFX::ForcedEnd(hDropEffectName_);
	EffectManager::Draw(hDropEffectName_,dropEffectFilePath_, transform_->position_);

	//次の目的地に移動するように
	ARGUMENT_INITIALIZE(ballStatus_, BallStatus::PURPOSE_MOVE);

	//逆にする
	if(isGotoPlayer)
		isGoToBasePoint_ = false;
	else
		isGoToBasePoint_ = true;
}

//何かのオブジェクトに当たった時に呼ばれる関数
void Ball::TimeMethod()
{
	Enter();
}

//指定したZ位置を通過するときのボールの位置を取得
XMFLOAT3  Ball::GetSpecifyPosZBallPosition(float zPos)
{
	//ネットのZ位置を通過するときの秒数を求める
	float t = (zPos - startPoint_.z) / XMVectorGetZ(endPointDirection_);

	XMFLOAT3 nowPos = VectorToFloat3(startPoint_ + (endPointDirection_ * t));

	//X方向の強さが0以外のなら
	if (strength_.x != ZERO)
	{
		nowPos.x = ((v0_.x * sin(XMConvertToRadians(ANGLE)) * t) - (0.5f * GRAVITY * t * t)) + nowPos.x * (MAX_RATIO - t);

		//負なら
		if (signbit(strength_.x))
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * t)) * strength_.x * 2);
		//正なら
		else
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * t)) * strength_.x / 2);
	}

	return nowPos;
}