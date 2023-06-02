#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "../Component.h"
using namespace DirectX;

//クラスの前方宣言
class GameObject;
class BoxCollider;
class SphereCollider;

//あたり判定のタイプ
enum ColliderType
{
	COLLIDER_BOX,		//箱型
	COLLIDER_CIRCLE		//球体
};

//-----------------------------------------------------------
//あたり判定を管理するクラス
//-----------------------------------------------------------
template<class T>
class Collider : public Component
{
	//それぞれのクラスのprivateメンバにアクセスできるようにする
	friend class BoxCollider;
	friend class SphereCollider;

	//関数ポインタ
 	void (T::*OnCollision)(GameObject*); //当たった時に呼ばれる関数のポインタ
 	void (T::*OutCollision)(GameObject*);//当たらなくなった時に呼ばれる関数のポインタ

protected:

	ColliderType	type_;			//種類
	XMFLOAT3		center_;		//中心位置（ゲームオブジェクトの原点から見た位置）
	XMFLOAT3		size_;			//判定サイズ（幅、高さ、奥行き）
	int				hDebugModel_;	//デバッグ表示用のモデルのID
	bool            rotateflag_;    //コライダーが回転するかどうか

public:

	//コンストラクタ
	Collider();

	//デストラクタ
	virtual ~Collider();

	///////////////////////////オーバライドする関数////////////////////////////////

	//描画
	void Draw() override;

	/////////////////////////////////接触判定関数////////////////////////////////////////

	//衝突判定
	//引数：pTarget	衝突してるか調べる相手
	void Collision(GameObject* pTarget);

	//接触判定（継承先のSphereColliderかBoxColliderでオーバーライド）
	//引数：target	相手の当たり判定
	//戻値：接触してればtrue
	virtual bool IsHit(Collider* target) = 0;

	//箱型同士の衝突判定
	//引数：boxA	１つ目の箱型判定
	//引数：boxB	２つ目の箱型判定
	//戻値：接触していればtrue
	bool IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB);

	//箱型と球体の衝突判定
	//引数：box	箱型判定
	//引数：sphere	２つ目の箱型判定
	//戻値：接触していればtrue
	bool IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere);

	//球体同士の衝突判定
	//引数：circleA	１つ目の球体判定
	//引数：circleB	２つ目の球体判定
	//戻値：接触していればtrue
	bool IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB);

	//テスト表示用の枠を描画
	//引数：position	オブジェクトの位置
	void Draw(XMFLOAT3 position, XMFLOAT3 rotate);

	///////////////////////////セッター・ゲッター////////////////////////////////

	//当たった時に呼ばれる関数ポインタをセット
	void SetHitFunc(void(T::*func)(GameObject*)) { OnCollision = func; }

	//当たらなくなった時に呼ばれる関数のポインタをセット
	void SetHitOutFunc(void(T::*func)(GameObject*)) { OutCollision = func; }

	//セッター
	void SetPos(XMFLOAT3 pos) { center_ = pos; }

	//セッター
	void SetSize(XMFLOAT3 scale) { size_ = scale; }

	//セッター
	void SetSizePos(XMFLOAT3 scale, XMFLOAT3 pos) { size_ = scale; center_ = pos; }

	//Get
	XMFLOAT3 Getcenter() { return center_; }

	//半径ゲット
	float GetRadius() { return size_.x; }
};

