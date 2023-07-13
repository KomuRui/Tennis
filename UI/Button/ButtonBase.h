#pragma once
#include "../ImageBase.h"

/// <summary>
/// ボタンクラス
/// </summary>
class ButtonBase : public ImageBase
{
protected:

	//ボタンが選択されているとき何をするかの関数ポインタ
	void(*ButtonSelectingFunc)(void);

	//押したときの関数ポインタ
	void(*OnPushFunc)(void);

	//ボタン選択された瞬間に呼ぶ関数ポインタ
	void(*ButtonSelectFunc)(void);

	//ボタンが選択解除された瞬間に呼ぶ関数ポインタ
	void (*ButtonSelectReleaseFunc)(void);
	
	//自分の前に選択されていたボタンのポジションを格納
	XMFLOAT3 beforeButtonSelectPos_;

	//何番のコントローラーに押されたのか
	int numController_;

	//選択されているかどうか
	bool isSelect_;

	//動き中かどうか
	bool isMove_;

	//一回でも押したかどうか
	bool isPush_;

	//選択中が変更されるかどうか
	bool isSelectNoChange_;

public:

	//コンストラクタ
	ButtonBase(GameObject* parent, std::string modelPath, std::string name);
	
	////////////////////オーバーライドする関数/////////////////////////

	//更新
	void ChildUpdate() override;

	//初期化
	virtual void ChildInitialize() override {};

	//描画
	virtual void ChildDraw() override {};

	/////////////////////////////関数////////////////////////////////

	/// <summary>
	/// 継承先用の更新
	/// </summary>
	virtual void ChildButtonUpdate() {};

	/// <summary>
	/// ボタンが選択されているとき何をするか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
	virtual void IsButtonSelecting() {};

	/// <summary>
	/// ボタンが押されたら何するか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
	virtual void IsButtonPush() {};

	/// <summary>
	/// ボタンが選択された瞬間に何をするか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
	virtual void IsButtonSelect() {};

	/// <summary>
	/// ボタンが選択解除された瞬間に何をするか
	/// </summary>
	/// <param name="p">実行したい関数ポインタ</param>
	virtual void IsButtonSelectRelease() {};

	//////////////////////////セットゲット関数/////////////////////////////

	/// <summary>
	/// 選択されているかをセット 
	/// </summary>
	/// <param name="flag">trueなら選択されてる</param>
	void SetSelect(bool flag, int numController);

	/// <summary>
	/// 選択されているかを取得
	/// </summary>
	/// <returns>trueなら選択されている</returns>
	bool IsSelect() { return isSelect_; }

	/// <summary>
	/// 動いているかセット
	/// </summary>
	/// <param name="flag">trueなら動いている</param>
	void SetMove(bool flag);

	/// <summary>
	/// 動いているか取得
	/// </summary>
	/// <returns>trueなら動いている</returns>
	bool IsMove() { return isMove_; }

	/// <summary>
	/// 選択中が変更されるかセット
	/// </summary>
	/// <param name="flag">trueなら動いている</param>
	void SetSelectNoChange(bool flag) { isSelectNoChange_ = flag; }

	/// <summary>
	/// 選択中が変更されるかどうか取得
	/// </summary>
	/// <returns>trueなら変更されない</returns>
	bool IsSelectNoChange() { return isSelectNoChange_; }

	/// <summary>
	/// 自分の前に選択されていたボタンのポジションをセット
	/// </summary>
	/// <param name="pos">位ポジションを置</param>
	void SetBeforeButtonSelectPos(XMFLOAT3 pos) { beforeButtonSelectPos_ = pos; }

	/// <summary>
	/// コントローラー番号を取得
	/// </summary>
	/// <returns>コントローラー番号</returns>
	int GetControllerNum() { return numController_; }
};

