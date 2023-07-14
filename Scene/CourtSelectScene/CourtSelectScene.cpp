#include "CourtSelectScene.h"
#include "../../UI/ModeSelect/ModeSelectSceneUI.h"
#include "../../Engine/GameObject/Camera.h"
#include <fstream>
#include "../../Engine/nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

//定数
namespace
{
	static const XMFLOAT3 CAM_POS = { 0, 20, 25 };		       //カメラの位置
	static const XMFLOAT3 CAM_TAR = { ZERO,ZERO,ZERO };        //カメラのターゲット
	static const int FIELD_ANGLE = 45;						   //カメラの画角
}

//コンストラクタ
CourtSelectScene::CourtSelectScene(GameObject* parent)
	: GameObject(parent, "CourtSelectScene"), nowLookNum_(ZERO)
{
}

//デストラクタ
CourtSelectScene::~CourtSelectScene()
{
}

//初期化
void CourtSelectScene::Initialize()
{

	///////////////カメラ///////////////////

	//一つ目のカメラ
	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(FIELD_ANGLE);

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	std::unique_ptr<CreateStage> pCreateStage = std::make_unique<CreateStage>();
	pCreateStage->LoadFileCreateStage(this, "Data/StageData/CourtSelect/CourtSelect.json");

	/////////////////ファイル読み込んでパスごとの位置取得///////////////////

	SetData("Data/PathData/TitleCamera/CamPos2.json", "Data/PathData/TitleCamera/CamTar2.json");
	SetData("Data/PathData/TitleCamera/CamPos3.json", "Data/PathData/TitleCamera/CamTar3.json");

	//開始
	hermiteMoveTable_[nowLookNum_].first->Start();
	hermiteMoveTable_[nowLookNum_].second->Start();
}

//更新
void CourtSelectScene::Update()
{
	//カメラ
	CameraMove();
}

//カメラの動き
void CourtSelectScene::CameraMove()
{
	//カメラ設定
	Camera::SetPosition(hermiteMoveTable_[nowLookNum_].first->Updata());
	Camera::SetTarget(hermiteMoveTable_[nowLookNum_].second->Updata());

	//動きが終わったのなら
	if (hermiteMoveTable_[nowLookNum_].first->IsFinish())
	{
		nowLookNum_++;

		//サイズオーバーしていたなら
		if (hermiteMoveTable_.size() == nowLookNum_)
			ARGUMENT_INITIALIZE(nowLookNum_, ZERO);

		//開始
		hermiteMoveTable_[nowLookNum_].first->ReStart();
		hermiteMoveTable_[nowLookNum_].second->ReStart();
	}
}

//データセット
void CourtSelectScene::SetData(string posFileName, string tarFileName)
{
	//新しく追加
	hermiteMoveTable_.push_back({ std::make_unique<HermiteSplineMove>(), std::make_unique<HermiteSplineMove>() });

	//読み込み
	ifstream ifsPos(posFileName);
	json json_object_Pos;
	ifsPos >> json_object_Pos;

	//各値取得
	for (auto it = json_object_Pos.begin(); it != json_object_Pos.end(); it++) {

		hermiteMoveTable_[hermiteMoveTable_.size() - 1].first->AddPath(XMFLOAT3(json_object_Pos[it.key()]["Position"][0], json_object_Pos[it.key()]["Position"][1], json_object_Pos[it.key()]["Position"][2]), XMFLOAT3(50, ZERO, ZERO));
	}

	//読み込み
	ifstream ifsTar(tarFileName);
	json json_object_Tar;
	ifsTar >> json_object_Tar;

	//各値取得
	for (auto it = json_object_Tar.begin(); it != json_object_Tar.end(); it++) {

		hermiteMoveTable_[hermiteMoveTable_.size() - 1].second->AddPath(XMFLOAT3(json_object_Tar[it.key()]["Position"][0], json_object_Tar[it.key()]["Position"][1], json_object_Tar[it.key()]["Position"][2]), XMFLOAT3(ZERO, ZERO, ZERO));
	}
}