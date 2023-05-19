#include "Racket.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Engine/Collider/SphereCollider.h"
#include "../../Engine/Collider/BoxCollider.h"
#include "../../Manager/EffectManager/EffectManager.h"
#include "../../Player/PlayerBase.h"
#include "Ball.h"

//定数
namespace
{		
	static const int RACKET_START_ROTATION_ANGLE = -185; //ラケットの開始角度

	////////////////コライダー///////////////////

	static const int      BASE_ADD_ANGLE_VALUE = -80;    //ベースに加算する角度の値
	static const float    COLLIDER_SIZE_X = 1.5f;        //コライダーのサイズ
	static const float    COLLIDER_SIZE_Y = 2.0f;        //コライダーのサイズ
	static const float    COLLIDER_SIZE_Z = 1.0f;        //コライダーのサイズ
}

//コンストラクタ
Racket::Racket(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), type_(Type::FLAT), colliderPos_(ZERO, ZERO, ZERO)
{
}

Racket::Racket(GameObject* parent)
	:NormalObject(parent, "Racket/Normal.fbx", "Racket"), type_(Type::FLAT), colliderPos_(ZERO, ZERO, ZERO)
{}

//初期化
void Racket::ChildInitialize()
{
	//明るさ最大値に設定
	Model::SetBrightness(hModel_, 1.0f);
	
	//球種ごとのボールの色を設定
	ARGUMENT_INITIALIZE(lineColor_[Type::FLAT], XMFLOAT4(1, ZERO, 1, 1));
	ARGUMENT_INITIALIZE(lineColor_[Type::LOB], XMFLOAT4(1, 1, ZERO, 1));
	ARGUMENT_INITIALIZE(lineColor_[Type::SLICE], XMFLOAT4(ZERO, 1, 1, 1));
	ARGUMENT_INITIALIZE(lineColor_[Type::TOP_SPIN], XMFLOAT4(1, ZERO, ZERO, 1));

	//Mayaで原点を0,0,0に設定した分戻す
	ARGUMENT_INITIALIZE(transform_.position_, XMFLOAT3(0.643f,0.835f,0.011f));
		
	//開始角度を設定
	SetRotateY(RACKET_START_ROTATION_ANGLE);

	//当たり判定
	BoxCollider * collision = new BoxCollider({ ZERO,ZERO,ZERO }, { COLLIDER_SIZE_X,COLLIDER_SIZE_Y,COLLIDER_SIZE_Z });
	AddCollider(collision);
}

//更新
void Racket::ChildUpdate()
{
	//ラケットの端のポジションを求める
	XMFLOAT3 edgePos = VectorToFloat3(Model::GetBonePosition(hModel_, "Edge") - GetParent()->GetPosition() - transform_.position_);
	
	//コライダーのポジション求めて新しく設定(骨のポジションおかしいので力ずくで回転)
	colliderPos_ = VectorToFloat3(Model::GetBonePosition(hModel_, "Base") - GetParent()->GetPosition() - transform_.position_);
	colliderPos_ = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos_), XMMatrixInverse(nullptr, XMMatrixTranslation(edgePos.x, ZERO, edgePos.z)) *  XMMatrixRotationY(XMConvertToRadians(BASE_ADD_ANGLE_VALUE))));
	colliderPos_ = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos_), XMMatrixTranslation(edgePos.x, ZERO, edgePos.z)));
	SetPosCollider(colliderPos_);
}

//当たり判定
void Racket::OnCollision(GameObject* pTarget)
{
	//ボールに当たってないか、打つ動作をしていないのならこの先の処理はしない
	if (pTarget->GetObjectName() != "Ball" || !((PlayerBase*)GetParent())->pState_->IsHitMove()) return;

	//ヒットストップ演出(動きを止める)
	Leave();
	pTarget->Leave();

	//Playerも敵も0.1秒後に動き出す
	SetTimeMethod(0.1f);
	pTarget->SetTimeMethod(0.1f);

	//ボールの軌跡色を指定
	((Ball*)pTarget)->SetBallLineColor(lineColor_[type_]);

	//ボールを次のコートへ
	((Ball*)pTarget)->Reset(false);

	//ボールのポジションを修正
	XMFLOAT3 pos = VectorToFloat3(colliderPos_ + GetParent()->GetPosition());
	ARGUMENT_INITIALIZE(pos.y, COLLIDER_SIZE_Y / 2.0f);
	((Ball*)pTarget)->SetPosition(pos);

	//エフェクト表示
	EffectManager::Draw("Effect/TopSpinEffect.txt", pos);
}

//何かのオブジェクトに当たった時に呼ばれる関数
void Racket::TimeMethod()
{
	Enter();
}