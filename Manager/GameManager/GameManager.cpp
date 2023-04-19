#include "GameManager.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../TextManager/TextManager.h"
#include "../ButtonManager/ButtonManager.h"
#include "../AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../AudioManager/OtherAudioManager/OtherAudioManager.h"
#include <cmath>

//ゲームのいろいろな管理をする
namespace GameManager
{
	///////////////////////////////変数//////////////////////////////////

	//現在使用されているプレイヤーのポインタ格納用
	PlayerBase* pNowPlayer_;

	//現在の使用されているステージのポインタ格納用
	Stage* pNowStage_;

	//現在の使用されているワープのポインタ格納用
	Warp* pNowWarp_;

	//シーンマネージャーのポインタ格納用
	SceneManager* pSceneManager_;

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void GameManager::Initialize()
	{
		//音初期化
		OtherAudioManager::Initialize();
		PlayerAudioManager::Initialize();

		//テキストマネージャの初期化
		TextManager::Initialize();

		//フェイドの初期化
		Fade::Initialize();

		//各変数初期化
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(pSceneManager_, nullptr);
	}

	//シーン遷移の時の初期化
	void GameManager::SceneTransitionInitialize()
	{
		//いろいろ初期化状態にしておく
		Light::Initialize();
		Fade::SceneTransitionInitialize();
		OtherAudioManager::SceneTransitionInitialize();
		PlayerAudioManager::SceneTransitionInitialize();
	}

	//Playerが死亡した時にLifeManagerから呼ばれる
	void GameManager::PlayerDie()
	{

	}

	//更新
	void GameManager::Update()
	{
		//ボタンマネージャの更新を呼ぶ
		ButtonManager::Update();
	}

	//描画(コインの取得数やPlayerライフの表示)
	void GameManager::Draw()
	{
		//Uiなどを表示
		Image::UiDraw();

		//フェード用の描画
		Fade::Draw();
	}


	///////////////////////////////セットゲット関数//////////////////////////////////
	
	//プレイヤーのポインタセット
	void GameManager::SetpPlayer(PlayerBase* player) { pNowPlayer_ = player; }

	//プレイヤーのポインタゲット
	PlayerBase* GameManager::GetpPlayer() { return pNowPlayer_; }

	//ステージのポインタセット
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//ステージのポインタゲット
	Stage* GameManager::GetpStage() { return pNowStage_; }

	//ワープのポインタセット
	void GameManager::SetpWarp(Warp* warp) { pNowWarp_ = warp; }

	//ワープのポインタゲット
	Warp* GameManager::GetpWarp() { return pNowWarp_; }

	//シーンマネージャーのポインタセット
	void GameManager::SetpSceneManager(SceneManager* scene) { pSceneManager_ = scene; }

	//シーンマネージャーのポインタゲット
	SceneManager* GameManager::GetpSceneManager() { return pSceneManager_; }

}