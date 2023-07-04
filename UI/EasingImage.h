#pragma once
#include "ImageBase.h"
#include "../Engine/Component/EasingMove.h"

/// <summary>
/// イージング移動をする画像を表示させるクラス
/// </summary>
class EasingImage : public ImageBase
{
protected:

	//イージング用
	std::unique_ptr<EasingMove> easing_; 


public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	EasingImage(GameObject* parent, std::string modelPath, std::string name);

	//更新
	void ChildUpdate() override;

	//子供用の更新
	virtual void EasingImageChileUpdate() {};
};

