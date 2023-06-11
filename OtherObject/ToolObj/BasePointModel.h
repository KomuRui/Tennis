#pragma once
#include "../../Base/NormalObject.h"

/// <summary>
/// ボールが飛んでいく基準点に配置するモデル
/// </summary>
class BasePointModel : public NormalObject
{
	//基準点の名前
	string basePointName_;

	//プレイヤー1のコートかどうか
	bool isPlayer1CourtType_;

	//サーブレシーブの基準点かどうか
	bool isServeReceiveBasePoint_;

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
	/// プレイヤー1のコートかどうかセット
	/// </summary>
	/// <param name="flag">trueならプレイヤー1のコートにセット</param>
	void SetPlayer1CourtType(bool flag) { isPlayer1CourtType_ = flag; }

	/// <summary>
	/// プレイヤー1のコートかどうか取得
	/// </summary>
	/// <returns>trueならプレイヤータイプ</returns>
	bool isPlaye1CourtType() { return isPlayer1CourtType_; }

	/// <summary>
	/// サーブレシーブ時の基準点かどうかセット
	/// </summary>
	/// <param name="flag">trueならサーブレシーブ時の基準点にセット</param>
	void SetServeReceiveBasePoint(bool flag) { isServeReceiveBasePoint_ = flag; }

	/// <summary>
	/// サーブレシーブ時の基準点かどうか取得
	/// </summary>
	/// <returns>trueならサーブレシーブ時の基準点</returns>
	bool isServeReceiveBasePoint() { return isServeReceiveBasePoint_; }

	/// <summary>
	/// 基準点の名前を取得
	/// </summary>
	/// <returns>基準点の名前</returns>
	string GetBasePointName() { return basePointName_; }
};

