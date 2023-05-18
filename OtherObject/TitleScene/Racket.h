#pragma once
#include "../../Base/NormalObject.h"

//ボールを打つ時の球
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

	//ボールを打つ時の球
	Type type_;

public:

	//コンストラクタ
	Racket(GameObject* parent, std::string modelPath, std::string name);
	Racket(GameObject* parent);

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override;

	//デストラクタ
	~Racket() {};
};

