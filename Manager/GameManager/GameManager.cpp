#include "GameManager.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/ImageManager.h"
#include "../TextManager/TextManager.h"
#include "../ButtonManager/ButtonManager.h"
#include "../ScoreManager/ScoreManager.h"
#include "../AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../AudioManager/OtherAudioManager/OtherAudioManager.h"
#include "../BasePointManager/BasePointManager.h"
#include <cmath>

//ゲームのいろいろな管理をする
namespace GameManager
{
	///////////////////////////////変数//////////////////////////////////

	//現在使用されているプレイヤーのポインタ格納用
	PlayerBase* pNowPlayer_;

	//現在の使用されているステージのポインタ格納用
	Stage* pNowStage_;

	//シーンマネージャーのポインタ格納用
	SceneManager* pSceneManager_;

	//プレイヤー人数
	Players player_;

	//現在のプレイヤー登録人数
	int nowPlayerRegistration_;

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void GameManager::Initialize()
	{
		//音初期化
		OtherAudioManager::Initialize();
		PlayerAudioManager::Initialize();

		//テキストマネージャの初期化
		TextManager::Initialize();

		//スコアマネージャーの初期化
		ScoreManager::Initialize();

		//基準点のマネージャーを初期化
		BasePointManager::Initialize();

		//フェイドの初期化
		Fade::Initialize();

		//各変数初期化
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(pSceneManager_, nullptr);
		ARGUMENT_INITIALIZE(player_, Players::ONE);
		ARGUMENT_INITIALIZE(nowPlayerRegistration_, ZERO);
	}

	//シーン遷移の時の初期化
	void GameManager::SceneTransitionInitialize()
	{
		//いろいろ初期化状態にしておく
		Light::Initialize();
		Fade::SceneTransitionInitialize();
		OtherAudioManager::SceneTransitionInitialize();
		PlayerAudioManager::SceneTransitionInitialize();
		ScoreManager::SceneTransitionInitialize();
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

		//基準点のマネージャーを更新
		BasePointManager::Update();
	}

	//描画(コインの取得数やPlayerライフの表示)
	void GameManager::Draw()
	{
		//Uiなどを表示
		ImageManager::UiDraw();

		//スコアマネージャーの描画
		ScoreManager::Draw();

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

	//シーンマネージャーのポインタセット
	void GameManager::SetpSceneManager(SceneManager* scene) { pSceneManager_ = scene; }

	//シーンマネージャーのポインタゲット
	SceneManager* GameManager::GetpSceneManager() { return pSceneManager_; }

	//プレイヤー人数の設定
	void GameManager::SetPlayers(Players s) { player_ = s; }

	//プレイヤー人数の取得
	Players GameManager::GetPlayers() { return player_; }

	//プレイヤーセット
	int  GameManager::SetPlayer() { 

		//プレイヤー番号返す
		return nowPlayerRegistration_++;
	};
}