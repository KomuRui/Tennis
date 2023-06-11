#include "Ball.h"
#include "../../Engine/System.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../OtherObject/TitleScene/Racket.h"
#include "../../OtherObject/TitleScene/Referee.h"
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
	static const XMVECTOR TOSS_UP_VALUE = { ZERO,0.2f,ZERO,ZERO };    //トスアップの時の値

	static const XMFLOAT4 AMBIENT_COLOR = { 1.0f, 1.0f, ZERO, ZERO }; //アンビエント色
}

//コンストラクタ
Ball::Ball(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name)
{
	hShadowModel_ = ZERO;
	ballInfo_.ratio_ = ZERO;
	ballInfo_.hTime_ = ZERO;
	ballInfo_.boundCount_ = ZERO;
	ballInfo_.hTime_ = ZERO;
	ballInfo_.moveTime_ = 1.0f;
	ballInfo_.strength_ = { ZERO,ZERO };
	ballInfo_.v0_ = { ZERO,ZERO };
	ballInfo_.endPointDirection_ = XMVectorSet(ZERO, ZERO, ZERO, ZERO);
	ballInfo_.tossUpVector_ = TOSS_UP_VALUE;
	ballInfo_.startPoint_ = { ZERO, ZERO, ZERO };
	ballInfo_.endPoint_ = { ZERO, ZERO, ZERO };
	ballInfo_.pLine_ = nullptr;
	ballInfo_.isGoToBasePoint_ = false;
	ballInfo_.isTossUp_ = false;
	ballInfo_.hLandEffectName_ = "LandEffect";
	ballInfo_.hDropEffectName_ = "DropEffect";
	ballInfo_.dropEffectFilePath_ = "Effect/SliceDrop.txt";
	ballInfo_.ballStatus_ = BallStatus::PLAYER_HAV_BALL;
}

Ball::Ball(GameObject* parent)
	:NormalObject(parent, "Ball/Ball.fbx", "Ball")
{
	hShadowModel_ = ZERO;
	ballInfo_.ratio_ = ZERO;
	ballInfo_.hTime_ = ZERO;
	ballInfo_.boundCount_ = ZERO;
	ballInfo_.hTime_ = ZERO;
	ballInfo_.moveTime_ = 1.0f;
	ballInfo_.strength_ = { ZERO,ZERO };
	ballInfo_.v0_ = { ZERO,ZERO };
	ballInfo_.endPointDirection_ = XMVectorSet(ZERO, ZERO, ZERO, ZERO);
	ballInfo_.tossUpVector_ = TOSS_UP_VALUE;
	ballInfo_.startPoint_ = { ZERO, ZERO, ZERO };
	ballInfo_.endPoint_ = { ZERO, ZERO, ZERO };
	ballInfo_.pLine_ = nullptr;
	ballInfo_.isGoToBasePoint_ = false;
	ballInfo_.isTossUp_ = false;
	ballInfo_.hLandEffectName_ = "LandEffect";
	ballInfo_.hDropEffectName_ = "DropEffect";
	ballInfo_.dropEffectFilePath_ = "Effect/SliceDrop.txt";
	ballInfo_.ballStatus_ = BallStatus::PLAYER_HAV_BALL;
}

//初期化
void Ball::ChildInitialize()
{
	//各初期化
	//ARGUMENT_INITIALIZE(transform_->position_, BasePointManager::GetRandomBasePoint(true));
	//ARGUMENT_INITIALIZE(startPoint_, transform_->position_);
	//ARGUMENT_INITIALIZE(endPoint_,BasePointManager::GetRandomBasePoint(false));
	//ARGUMENT_INITIALIZE(endPointDirection_,endPoint_ - startPoint_);
	//ARGUMENT_INITIALIZE(strength_.x, Random(1, 5));
	//ARGUMENT_INITIALIZE(strength_.y, Random(2, 5));
	//ARGUMENT_INITIALIZE(moveTime_, 0.7f);
	//ARGUMENT_INITIALIZE(hTime_, Time::Add());
	//ARGUMENT_INITIALIZE(v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	//ARGUMENT_INITIALIZE(v0_.x, (endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(ballInfo_.pLine_, new PolyLine);
	ballInfo_.pLine_->Load("Image/Effect/circle_Wh.png");
	ballInfo_.pLine_->AddPosition(transform_->position_);

	//影のモデルロード
	ARGUMENT_INITIALIZE(hShadowModel_, ModelManager::Load("Ball/BallShadow.fbx"));
	assert(hShadowModel_ >= ZERO);
	ARGUMENT_INITIALIZE(tShadow_.position_, transform_->position_);
	ARGUMENT_INITIALIZE(tShadow_.position_.y, 0.2f);
	SetShadow(false);

	//着地エフェクト表示(同じ高さに表示すると被ってしまうので、少し上げる)
	//XMFLOAT3 pos = endPoint_;
	//ARGUMENT_INITIALIZE(pos.y, LANDING_EFFECT_POS_Y);
	//OtherEffectManager::LandingEffect(hLandEffectName_,pos, moveTime_);

	//雫みたいなエフェクト表示
	//EffectManager::Draw(hDropEffectName_,dropEffectFilePath_, transform_->position_);

	//当たり判定
	sphere_ = AddComponent<SphereCollider>();
	sphere_->SetPos({ ZERO,ZERO,ZERO });
	sphere_->SetSize({ 0.1f,0.1f,0.1f });

	//アンビエント
	ModelManager::SetAmbient(hModel_, AMBIENT_COLOR);

	//タイムスタート
	Time::UnLock(ballInfo_.hTime_);
}

//更新
void Ball::ChildUpdate()
{
	//状態ごとに分ける
	switch (ballInfo_.ballStatus_)
	{

	//目的地まで移動
	case BallStatus::PURPOSE_MOVE:
		MoveToPurpose();
		break;

	//バウンド移動
	case BallStatus::BOUND_MOVE:
		BoundMove();
		break;

	//プレイヤーがボールを持っている状態
	case BallStatus::PLAYER_HAV_BALL:
		PlayerHavingBall();
		break;

	//停止
	case BallStatus::STOP:
		Stop();
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
	ballInfo_.pLine_->Draw();
}

//目的地まで移動
void Ball::MoveToPurpose()
{
	//どのくらいの割合時間がたったか求める(0～1)
	ARGUMENT_INITIALIZE(ballInfo_.ratio_, (Time::GetTimef(ballInfo_.hTime_) / ballInfo_.moveTime_));

	//0～1の範囲におさめる
	ARGUMENT_INITIALIZE(ballInfo_.ratio_, std::min<float>(ballInfo_.ratio_, MAX_RATIO));

	//現在の位置
	XMFLOAT3 nowPos = VectorToFloat3(ballInfo_.startPoint_ + (ballInfo_.endPointDirection_ * ballInfo_.ratio_));
	nowPos.y = ((ballInfo_.v0_.y * sin(XMConvertToRadians(ANGLE)) * ballInfo_.ratio_) - (0.5f * GRAVITY * ballInfo_.ratio_ * ballInfo_.ratio_)) * ballInfo_.strength_.y;
	nowPos.y += ballInfo_.startPoint_.y * (MAX_RATIO - ballInfo_.ratio_);

	//X方向の強さが0以外のなら
	if (ballInfo_.strength_.x != ZERO)
	{
		nowPos.x = ((ballInfo_.v0_.x * sin(XMConvertToRadians(ANGLE)) * ballInfo_.ratio_) - (0.5f * GRAVITY * ballInfo_.ratio_ * ballInfo_.ratio_)) + nowPos.x * (MAX_RATIO - ballInfo_.ratio_);
		
		//負なら
		if(signbit(ballInfo_.strength_.x))
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * ballInfo_.ratio_)) * ballInfo_.strength_.x * 2);
		//正なら
		else 
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * ballInfo_.ratio_)) * ballInfo_.strength_.x / 2);
	}

	//移動前のポジション保存
	XMFLOAT3 beforePos = transform_->position_;

	//求めたポジション設定
	ARGUMENT_INITIALIZE(transform_->position_, nowPos);
	ballInfo_.pLine_->AddPosition(transform_->position_);

	//エフェクトのポジション更新
	ARGUMENT_INITIALIZE(VFX::GetEmitter(ballInfo_.hDropEffectName_)->data.position,transform_->position_);

	//進行ベクトルを求める
	ARGUMENT_INITIALIZE(ballInfo_.progressVector_, transform_->position_ - beforePos);

	//もし目標地点までの移動が終わったのなら
	if (ballInfo_.ratio_ >= MAX_RATIO)
	{
		//反射ベクトルを求めて進行ベクトルとする
		ARGUMENT_INITIALIZE(ballInfo_.progressVector_, XMVector3Reflect(ballInfo_.progressVector_, UP_VECTOR));
		
		//バウンド状態に
		ARGUMENT_INITIALIZE(ballInfo_.ballStatus_, BallStatus::BOUND_MOVE);
		
		//タイマーリセット
		Time::Reset(ballInfo_.hTime_);

		//正反射ベクトルの角度を求めたいので正反射ベクトルのYを無視したベクトルを作る
		XMVECTOR v = { XMVectorGetX(ballInfo_.progressVector_),ZERO,XMVectorGetZ(ballInfo_.progressVector_),ZERO };

		//正反射ベクトルの角度で放物線を描くと低い弾道になるので、定数分角度を増やす
		ARGUMENT_INITIALIZE(ballInfo_.firstAngle_,GetDot(ballInfo_.progressVector_, v) + XMConvertToRadians(ADD_ANGLE_VALUE));
	}
}

//バウンド移動
void Ball::BoundMove()
{
	//どのくらい時間がたったか取得
	float time = Time::GetTimef(ballInfo_.hTime_);

	//進行ベクトルを足して進める
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + XMVector3Normalize(ballInfo_.progressVector_) * 0.2f));
	
	//現在の位置を求める
	XMFLOAT3 nowPos = transform_->position_;
	nowPos.y = (ballInfo_.v0_.y * sin(ballInfo_.firstAngle_) * time) - (0.5f * GRAVITY * (time * time));
	transform_->position_.y = nowPos.y;

	//エフェクトのポジション更新
	ballInfo_.pLine_->AddPosition(transform_->position_);
	ARGUMENT_INITIALIZE(VFX::GetEmitter(ballInfo_.hDropEffectName_)->data.position, transform_->position_);

	//地面に着いてないのならこの先は処理しない
	if (transform_->position_.y > ZERO) return;

	//進行ベクトルを更新
	ARGUMENT_INITIALIZE(ballInfo_.progressVector_, XMVector3Reflect(ballInfo_.progressVector_, UP_VECTOR));
	
	//進行ベクトルの角度を更新
	XMVECTOR v = { XMVectorGetX(ballInfo_.progressVector_),ZERO,XMVectorGetZ(ballInfo_.progressVector_),ZERO };
	ballInfo_.firstAngle_ = GetDot(ballInfo_.progressVector_, v);

	//タイムリセット
	Time::Reset(ballInfo_.hTime_);

	//Yの強度を減らす
	ballInfo_.v0_.y *= 0.4f;

	//バウンドカウント増やす
	ballInfo_.boundCount_++;

	//2回バウンドしたら
	if (ballInfo_.boundCount_ == 2)
	{
		//次の目的地に移動するように
		ARGUMENT_INITIALIZE(ballInfo_.ballStatus_, BallStatus::PURPOSE_MOVE);
		ARGUMENT_INITIALIZE(ballInfo_.boundCount_,ZERO);

		Time::Reset(ballInfo_.hTime_);
		VFX::ForcedEnd(ballInfo_.hLandEffectName_);
		VFX::ForcedEnd(ballInfo_.hDropEffectName_);

		//打つ強さをランダムに取得
		HitStrength h =  GameManager::GetpPlayer()->GetRacket()->GetRamdomHitStrength();

		//リセット
		Reset(h.strength_.x, h.strength_.y,h.moveTime_,BasePointManager::GetRandomBasePointName());
	}
}

//プレイヤーがボールを持っている状態の時に呼ぶ関数
void Ball::PlayerHavingBall()
{
	ImGuiSet::DebugLog("tossup", VectorToFloat3(ballInfo_.tossUpVector_));
	ImGuiSet::DebugLog("flag", ballInfo_.isTossUp_);
	//もしトスアップしたのなら
	if (ballInfo_.isTossUp_)
	{
		//ボールを上げる
		ARGUMENT_INITIALIZE(transform_->position_,VectorToFloat3(transform_->position_ + ballInfo_.tossUpVector_));
		ballInfo_.tossUpVector_ -= XMVectorSet(ZERO, 0.0065f, ZERO, ZERO);

		//もし地面より下になったのなら
		if (transform_->GetPosition().y <= ZERO)
		{
			//トスアップのベクトルの値を元に戻す
			ARGUMENT_INITIALIZE(ballInfo_.tossUpVector_, TOSS_UP_VALUE);
			ARGUMENT_INITIALIZE(ballInfo_.isTossUp_, false);
			transform_->SetPositionY(ZERO);
		}
	}
}

//リセット(始点終点すべて再設定)
void Ball::Reset(float strengthX, float strengthY, float moveTime,string basePpointName)
{
	//向かうポジションを取得(少しランダムにずらす)
	XMFLOAT3 endPos = BasePointManager::GetBasePoint(basePpointName, ballInfo_.isGoToBasePoint_);

	//ラリー中の時だけ
	if (GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_RALLY)
	{
		endPos.x += ((rand() % 31 + 1) / 10) * (rand() % 3 - 1);
		endPos.z += ((rand() % 31 + 1) / 10) * (rand() % 3 - 1);

		//クランプする
		ARGUMENT_INITIALIZE(endPos.x, Clamp<float>(endPos.x, MAX_POS_X, MIN_POS_X));
		ARGUMENT_INITIALIZE(endPos.z, Clamp<float>(endPos.z, MAX_POS_Z, MIN_POS_Z));
	}

	//各情報再設定
	ARGUMENT_INITIALIZE(ballInfo_.startPoint_, transform_->position_);
	ARGUMENT_INITIALIZE(ballInfo_.endPoint_, endPos);
	ARGUMENT_INITIALIZE(ballInfo_.endPointDirection_, ballInfo_.endPoint_ - ballInfo_.startPoint_);
	ARGUMENT_INITIALIZE(ballInfo_.v0_.y, (0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(ballInfo_.v0_.x, (ballInfo_.endPoint_.x + 0.5f * GRAVITY) / sin(XMConvertToRadians(ANGLE)));
	ARGUMENT_INITIALIZE(ballInfo_.moveTime_, moveTime)
	ARGUMENT_INITIALIZE(ballInfo_.strength_.y, strengthY);
	ARGUMENT_INITIALIZE(ballInfo_.strength_.x, strengthX);
	Time::Reset(ballInfo_.hTime_);

	//ネットをしていたらボールの軌道を修正する
	//ネットのZ位置を通過するときの秒数を求める
	float t = abs(ballInfo_.startPoint_.z / abs(XMVectorGetZ(ballInfo_.endPointDirection_)));

	//ネットのZ位置を通過するときのY位置を求める
	float y = (ballInfo_.v0_.y * sin(XMConvertToRadians(ANGLE)) * t) - (0.5f * GRAVITY * pow(t, 2));

	//もしYの位置がネットの位置より低いなら
	if (y <= 1.2f)
	{
		//差分を求める
		float differential = 1.2f - y;

		//差分 + 定数分Yの強さを増やす
		ballInfo_.strength_.y += differential * 2.0f;
	}

	//着地エフェクト表示(同じ高さに表示すると被ってしまうので、少し上げる)
	XMFLOAT3 pos = ballInfo_.endPoint_;
	ARGUMENT_INITIALIZE(pos.y, LANDING_EFFECT_POS_Y);
	VFX::ForcedEnd(ballInfo_.hLandEffectName_);
    OtherEffectManager::LandingEffect(ballInfo_.hLandEffectName_,pos, ballInfo_.moveTime_);

	//雫みたいなエフェクト表示
	VFX::ForcedEnd(ballInfo_.hDropEffectName_);
	EffectManager::Draw(ballInfo_.hDropEffectName_, ballInfo_.dropEffectFilePath_, transform_->position_);

	//次の目的地に移動するように
	ARGUMENT_INITIALIZE(ballInfo_.ballStatus_, BallStatus::PURPOSE_MOVE);

	//逆にする
	ARGUMENT_INITIALIZE(ballInfo_.isGoToBasePoint_, !ballInfo_.isGoToBasePoint_);
}

//ボールトスアップするときのベクトルをリセット
void Ball::ResetBallTossUpVec() 
{
	GameManager::GetpBall()->SetTossUp(false);
	ARGUMENT_INITIALIZE(ballInfo_.tossUpVector_, TOSS_UP_VALUE);
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
	float t = (zPos - ballInfo_.startPoint_.z) / XMVectorGetZ(ballInfo_.endPointDirection_);

	XMFLOAT3 nowPos = VectorToFloat3(ballInfo_.startPoint_ + (ballInfo_.endPointDirection_ * t));

	//X方向の強さが0以外のなら
	if (ballInfo_.strength_.x != ZERO)
	{
		nowPos.x = ((ballInfo_.v0_.x * sin(XMConvertToRadians(ANGLE)) * t) - (0.5f * GRAVITY * t * t)) + nowPos.x * (MAX_RATIO - t);

		//負なら
		if (signbit(ballInfo_.strength_.x))
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * t)) * ballInfo_.strength_.x * 2);
		//正なら
		else
			nowPos.x += (sin(XMConvertToRadians(PI_DEGREES * t)) * ballInfo_.strength_.x / 2);
	}

	return nowPos;
}