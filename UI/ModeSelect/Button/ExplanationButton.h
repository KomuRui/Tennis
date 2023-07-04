#pragma once
#include "../../Button/EasingButton.h"

/// <summary>
/// あそびかたボタン
/// </summary>
class ExplanationButton : public EasingButton
{

	int hSelectPict_;    //選択されているときの画像番号
	int hNotSelectPict_; //選択されていないときの画像番号

public:

	//コンストラクタ
	ExplanationButton(GameObject* parent, std::string modelPath, std::string name);

	////////////////////オーバーライドする関数/////////////////////////

	/// <summary>
	/// 初期化
	/// </summary>
	void ChildInitialize() override;

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

