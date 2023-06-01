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
};

