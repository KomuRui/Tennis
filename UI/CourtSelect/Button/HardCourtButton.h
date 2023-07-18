#pragma once
#include "../../Button/EasingButton.h"

/// <summary>
/// ハードコートボタン
/// </summary>
class HardCourtButton : public EasingButton
{
	std::unique_ptr<EasingMove> easingSelectPict_; //選択されているときの画像のイージング用
	Transform tSelectPict_;                        //選択されているときの画像のトランスフォーム
	Transform tCourtInfoPict_;                     //コート情報の画像のトランスフォーム
	int hSelectPict_;                              //選択されているときの画像番号
	int hTextPict_;								   //文字画像番号
	int hCourtInfoPict_;                           //コート情報の画像番号

public:

	//コンストラクタ
	HardCourtButton(GameObject* parent, std::string modelPath, std::string name);

	////////////////////オーバーライドする関数/////////////////////////

	/// <summary>
	/// 初期化
	/// </summary>
	void ChildInitialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void EasingButtonChileUpdate() override;

	/// <summary>
	/// 描画
	/// </summary>
	void ChildDraw() override;

	/// <summary>
	/// ボタンが押されたら何するか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
	void IsButtonPush() override;

	/// <summary>
	/// ボタンが選択された瞬間に何をするか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
	void IsButtonSelect() override;

	/// <summary>
	/// ボタンが選択解除された瞬間に何をするか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
	void IsButtonSelectRelease() override;
};

