#include "sceneManager.h"
#include "../../Engine/ResourceManager/ModelManager.h"
#include "../../Engine/ResourceManager/ImageManager.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Engine/GameObject/Light.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Scene/PlayScene/PlayScene.h"
#include "../../Scene/TitleScene/TitleScene.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "../../Engine/ResourceManager/VFX.h"
#include "../../Engine/GUI/ImGuiSet.h"


//コンストラクタ
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager"), isLoadDraw_(true), isSameSceneInitialize_(false)
{
}

//初期化
void SceneManager::Initialize()
{
	//自身を追加
	GameManager::SetpSceneManager(this);

	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

//更新
void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_ || isSameSceneInitialize_)
	{
		SceneUpdate();
	}
}

//シーンを更新
void SceneManager::SceneUpdate()
{
	//ロード中に描画するなら
	if (isLoadDraw_)
	{
		//ロードしているとき用の画像表示(すぐ表示したいので描画終了を呼ぶ)
		Fade::SetFadeStatus(DRAW);
		Direct3D::EndDraw();
	}

	//そのシーンのオブジェクトを全削除
	KillAllChildren();

	//ロードしたデータを全削除
	ButtonManager::Reset();
	VFX::Release();
	Audio::AllRelease();
	ModelManager::AllRelease();
	ImageManager::AllRelease();
	Time::AllRelease();

	//シーン遷移時の初期化
	GameManager::SceneTransitionInitialize();

	//次のシーンを作成
	switch (nextSceneID_)
	{
	case SCENE_ID_PLAY:				 Instantiate<PlayScene>(this); break;
	case SCENE_ID_TITLE:			 Instantiate<TitleScene>(this); break;
	}

	//カレントシーンを更新
	ARGUMENT_INITIALIZE(currentSceneID_, nextSceneID_);

	//ロード中に描画するに初期化しておく
	ARGUMENT_INITIALIZE(isLoadDraw_, true);

	//初期化状態に
	ARGUMENT_INITIALIZE(isSameSceneInitialize_, false);
}

//同じシーンを初期化状態にする
void SceneManager::SameSceneInitializ(SCENE_ID next)
{
	//時間止めていれば解除
	Direct3D::SetTimeScale(false);

	//マップエディタ状態なら解除しておく
	Direct3D::SetScreenGameStatus(true);

	//初期状態に
	ImGuiSet::SetGameMode(static_cast<int>(Mode::START));
	ImGuiSet::SetScreenMode(static_cast<int>(Mode::GAME));
	Direct3D::SetBackScreenColor(XMFLOAT4(0, 0, 0, 1));

	//シーン切り替え
	ChangeScene(next);

	//同じシーンを初期化するに設定
	ARGUMENT_INITIALIZE(isSameSceneInitialize_,true);
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next){ 	

	//時間止めていれば解除
	Direct3D::SetTimeScale(false);

	//マップエディタ状態なら解除しておく
	Direct3D::SetScreenGameStatus(true);
	
	//初期状態に
	ImGuiSet::SetGameMode(static_cast<int>(Mode::START));
	ImGuiSet::SetScreenMode(static_cast<int>(Mode::GAME));
	Direct3D::SetBackScreenColor(XMFLOAT4(0, 0, 0, 1));
	
	ARGUMENT_INITIALIZE(nextSceneID_,next);
}

//一個前のシーンIDをゲット
SCENE_ID SceneManager::GetBeforeSceneId() { return currentSceneID_; }

//現在のシーンIDゲット
SCENE_ID SceneManager::GetSceneId(){ return nextSceneID_;}

//ロードをしてる時に画像表示するかセットする
void SceneManager::SetLoadDrawFlag(bool flag){ ARGUMENT_INITIALIZE(isLoadDraw_, flag);}