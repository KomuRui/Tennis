#include "Racket.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Engine/Collider/SphereCollider.h"
#include "../../Engine/Collider/BoxCollider.h"
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
	:NormalObject(parent, modelPath, name)
{
}

Racket::Racket(GameObject* parent)
	:NormalObject(parent, "Racket/Normal.fbx", "Racket")
{}

//初期化
void Racket::ChildInitialize()
{
	//明るさ最大値に設定
	Model::SetBrightness(hModel_, 1.0f);
	
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
	XMFLOAT3 colliderPos = VectorToFloat3(Model::GetBonePosition(hModel_, "Base") - GetParent()->GetPosition() - transform_.position_);
	colliderPos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos), XMMatrixInverse(nullptr, XMMatrixTranslation(edgePos.x, ZERO, edgePos.z)) *  XMMatrixRotationY(XMConvertToRadians(BASE_ADD_ANGLE_VALUE))));
	colliderPos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos), XMMatrixTranslation(edgePos.x, ZERO, edgePos.z)));
	SetPosCollider(colliderPos);
}

//当たり判定
void Racket::OnCollision(GameObject* pTarget)
{
	//ボールに当たってないか、打つ動作をしていないのならこの先の処理はしない
	if (pTarget->GetObjectName() != "Ball" || !((PlayerBase*)GetParent())->pState_->IsHitMove()) return;

	//ボールを次のコートへ
	((Ball*)pTarget)->Reset(false);
}