#include "NormalObject.h"
#include "../Engine/ResourceManager/ModelManager.h"

//コンストラクタ
NormalObject::NormalObject(GameObject* parent, std::string modelPath, std::string name)
	:GameObject(parent,name),modelNamePath_(modelPath),hModel_(-1)
{}

//初期化
void NormalObject::Initialize()
{
	///////////////モデルデータのロード///////////////////

	ARGUMENT_INITIALIZE(hModel_,ModelManager::Load(modelNamePath_));
	ARGUMENT_INITIALIZE(pathName_, modelNamePath_);
	assert(hModel_ >= ZERO);

	//モデルの名前設定
	ModelManager::SetModelName(hModel_,GetObjectName());

	//ゲームオブジェクト追加
	ModelManager::SetGameObject(hModel_, this);

	//影ONにしておく
	SetShadow(true);
	
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
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);

	//継承先用
	ChildDraw();
}

//開放
void NormalObject::Release()
{
	//継承先用
	ChildRelease();
}
