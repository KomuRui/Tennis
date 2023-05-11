#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// ボールが飛んでいく基準点に配置するモデル
/// </summary>
class BasePointModel : public NormalObject
{
	//基準点の名前
	string basePointName_;

	//プレイヤータイプかどうか
	bool isPlayerType_;

public:

	//コンストラクタ
	BasePointModel(GameObject* parent, std::string modelPath, std::string name);
	BasePointModel(GameObject* parent);

	//デストラクタ
	~BasePointModel() {};

	//初期化
	void ChildInitialize() override;

	//描画
	void Draw() override;

	//二つ目のウィンドウの描画
	void TwoWindowDraw() override;

	//基準点の名前セット
	void SetBasePointName(string name) { basePointName_ = name; }

	/// <summary>
	/// プレイヤータイプかどうかセット
	/// </summary>
	/// <param name="flag">trueならプレイヤータイプにセット</param>
	void SetPlayerType(bool flag) { isPlayerType_ = flag; }

	/// <summary>
	/// プレイヤータイプかどうか取得
	/// </summary>
	/// <returns>trueならプレイヤータイプ</returns>
	bool isPlayerType() { return isPlayerType_; }

	/// <summary>
	/// 基準点の名前を取得
	/// </summary>
	/// <returns>基準点の名前</returns>
	string GetBasePointName() { return basePointName_; }
};

