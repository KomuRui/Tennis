#include "CreateStage.h"
#include "../GameObject/Light.h"
#include "../GameObject/CameraTransitionObject.h"
#include "../../UI/ImageBase.h"
#include "../../UI/ScalingImage.h"
#include "../../UI/Title/StartImage.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../GameObject/GameObject.h"
#include "../../Base/NormalObject.h"
#include "../../OtherObject/PlayScene/TennisCourt.h"
#include "../../OtherObject/PlayScene/TennisCourtAround.h"
#include "../../OtherObject/PlayScene/Net.h"
#include "../../OtherObject/PlayScene/NetAround.h"
#include "../../OtherObject/PlayScene/Water.h"
#include "../../OtherObject/PlayScene/Ball.h"
#include "../../OtherObject/PlayScene/Referee.h"
#include "../../OtherObject/PlayScene/Sky.h"
#include "../../Player/PlayerBase.h"
#include "../Component/Transform/Transform.h"
#include "../../Engine/nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

//コンストラクタ
CreateStage::CreateStage()
	:createShineController_(false)
{
}

//オブジェクト作成
void CreateStage::CreateObject(GameObject* parent, std::string ModelPathName, std::string inName, Transform* t)
{
	
	/////////////////////Player///////////////////////

	if (inName == "Player")
	{
		GameManager::SetpPlayer(InstantiateNormal<PlayerBase>(parent, ModelPathName, inName, t));
	}

	/////////////////////Base///////////////////////

	if (inName == "NormalObject")
	{
		InstantiateNormal<NormalObject>(parent, ModelPathName, inName, t);
	}

	/////////////////////UI///////////////////////

	if (inName == "ImageBase")
	{
		InstantiateNormal<ImageBase>(parent, ModelPathName, inName, t);
	}
	if (inName == "ScalingImage")
	{
		InstantiateNormal<ScalingImage>(parent, ModelPathName, inName, t);
	}
	if (inName == "StartImage")
	{
		InstantiateNormal<StartImage>(parent, ModelPathName, inName, t);
	}

	/////////////////////OtherObject///////////////////////

	if (inName == "TennisCourt")
	{
		InstantiateNormal<TennisCourt>(parent, ModelPathName, inName, t);
	}
	if (inName == "TennisCourtAround")
	{
		InstantiateNormal<TennisCourtAround>(parent, ModelPathName, inName, t);
	}
	if (inName == "Net")
	{
		InstantiateNormal<Net>(parent, ModelPathName, inName, t);
	}
	if (inName == "NetAround")
	{
		InstantiateNormal<NetAround>(parent, ModelPathName, inName, t);
	}
	if (inName == "Water")
	{
		InstantiateNormal<Water>(parent, ModelPathName, inName, t);
	}
	if (inName == "Ball")
	{
		GameManager::SetpBall(InstantiateNormal<Ball>(parent, ModelPathName, inName, t));
	}
	if (inName == "Sky")
	{
		InstantiateNormal<Sky>(parent, ModelPathName, inName, t);
	}

	/////////////////////Camera////////////////////////

	if (inName == "Camera")
	{
		//カメラ情報を入れる変数用意
		StageCameraTransition information;

		//各情報初期化
		information.CameraPosition = XMFLOAT3(0,0,0);
		information.CameraTarget = t->rotate_;
		information.CollisionSize = t->scale_;

		//コンストラクタ呼ぶ
		CameraTransitionObject* pNewObject = new CameraTransitionObject(parent, information);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}

		//回転と拡大を0に初期化する
		ARGUMENT_INITIALIZE(t->rotate_, XMFLOAT3(0, 0, 0));
		ARGUMENT_INITIALIZE(t->scale_, XMFLOAT3(0, 0, 0));

		pNewObject->GetComponent<Transform>()->SetTransform(t);
		pNewObject->Initialize();
		createStageAllObject_.push_back(pNewObject);
	}

	/////////////////////Light/////////////////////////

	if (inName == "Light")
	{
		Light::CreateLight(XMFLOAT4(t->position_.x, t->position_.y, t->position_.z, 0), t->scale_.x);
	}

	/////////////////////Gimmick///////////////////////

}

//各ステージのファイルロードしステージを作成してくれる
void CreateStage::LoadFileCreateStage(GameObject* parent, std::string filename)
{
	//各パラメータ格納用
	std::string ModelPathName;
	std::string Name;
	Transform t;

	//親情報があれば追加する
	if (parent != nullptr)
		t.parent = parent;
	else
		t.parent = nullptr;

	//ファイル読み込み
	ifstream ifs(filename);
	json json_object;
	ifs >> json_object;

	//各値取得
	for (auto it = json_object.begin(); it != json_object.end(); it++) {
		
		ARGUMENT_INITIALIZE(ModelPathName,json_object[it.key()]["FileName"]);
		ARGUMENT_INITIALIZE(Name,json_object[it.key()]["TypeName"]);
		ARGUMENT_INITIALIZE(t.position_,XMFLOAT3(json_object[it.key()]["Position"][0], json_object[it.key()]["Position"][1], json_object[it.key()]["Position"][2]));
		ARGUMENT_INITIALIZE(t.rotate_,XMFLOAT3(json_object[it.key()]["Rotate"][0], json_object[it.key()]["Rotate"][1], json_object[it.key()]["Rotate"][2]));
		ARGUMENT_INITIALIZE(t.scale_,XMFLOAT3(json_object[it.key()]["Scale"][0], json_object[it.key()]["Scale"][1], json_object[it.key()]["Scale"][2]));
		ARGUMENT_INITIALIZE(t.parent, parent);

		//パラメータを基にオブジェクト作成
		CreateObject(parent, ModelPathName, Name, &t);
	}	

}

//各ステージのファイルロードだけしてくれる
void CreateStage::LoadFile(GameObject* parent, std::string filename)
{
	//各パラメータ格納用
	std::string ModelPathName;
	std::string Name;
	Transform t;

	//親情報があれば追加する
	if (parent != nullptr)
		t.parent = parent;
	else
		t.parent = nullptr;

	//ファイル読み込み
	ifstream ifs(filename);
	json json_object;
	ifs >> json_object;

	//各値取得
	for (auto it = json_object.begin(); it != json_object.end(); it++) {

		//情報を格納しておく変数
		CreateStageInfo info;

		ARGUMENT_INITIALIZE(info.ModelPathName, json_object[it.key()]["FileName"]);
		ARGUMENT_INITIALIZE(info.inName, json_object[it.key()]["TypeName"]);
		ARGUMENT_INITIALIZE(info.t->position_, XMFLOAT3(json_object[it.key()]["Position"][0], json_object[it.key()]["Position"][1], json_object[it.key()]["Position"][2]));
		ARGUMENT_INITIALIZE(info.t->rotate_, XMFLOAT3(json_object[it.key()]["Rotate"][0], json_object[it.key()]["Rotate"][1], json_object[it.key()]["Rotate"][2]));
		ARGUMENT_INITIALIZE(info.t->scale_, XMFLOAT3(json_object[it.key()]["Scale"][0], json_object[it.key()]["Scale"][1], json_object[it.key()]["Scale"][2]));
		ARGUMENT_INITIALIZE(info.t->parent, t.parent);

		//保存しておく
		info_.push_back(info);
	}

}

//LoadFileを使ってロードしたファイルを元にステージを作成
void CreateStage::LoadFileBasedCreateStage()
{
	for (auto i = info_.begin(); i != info_.end(); i++)
	{
		CreateObject((*i).parent, (*i).ModelPathName, (*i).inName, (*i).t);
	}
}

//作成したステージをすべて削除
void CreateStage::AllCreateStageDelete(bool isKillPlayer)
{
	//作ったステージ分回す
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end();)
	{
		(*i)->KillMe();
		i = createStageAllObject_.erase(i);
	}

	//もしPlayerがいるのなら
	if (GameManager::GetpPlayer() != nullptr && isKillPlayer)GameManager::GetpPlayer()->KillMe();

	//すべてクリア
	createStageAllObject_.clear();
}

/// <summary>
/// 作成したステージすべて描画と更新しないように
/// </summary>
void CreateStage::AllCreateStageInvisibleAndLeave()
{
	//作ったステージ分回す
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end(); i++)
	{
		(*i)->Invisible();
		(*i)->Leave();
	}
}

/// <summary>
/// 作成した全てのステージを更新する
/// </summary>
void CreateStage::AllCreateStageUpdate()
{
	//作ったステージ分回す
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end(); i++)
	{
		if((*i) != nullptr)
			(*i)->Update();

		//空なら終了
		if (createStageAllObject_.empty()) return;
	}
}

/// <summary>
/// 作成した全てのステージを描画する
/// </summary>
void CreateStage::AllCreateStageDraw()
{
	//作ったステージ分回す
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end(); i++)
	{
		if ((*i) != nullptr)
			(*i)->Draw();
	}
}

/// <summary>
/// 作成したステージすべて描画と更新するように
/// </summary>
void CreateStage::AllCreateStageVisibleAndEnter()
{
	//作ったステージ分回す
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end(); i++)
	{
		(*i)->Visible();
		(*i)->Enter();
	}
}

//普通の生成
template <class T>
T* CreateStage::InstantiateNormal(GameObject* pParent,std::string modelPath, std::string name, Transform* t)
{
	T* pNewObject = new T(pParent, modelPath,name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}

	if (pNewObject->GetComponent<Transform>())
		pNewObject->GetComponent<Transform>()->SetTransform(t);

	pNewObject->Initialize();

	createStageAllObject_.push_back(pNewObject);

	return pNewObject;
}

//普通型の生成(名前とモデルパス指定しない)
template <class T>
T* CreateStage::InstantiateNormal(GameObject* pParent, Transform* t)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}

	if(pNewObject->GetComponent<Transform>())
		pNewObject->GetComponent<Transform>()->SetTransform(t);

	pNewObject->Initialize();

	return pNewObject;
}

//ボタンの生成
template <class T>
T* CreateStage::InstantiateButton(GameObject* pParent, std::string modelPath, std::string name, Transform* t)
{
	T* p = InstantiateNormal<T>(pParent, modelPath, name, t);
	ButtonManager::AddButton(p);

	return p;
}