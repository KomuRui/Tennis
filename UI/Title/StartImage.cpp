#include "StartImage.h"
#include "../../Engine/ResourceManager/ImageManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Time.h"

//定数
namespace
{
	static const float CHANGE_VALUE = 0.015f; //変化量
	static const float MAX_ALPHA = 1.0f;	  //最大透明度
	static const float MIN_ALPHA = 0.2f;	  //最小透明度
}

//コンストラクタ
StartImage::StartImage(GameObject* parent, std::string modelPath, std::string name)
	: ImageBase(parent, modelPath, name), nowAlpha_(MAX_ALPHA), sign_(-1)
{
}

//初期化
void StartImage::ChildInitialize()
{
	//透明じゃなくしておく
	ImageManager::SetAlpha(hPict_, nowAlpha_);
}

//更新
void StartImage::ChildUpdate()
{
	//値加算
	nowAlpha_ += CHANGE_VALUE * sign_;
	ImageManager::SetAlpha(hPict_, nowAlpha_);

	//範囲外なら符号を変える
	if (nowAlpha_ < MIN_ALPHA || nowAlpha_ > MAX_ALPHA) sign_ *= -1;

	//透明度が範囲内に収まるように
	ARGUMENT_INITIALIZE(nowAlpha_,Clamp<float>(nowAlpha_, MAX_ALPHA, MIN_ALPHA));
}

