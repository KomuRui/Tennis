#include "TestScene.h"
#include "../../Engine/System.h"
#include "../../test.h"
#include "../../testBox.h"

//定数
namespace
{
	static const float RATATION_SPEED = 0.5f;                  //回転速度
	static const XMFLOAT3 CAM_POS = { 0, 0, 10 };		       //カメラの位置
	static const XMFLOAT3 CAM_TAR = { ZERO,ZERO,ZERO };        //カメラのターゲット
	static const int FIELD_ANGLE = 45;						   //カメラの画角
}


//コンストラクタ
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//デストラクタ
TestScene::~TestScene()
{
}

//初期化
void TestScene::Initialize()
{
	///////////////カメラ///////////////////

	//一つ目のカメラ
	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(FIELD_ANGLE);

	//Instantiate<test>(this, "Ball/Ball.fbx", "test1");
	Instantiate<test>(this, "Ball/Ball.fbx", "test2")->GetComponent<Transform>()->SetPosition(5,0,0);
	Instantiate<testBox>(this, "Ball/Ball.fbx", "testBox")->GetComponent<Transform>()->SetPosition(-5,0,0);
	Instantiate<testBox>(this, "Ball/Ball.fbx", "testBox2")->GetComponent<Transform>()->SetPosition(0,0,0);
}

//更新
void TestScene::Update()
{

}

//描画
void TestScene::Draw()
{
}

