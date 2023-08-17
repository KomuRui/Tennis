#include "TestScene.h"
#include "../../Engine/System.h"
#include "../../test.h"
#include "../../testBox.h"

//�萔
namespace
{
	static const float RATATION_SPEED = 0.5f;                  //��]���x
	static const XMFLOAT3 CAM_POS = { 0, 0, 10 };		       //�J�����̈ʒu
	static const XMFLOAT3 CAM_TAR = { ZERO,ZERO,ZERO };        //�J�����̃^�[�Q�b�g
	static const int FIELD_ANGLE = 45;						   //�J�����̉�p
}


//�R���X�g���N�^
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//�f�X�g���N�^
TestScene::~TestScene()
{
}

//������
void TestScene::Initialize()
{
	///////////////�J����///////////////////

	//��ڂ̃J����
	Camera::SetPosition(CAM_POS);
	Camera::SetTarget(CAM_TAR);
	Camera::SetFieldAngle(FIELD_ANGLE);

	//Instantiate<test>(this, "Ball/Ball.fbx", "test1");
	Instantiate<test>(this, "Ball/Ball.fbx", "test2")->GetComponent<Transform>()->SetPosition(5,0,0);
	Instantiate<testBox>(this, "Ball/Ball.fbx", "testBox")->GetComponent<Transform>()->SetPosition(-5,0,0);
	Instantiate<testBox>(this, "Ball/Ball.fbx", "testBox2")->GetComponent<Transform>()->SetPosition(0,0,0);
}

//�X�V
void TestScene::Update()
{

}

//�`��
void TestScene::Draw()
{
}

