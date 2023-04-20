#include "NormalObject.h"
#include "../Engine/ResourceManager/Model.h"

//コンストラクタ
NormalObject::NormalObject(GameObject* parent, std::string modelPath, std::string name)
	:GameObject(parent,name),modelNamePath_(modelPath),hModel_(-1)
{}

//初期化
void NormalObject::Initialize()
{
	///////////////モデルデータのロード///////////////////

	ARGUMENT_INITIALIZE(hModel_,Model::Load(modelNamePath_));
	ARGUMENT_INITIALIZE(pathName_, modelNamePath_);
	assert(hModel_ >= ZERO);

	//継承先用
	ChildInitialize();
}

//更新の前に一回呼ばれる関数
void NormalObject::StartUpdate()
{
	//継承先用
	ChildStartUpdate();
}

//更新
void NormalObject::Update()
{
	//継承先用
	ChildUpdate();
}

//描画
void NormalObject::Draw()
{
	//描画
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	//継承先用
	ChildDraw();
}

//開放
void NormalObject::Release()
{
	//継承先用
	ChildRelease();
}
