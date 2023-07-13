#pragma once
#pragma once
#include "../../Button/EasingButton.h"
#include "../CharaSelectSceneUI.h"

/// <summary>
/// ボスボタン
/// </summary>
class BossButton : public EasingButton
{
	//UI統括してるやつ
	CharaSelectSceneUI* charaSelectSceneUI;

	//キャラ画像
	int hCharaPict_;
	std::unique_ptr<Transform> tCharaPict_;        //トランスフォーム
	std::unique_ptr<EasingMove> easingCharaPict_;  //イージング用

public:

	//コンストラクタ
	BossButton(GameObject* parent, std::string modelPath, std::string name);

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

