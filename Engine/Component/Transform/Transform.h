#pragma once
#include "../Component.h"
#include <DirectXMath.h>

using namespace DirectX;

class GameObject;

/// <summary>
/// トランスフォームコンポーネント
/// </summary>
class Transform : public Component
{

public:

	XMMATRIX matTranslate_;	//移動行列
	XMMATRIX matRotate_;	//回転行列	
	XMMATRIX matScale_;		//拡大行列
	XMFLOAT3 position_;		//位置
	XMFLOAT3 rotate_;		//向き
	XMFLOAT3 scale_;		//拡大率
	XMMATRIX matAxisRotate_;//軸回転行列	
	bool     isAxisRotate_; //軸回転を使うかどうか

	//コンストラクタ
	Transform();

	//デストラクタ
	~Transform();

	//各行列の計算
	//引数：なし
	//戻値：なし
	void Calclation();

	//ワールド行列を取得
	//引数：なし
	//戻値：その時点でのワールド行列
	XMMATRIX GetWorldMatrix();

	/// <summary>
	/// 親のワールド行列を取得
	/// </summary>
	/// <returns>親のワールド行列</returns>
	XMMATRIX GetParentWorldMatrix();

	/////////////////////////////////////セッター・ゲッター//////////////////////////////////////////

	XMFLOAT3 GetPosition() { return position_; }
	XMFLOAT3 GetRotate() { return rotate_; }
	XMFLOAT3 GetScale() { return scale_; }
	XMFLOAT3 GetWorldPosition();
	XMFLOAT3 GetWorldRotate();
	XMFLOAT3 GetWorldScale();
	XMMATRIX GetWorldRotateMatrix();
	Transform* GetTransform() { return this; }
	void SetTransform(Transform* t);
	void SetPosition(XMFLOAT3 position) { position_ = position; }
	void SetPosition(float x, float y, float z) { SetPosition(XMFLOAT3(x, y, z)); }
	void SetPositionX(float x) { SetPosition(x, position_.y, position_.z); }
	void SetPositionY(float y) { SetPosition(position_.x, y, position_.z); }
	void SetPositionZ(float z) { SetPosition(position_.x, position_.y, z); }
	void SetRotate(XMFLOAT3 rotate) { rotate_ = rotate; }
	void SetRotate(float x, float y, float z) { SetRotate(XMFLOAT3(x, y, z)); }
	void SetRotateX(float x) { SetRotate(x, rotate_.y, rotate_.z); }
	void SetRotateY(float y) { SetRotate(rotate_.x, y, rotate_.z); }
	void SetRotateZ(float z) { SetRotate(rotate_.x, rotate_.y, z); }
	void SetScale(XMFLOAT3 scale) { scale_ = scale; }
	void SetScale(float x, float y, float z) { SetScale(XMFLOAT3(x, y, z)); }
};

