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

//定数
namespace
{
	static const float RATATION_SPEED = 0.5f;     //回転速度
	static const XMFLOAT3 CAM_POS = { 0, 7, 15 }; //カメラの位置
	static const XMFLOAT3 CAM_TAR = { 0, 0, 0 };  //カメラのターゲット
	static const int FIELD_ANGLE = 45;            //カメラの画角
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

	///////////////カメラ///////////////////

	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(FIELD_ANGLE);
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
