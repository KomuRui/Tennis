#include "TennisCourt.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/DirectX/Direct3D.h"

//コンストラクタ
TennisCourt::TennisCourt(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent,modelPath,name),type_(TennisCourtType::HARD_COURT)
{}

//初期化
void TennisCourt::ChildInitialize()
{
	//各コートのモデルロード
	ARGUMENT_INITIALIZE(hModelTable_[TennisCourtType::HARD_COURT], ModelManager::Load("Stage/TennisCourt_ha-do.fbx"));
	ARGUMENT_INITIALIZE(hModelTable_[TennisCourtType::GRASS_COURT], ModelManager::Load("Stage/TennisCourt_gurasu.fbx"));
	ARGUMENT_INITIALIZE(hModelTable_[TennisCourtType::CLAY_COURT], ModelManager::Load("Stage/TennisCourt_kurei.fbx"));

	//影適用しないように
	SetShadow(false);
}

//二つ目のウィンドウの描画
void TennisCourt::TwoWindowDraw()
{
	//描画
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

//テニスコートの型を設定
void TennisCourt::SetTennisCourtType(TennisCourtType type)
{
	//タイプ登録
	ARGUMENT_INITIALIZE(type_, type);
	ARGUMENT_INITIALIZE(hModel_, hModelTable_[type]);
}