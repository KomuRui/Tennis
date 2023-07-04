#pragma once
#include "ButtonBase.h"
#include "../../Engine/Component/EasingMove.h"

/// <summary>
/// イージング移動をするボタンを表示させるクラス
/// </summary>
class EasingButton : public ButtonBase
{
protected:

	//イージング用
	std::unique_ptr<EasingMove> easing_;


public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	EasingButton(GameObject* parent, std::string modelPath, std::string name);

	//更新
	void ChildButtonUpdate() override;

	//子供用の更新
	virtual void EasingButtonChileUpdate() {};
};

