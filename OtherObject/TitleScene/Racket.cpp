#include "Racket.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Engine/Collider/SphereCollider.h"


//定数
namespace
{		
	////////////////コライダー///////////////////

	static const float    COLLIDER_SIZE = 0.3f;               //コライダーのサイズ
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
	
	XMFLOAT3 a = Model::GetBonePosition(hModel_, "Base");
	a.z += 1.1f;
	//当たり判定
	SphereCollider* collision = new SphereCollider(a, COLLIDER_SIZE);
	AddCollider(collision);

}

//更新
void Racket::ChildUpdate()
{
}
