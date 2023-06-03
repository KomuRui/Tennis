#include "Racket.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Manager/EffectManager/EffectManager.h"
#include "../../Player/PlayerBase.h"
#include "Ball.h"

//定数
namespace
{		
	static const int RACKET_START_ROTATION_ANGLE = -185; //ラケットの開始角度

	////////////////コライダー///////////////////

	static const int      BASE_ADD_ANGLE_VALUE = -80;    //ベースに加算する角度の値
	static const float    COLLIDER_SIZE_X = 2.0f;        //コライダーのサイズ
	static const float    COLLIDER_SIZE_Y = 2.0f;        //コライダーのサイズ
	static const float    COLLIDER_SIZE_Z = 2.0f;        //コライダーのサイズ
}

//コンストラクタ
Racket::Racket(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), type_(Type::FLAT), stroke_(Stroke::FOREHAND), colliderPos_(ZERO, ZERO, ZERO), ratio_(1.0)
{
}

Racket::Racket(GameObject* parent)
	:NormalObject(parent, "Racket/Normal.fbx", "Racket"), type_(Type::FLAT), stroke_(Stroke::FOREHAND), colliderPos_(ZERO, ZERO, ZERO), ratio_(1.0)
{}

//初期化
void Racket::ChildInitialize()
{
	//明るさ最大値に設定
	ModelManager::SetBrightness(hModel_, 1.0f);
	
	//球種ごとのボールの色を設定
	ARGUMENT_INITIALIZE(lineColor_[Type::FLAT], XMFLOAT4(1, 0.5f, 1, 1));
	ARGUMENT_INITIALIZE(lineColor_[Type::LOB], XMFLOAT4(1, 1, ZERO, 1));
	ARGUMENT_INITIALIZE(lineColor_[Type::SLICE], XMFLOAT4(ZERO, 0.5f, 1, 1));
	ARGUMENT_INITIALIZE(lineColor_[Type::TOP_SPIN], XMFLOAT4(1, ZERO, ZERO, 1));

	//球種ごとのエフェクトのファイルパスを設定
	ARGUMENT_INITIALIZE(hitEffectFilePath_[Type::FLAT], "Effect/FlatEffect.txt");
	ARGUMENT_INITIALIZE(hitEffectFilePath_[Type::LOB], "Effect/LobEffect.txt");
	ARGUMENT_INITIALIZE(hitEffectFilePath_[Type::SLICE], "Effect/SliceEffect.txt");
	ARGUMENT_INITIALIZE(hitEffectFilePath_[Type::TOP_SPIN], "Effect/TopSpinEffect.txt");

	//球種ごとのエフェクトのファイルパスを設定
	ARGUMENT_INITIALIZE(dropEffectFilePath_[Type::FLAT], "Effect/FlatDrop.txt");
	ARGUMENT_INITIALIZE(dropEffectFilePath_[Type::LOB], "Effect/LobDrop.txt");
	ARGUMENT_INITIALIZE(dropEffectFilePath_[Type::SLICE], "Effect/SliceDrop.txt");
	ARGUMENT_INITIALIZE(dropEffectFilePath_[Type::TOP_SPIN], "Effect/TopSpinDrop.txt");

	//打つ時の強さを格納する用
	HitStrength h;

	//フラット
	ARGUMENT_INITIALIZE(h.strength_.x, ZERO);
	ARGUMENT_INITIALIZE(h.strength_.y, 1.0f);
	ARGUMENT_INITIALIZE(h.moveTime_, 1.0f);
	ARGUMENT_INITIALIZE(hitStrength_[Type::FLAT],h);
	
	//ロブ
	ARGUMENT_INITIALIZE(h.strength_.y, 4.0f);
	ARGUMENT_INITIALIZE(h.moveTime_, 1.6f);
	ARGUMENT_INITIALIZE(hitStrength_[Type::LOB],h);

	//トップスピン
	ARGUMENT_INITIALIZE(h.strength_.y, 1.8f);
	ARGUMENT_INITIALIZE(h.moveTime_, 0.9f);
	ARGUMENT_INITIALIZE(hitStrength_[Type::TOP_SPIN],h);

	//スライス
	ARGUMENT_INITIALIZE(h.strength_.x, 1.0f);
	ARGUMENT_INITIALIZE(h.strength_.y, 1.4f);
	ARGUMENT_INITIALIZE(h.moveTime_, 1.0f);
	ARGUMENT_INITIALIZE(hitStrength_[Type::SLICE],h);

	//Mayaで原点を0,0,0に設定した分戻す
	ARGUMENT_INITIALIZE(transform_->position_, XMFLOAT3(0.643f,0.835f,0.011f));
		
	//開始角度を設定
	transform_->SetRotateY(RACKET_START_ROTATION_ANGLE);

	//当たり判定
	box1_ = AddComponent<BoxCollider>();
	box1_->SetPos({ ZERO,ZERO,ZERO });
	box1_->SetSize({ COLLIDER_SIZE_X,COLLIDER_SIZE_Y,COLLIDER_SIZE_Z });
	box1_->SetHitFunc(static_cast<BoxCollider::FunctionPtr>(&Racket::HitColliderFunc));
	SetShadow(true);
}

//更新
void Racket::ChildUpdate()
{
	//ラケットの端のポジションを求める
	XMFLOAT3 edgePos = VectorToFloat3(ModelManager::GetBonePosition(hModel_, "Edge") - GetParent()->GetComponent<Transform>()->GetPosition() - transform_->position_);
	
	//コライダーのポジション求めて新しく設定(骨のポジションおかしいので力ずくで回転)
	colliderPos_ = VectorToFloat3(ModelManager::GetBonePosition(hModel_, "Base") - GetParent()->GetComponent<Transform>()->GetPosition() - transform_->position_);
	colliderPos_ = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos_), XMMatrixInverse(nullptr, XMMatrixTranslation(edgePos.x, ZERO, edgePos.z)) *  XMMatrixRotationY(XMConvertToRadians(BASE_ADD_ANGLE_VALUE))));
	colliderPos_ = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos_), XMMatrixTranslation(edgePos.x, ZERO, edgePos.z)));
	box1_->SetPos(colliderPos_);
}

//入力に対する基準点のポイントの名前を取得
string Racket::GetInputBasePoint()
{
	//最終的に返す文字列
	string name = "";

	//Lスティックの傾きを取得
	XMFLOAT3 stickL = Input::GetPadStickL();

	if (stickL.y > 0.1f)
		name += "Back_";
	else if (stickL.y < -0.1f)
		name += "Front_";
	else
		name += "Center_";

	if (stickL.x > 0.1f)
		name += "L";
	else if (stickL.x < -0.1f)
		name += "R";
	else
		name += "C";

	return name;
}

//当たり判定
void Racket::HitColliderFunc(GameObject* pTarget)
{
	//ボールに当たってないか、打つ動作をしていないのならこの先の処理はしない
	if (pTarget->GetObjectName() != "Ball" || !((PlayerBase*)GetParent())->pState_->IsHitMove() || ((Ball*)pTarget)->isGoToPlayerBasePoint()) return;

	//ヒットストップ演出(動きを止める)
	Leave();
	pTarget->Leave();

	//Playerも敵も0.1秒後に動き出す
	SetTimeMethod(0.1f);
	pTarget->SetTimeMethod(0.1f);

	//保存しておく
	float s = hitStrength_[type_].strength_.x;

	//バックハンドならXの強さを逆にする
	if (stroke_ == Stroke::BACKHAND)
		hitStrength_[type_].strength_.x *= -1;

	//ボールの軌跡色を指定
	((Ball*)pTarget)->SetBallLineColor(lineColor_[type_]);
	((Ball*)pTarget)->SetBallDropEffectFilePath(dropEffectFilePath_[type_]);

	//ボールを次のコートへ
	((Ball*)pTarget)->Reset(hitStrength_[type_].strength_.x, hitStrength_[type_].strength_.y, hitStrength_[type_].moveTime_ * ratio_,false, GetInputBasePoint());

	//エフェクト表示
	EffectManager::Draw("HitEffect",hitEffectFilePath_[type_], ((Ball*)pTarget)->GetComponent<Transform>()->GetPosition());

	//元に戻す
	ARGUMENT_INITIALIZE(hitStrength_[type_].strength_.x,s);
}

//何かのオブジェクトに当たった時に呼ばれる関数
void Racket::TimeMethod()
{
	Enter();
}

//ランダムに打つ時の強さを取得
HitStrength Racket::GetRamdomHitStrength() {


	//ボールのポインタを保存しておく
	Ball* pBall = ((Ball*)FindObject("Ball"));

	//ランダムな数を取得
	int num = Random(ZERO, static_cast<int>(Type::MAX) - 1);

	//数字によって返す値を変更
	switch (num)
	{

	//フラット
	case static_cast<int>(Type::FLAT):

		pBall->SetBallLineColor(lineColor_[Type::FLAT]);
		return hitStrength_[Type::FLAT];

	//ロブ
	case static_cast<int>(Type::LOB):

		pBall->SetBallLineColor(lineColor_[Type::LOB]);
		return hitStrength_[Type::LOB];

	//スライス
	case static_cast<int>(Type::SLICE):

		pBall->SetBallLineColor(lineColor_[Type::SLICE]);
		return hitStrength_[Type::SLICE];

	//トップスピン
	case static_cast<int>(Type::TOP_SPIN):

		pBall->SetBallLineColor(lineColor_[Type::TOP_SPIN]);
		return hitStrength_[Type::TOP_SPIN];
	default:

		pBall->SetBallLineColor(lineColor_[Type::FLAT]);
		return hitStrength_[Type::FLAT];
	}
}