#pragma once
#include "../../Base/NormalObject.h"
#include <map>

//球種
enum class Type {
	FLAT,      //フラット
	TOP_SPIN,  //トップスピン
	SLICE,     //スライス
	LOB,       //ロブ
	MAX
};

/// <summary>
/// ラケット
/// </summary>
class Racket : public NormalObject
{

	map<Type, XMFLOAT4> lineColor_;     //球種ごとのライン色
	map<Type, string> effectFilePath_;  //球種ごとのファイルパス
	Type type_;						    //球種
	XMFLOAT3 colliderPos_;              //コライダーのポジション

public:

	//コンストラクタ
	Racket(GameObject* parent, std::string modelPath, std::string name);
	Racket(GameObject* parent);

	//デストラクタ
	~Racket() {};

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override;

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	/// <summary>
	/// 型を設定
	/// </summary>
	/// <param name="t">設定したい型</param>
	void SetType(Type t) { type_ = t; }
};

