#pragma once
#include "../../Stage.h"
#include "../../Player/PlayerBase.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../OtherObject/TitleScene/Ball.h"


//画面総数
enum class Players
{
	ONE, //一人プレイ
	TWO, //二人プレイ
	MAX
};

class Referee;

//ゲームのいろいろな管理をする
namespace GameManager
{
	///////////////////////////////関数//////////////////////////////////
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// シーン遷移の時の初期化
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画(コインの取得数やPlayerライフの表示)
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤーを追加
	/// </summary>
	/// <param name="p">プレイヤーのポインタ</param>
	void AddPlayer(PlayerBase* p);

	///////////////////////////////セットゲット関数//////////////////////////////////

	//プレイヤーのポインタセット
	void SetpPlayer(PlayerBase* player);

	//プレイヤーのポインタゲット
	PlayerBase* GetpPlayer();

	//ステージのポインタセット
	void SetpStage(Stage* stage);

	//ステージのポインタゲット
	Stage* GetpStage();

	//シーンマネージャーのポインタセット
	void SetpSceneManager(SceneManager* scene);

	//シーンマネージャーのポインタゲット
	SceneManager* GetpSceneManager();

	//ボールのポインタセット
	void SetpBall(Ball* ball);

	//ボールのポインタゲット
	Ball* GetpBall();

	//プレイヤー人数の設定
	void SetPlayers(Players s);

	//プレイヤー人数の取得
	Players GetPlayers();

	/// <summary>
	/// プレイヤーセット
	/// </summary>
	/// <returns>プレイヤー番号</returns>
	int  SetPlayer(PlayerBase* p);

	/// <summary>
	/// 審判取得
	/// </summary>
	/// <returns>審判</returns>
	Referee* GetReferee();

	/// <summary>
	/// 引数のプレイヤー以外のプレイヤーを取得
	/// </summary>
	/// <param name="p">プレイヤー</param>
	/// <returns>プレイヤーを取得</returns>
	PlayerBase* GetNotMyPlayer(PlayerBase* p);

};

