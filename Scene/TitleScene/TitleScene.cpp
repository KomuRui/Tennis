#include "TitleScene.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"
#include "../../Manager/BasePointManager/BasePointManager.h"
#include "../../OtherObject/TitleScene/Ball.h"

//定数
namespace
{
	static const float RATATION_SPEED = 0.5f;                  //回転速度
	static const XMFLOAT3 CAM_POS = { 0, 10.67f, 24.17f };     //カメラの位置
	static const XMFLOAT3 CAM_TAR = { 0, 2.27f, 8.01f };       //カメラのターゲット
															   
	static const XMFLOAT3 CAM_POS_2 = { 0, 10.67f, -24.17f };  //カメラの位置
	static const XMFLOAT3 CAM_TAR_2 = { 0, 2.27f, -8.01f };    //カメラのターゲット

	static const XMFLOAT3 CAM_POS_TOW_WINDOW = { 0, 20, 0 };   //カメラの位置2
	static const XMFLOAT3 CAM_TAR_TOW_WINDOW = { 0, 0, 0 };    //カメラのターゲット2
	static const XMVECTOR CAM_UP_TOW_WINDOW = { -1, 0, 0, 0 }; //カメラの上方向
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

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFileCreateStage(this, "Stage/Title/StageInformation/TitleScene.txt");

	////////////////////////ツールの基準点モデルを生成/////////////////////////////////

	BasePointManager::InstantiateBasePointModel();

	GameManager::SetPlayers(Players::ONE);

	///////////////カメラ///////////////////

	//一つ目のカメラ
	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(FIELD_ANGLE);
	Camera::FrameCameraInitialize();

	//二つ目のカメラ
	Camera::SetPositionTwo(CAM_POS_2);
	Camera::SetTargetTwo(CAM_TAR_2);

	//二つ目のウィンドウのカメラ
	Camera::TwoWindowSetPosition(CAM_POS_TOW_WINDOW);
	Camera::TwoWindowSetTarget(CAM_TAR_TOW_WINDOW);
	Camera::SetTwoWindowUpDirection(CAM_UP_TOW_WINDOW);
}

//更新の前に一度だけ呼ばれる更新
void TitleScene::StartUpdate()
{
}

//更新
void TitleScene::Update()
{
}

//描画
void TitleScene::Draw()
{
}

//開放
void TitleScene::Release()
{
}
