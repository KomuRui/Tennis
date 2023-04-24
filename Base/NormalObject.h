#pragma once
#include "../Engine/GameObject/GameObject.h"

/// <summary>
/// ただ3Dオブジェクトを表示する基底クラス
/// </summary>
class NormalObject : public GameObject
{
protected:

	///////////////必要な情報///////////////////

	int hModel_;                     //モデル番号
	std::string modelNamePath_;      //ファイルネームパス

public:

	//コンストラクタ
	NormalObject(GameObject* parent, std::string modelPath, std::string name);

	//デストラクタ
	virtual ~NormalObject() {};
	
	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	/// <summary>
	/// 継承先用のUpdate
	/// </summary>
	virtual void ChildUpdate() {};

	/// <summary>
	/// 継承先用の初期化
	/// </summary>
	virtual void ChildInitialize() {};

	/// <summary>
	/// 継承先用の描画
	/// </summary>
	virtual void ChildDraw() {};

	/// <summary>
	/// 継承先用の更新の前に一度だけ呼ばれる関数
	/// </summary>
	virtual void ChildStartUpdate() {};

	/// <summary>
	/// 継承先用の開放
	/// </summary>
	virtual void ChildRelease() {};

	/// <summary>
	/// 継承先用のコライダーに当たった時に呼ばれる関数
	/// </summary>
	/// <param name="pTarget">当たったオブジェクトのポインタ</param>
	virtual void OnCollision(GameObject* pTarget) override {};

	/// <summary>
	/// 継承先用の指定した時間で呼ばれるメソッド
	/// </summary>
	virtual void TimeMethod() override {};


	////////////////////////////ゲッター・セッター////////////////////////////////

	int GetModelNum() { return hModel_; }
};

