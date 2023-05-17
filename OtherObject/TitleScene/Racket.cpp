#include "Racket.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Engine/Collider/SphereCollider.h"
#include "../../Engine/Collider/BoxCollider.h"


//定数
namespace
{		
	////////////////コライダー///////////////////

	static const int      BASE_ADD_ANGLE_VALUE = -110;   //ベースに加算する角度の値
	static const int      EDGE_ADD_ANGLE_VALUE = -180;   //端に加算する角度の値
	static const float    COLLIDER_SIZE_X = 1.0f;        //コライダーのサイズ
	static const float    COLLIDER_SIZE_Y = 1.5f;        //コライダーのサイズ
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
	

	ARGUMENT_INITIALIZE(transform_.position_, XMFLOAT3(0.643,0.835,0.011));
		
	//当たり判定
	BoxCollider * collision = new BoxCollider({ ZERO,ZERO,ZERO }, { COLLIDER_SIZE_X,COLLIDER_SIZE_Y,COLLIDER_SIZE_Z });
	AddCollider(collision);
}

//更新
void Racket::ChildUpdate()
{
	//ラケットの端のポジションを求める(骨のポジションおかしいので力ずくで回転)
	XMFLOAT3 edgePos = VectorToFloat3(Model::GetBonePosition(hModel_, "Edge") - GetParent()->GetPosition());
	edgePos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&edgePos), XMMatrixRotationY(XMConvertToRadians(1))));

	//コライダーのポジション求めて新しく設定(骨のポジションおかしいので力ずくで回転)
	XMFLOAT3 colliderPos = VectorToFloat3(Model::GetBonePosition(hModel_, "Base") - GetParent()->GetPosition());
	colliderPos = VectorToFloat3(XMVector3TransformCoord(XMLoadFloat3(&colliderPos), XMMatrixRotationY(XMConvertToRadians(BASE_ADD_ANGLE_VALUE))));
	SetPosCollider(colliderPos);
}
