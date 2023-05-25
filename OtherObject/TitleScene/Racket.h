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

//ストローク
enum class Stroke{
	FOREHAND,  //フォア
	BACKHAND,  //バック
	MAX
};

//打つ時の必要な情報
struct HitStrength {
	XMFLOAT2 strength_;   //強さ(XとY方向の)
	float moveTime_;	  //始点から終点まで動く時間
};

/// <summary>
/// ラケット
/// </summary>
class Racket : public NormalObject
{

	map<Type, XMFLOAT4> lineColor_;         //球種ごとのライン色
	map<Type, string> effectFilePath_;      //球種ごとのエフェクトのファイルパス
	map<Type, HitStrength> hitStrength_;    //球種ごとの打つ時の強さ
	Stroke stroke_;                         //ストローク
	Type type_;						        //球種
	XMFLOAT3 colliderPos_;                  //コライダーのポジション
	float ratio_;                           //倍率

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

	/// <summary>
	/// 入力に対する基準点のポイントの名前を取得
	/// </summary>
	/// <returns></returns>
	string GetInputBasePoint();

	//当たり判定
	void OnCollision(GameObject* pTarget) override;

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	/// <summary>
	/// 型を設定
	/// </summary>
	/// <param name="t">設定したい型</param>
	void SetType(Type t) { type_ = t; }

	/// <summary>
	/// ストロークを設定
	/// </summary>
	/// <param name="t">設定したいストローク</param>
	void SetStroke(Stroke t) { stroke_ = t; }

	/// <summary>
	/// 倍率を設定
	/// </summary>
	/// <param name="ratio">設定したい倍率</param>
	void SetRatio(float ratio) { ratio_ = ratio; }

	/// <summary>
	/// 倍率を取得
	/// </summary>
	/// <returns>倍率</returns>
	float GetRatio() { return ratio_; }

	/// <summary>
	/// ランダムに打つ時の強さを取得
	/// </summary>
	/// <returns>打つ時の強さ</returns>
	HitStrength GetRamdomHitStrength();

	/// <summary>
	/// タイプごとの色を取得
	/// </summary>
	/// <returns>タイプごとの色</returns>
	XMFLOAT4 GetTypeColor() { return lineColor_[type_]; }
};

