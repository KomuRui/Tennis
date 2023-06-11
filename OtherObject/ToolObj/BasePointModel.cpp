#include "BasePointModel.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/DirectX/Direct3D.h"

//コンストラクタ
BasePointModel::BasePointModel(GameObject* parent, std::string modelPath, std::string name)
	:NormalObject(parent, modelPath, name), basePointName_(""), isPlayerType_(false)
{}

BasePointModel::BasePointModel(GameObject* parent)
	:NormalObject(parent, "Tool/ToolModel/BasePosModel.fbx", "BasePointModel"), basePointName_(""), isPlayerType_(false)
{}

//初期化
void BasePointModel::ChildInitialize()
{
	//基準点として追加
	ModelManager::SetBasePointObj(hModel_,this);

	//レイの判定に含まれるように設定
	ModelManager::SetRayFlag(hModel_, true);
}

//二つ目のウィンドウの描画
void BasePointModel::TwoWindowDraw()
{
	//描画
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

//描画
void BasePointModel::Draw()
{
	//描画
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}
