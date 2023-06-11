#include "GameManager.h"
#include "../../Engine/System.h"
#include "../../OtherObject/TitleScene/Referee.h"
#include <cmath>

//ゲームのいろいろな管理をする
namespace GameManager
{
	///////////////////////////////変数//////////////////////////////////

	//現在使用されているプレイヤーのポインタ格納用
	PlayerBase* pNowPlayer_;

	//現在の使用されているステージのポインタ格納用
	Stage* pNowStage_;

	//現在の使用されているボールのポインタ格納用
	Ball* pNowBall_;

	//シーンマネージャーのポインタ格納用
	SceneManager* pSceneManager_;

	//審判
	Referee* referee_;

	//プレイヤー人数
	Players player_;

	//現在のプレイヤー登録人数
	int nowPlayerRegistration_;

	//プレイヤーのリスト保存用
	list<PlayerBase*> playerlist_;

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void GameManager::Initialize()
	{

		//テキストマネージャの初期化
		TextManager::Initialize();

		//基準点のマネージャーを初期化
		BasePointManager::Initialize();

		//フェイドの初期化
		Fade::Initialize();

		//各変数初期化
		ARGUMENT_INITIALIZE(pNowPlayer_, nullptr);
		ARGUMENT_INITIALIZE(pNowStage_, nullptr);
		ARGUMENT_INITIALIZE(pNowBall_, nullptr);
		ARGUMENT_INITIALIZE(pSceneManager_, nullptr);
		ARGUMENT_INITIALIZE(player_, Players::ONE);
		ARGUMENT_INITIALIZE(referee_, new Referee());
		ARGUMENT_INITIALIZE(nowPlayerRegistration_, ZERO);
	}

	//シーン遷移の時の初期化
	void GameManager::SceneTransitionInitialize()
	{
		//いろいろ初期化状態にしておく
		Light::Initialize();
		Fade::SceneTransitionInitialize();
	}

	//更新
	void GameManager::Update()
	{
		//ボタンマネージャの更新を呼ぶ
		ButtonManager::Update();

		//基準点のマネージャーを更新
		BasePointManager::Update();
	}

	//描画
	void GameManager::Draw()
	{
		//Uiなどを表示
		ImageManager::UiDraw();

		//スコアとか表示
		referee_->Draw();

		//フェード用の描画
		Fade::Draw();
	}

	//プレイヤーを追加
	void GameManager::AddPlayer(PlayerBase* p){ playerlist_.push_back(p);}

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

	//ボールのポインタセット
	void GameManager::SetpBall(Ball* ball) { pNowBall_ = ball; }

	//ボールのポインタゲット
	Ball* GameManager::GetpBall() { return pNowBall_; }

	//プレイヤー人数の設定
	void GameManager::SetPlayers(Players s) { player_ = s; }

	//プレイヤー人数の取得
	Players GameManager::GetPlayers() { return player_; }

	//プレイヤーセット
	int  GameManager::SetPlayer(PlayerBase* p) { 

		//登録
		playerlist_.push_back(p); 

		//1人目ならサーバーにしておく
		if (playerlist_.size() == 1)
		{
			referee_->SetServer(p);
		}
		//他はレシーバーに設定
		else
		{
			referee_->SetReceiver(p);
		}

		return nowPlayerRegistration_++; 
	}

	//審判取得
	Referee* GameManager::GetReferee() { return referee_; }

	//引数のプレイヤー以外のプレイヤーを取得
	PlayerBase* GetNotMyPlayer(PlayerBase* p)
	{
		for (auto i = playerlist_.begin(); i != playerlist_.end(); i++)
		{
			if ((*i) != p)
				return (*i);
		}

		return nullptr;
	}
}