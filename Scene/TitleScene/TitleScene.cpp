#include "TitleScene.h"
#include "../../Engine/System.h"

//定数
namespace
{
	static const float RATATION_SPEED = 0.5f;                  //回転速度
	static const XMFLOAT3 CAM_POS = { 0, 20, 25 };		       //カメラの位置
	static const XMFLOAT3 CAM_TAR = { ZERO,ZERO,ZERO };        //カメラのターゲット
	static const int FIELD_ANGLE = 45;						   //カメラの画角
}


//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
}

//デストラクタ
TitleScene::~TitleScene()
{
}

//初期化
void TitleScene::Initialize()
{
	///////////////カメラ///////////////////

	//一つ目のカメラ
	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(FIELD_ANGLE);

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFileCreateStage(this, "Data/StageData/Title/Title.json");

	hermiteMoveCamPos_->AddPath(CAM_POS,XMFLOAT3(15,0,15));
	hermiteMoveCamPos_->AddPath(XMFLOAT3(5,20,30));
	hermiteMoveCamPos_->AddPath(XMFLOAT3(-25,20,25));
	hermiteMoveCamPos_->AddPath(XMFLOAT3(28,20,40));
	hermiteMoveCamPos_->AddPath(XMFLOAT3(-3,20,10));
	hermiteMoveCamPos_->AddPath(XMFLOAT3(15,20,40));
	hermiteMoveCamPos_->Start();

	hermiteMoveCamTar_->AddPath(CAM_TAR, XMFLOAT3(15, 0, 15));
	hermiteMoveCamTar_->AddPath(XMFLOAT3(15, 0, -5));
	hermiteMoveCamTar_->AddPath(XMFLOAT3(5, 0, -15));
	hermiteMoveCamTar_->AddPath(XMFLOAT3(-18, 0, 9));
	hermiteMoveCamTar_->AddPath(XMFLOAT3(20, 0, 10));
	hermiteMoveCamTar_->AddPath(XMFLOAT3(1, 0, -10));
	hermiteMoveCamTar_->Start();
}

//更新
void TitleScene::Update()
{
	//Camera::SetPosition(hermiteMoveCamPos_->Updata());
	//Camera::SetTarget(hermiteMoveCamTar_->Updata());
}

//描画
void TitleScene::Draw()
{
}
