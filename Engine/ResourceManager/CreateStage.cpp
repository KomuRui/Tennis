#include "CreateStage.h"
#include "../GameObject/Light.h"
#include "../GameObject/CameraTransitionObject.h"
#include "../../UI/ImageBase.h"
#include "../../UI/ScalingImage.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../GameObject/GameObject.h"
#include "../../Base/Mob.h"
#include "../../Base/NormalObject.h"
#include "../../OtherObject/TitleScene/TennisCourt.h"
#include "../../OtherObject/TitleScene/TennisCourtAround.h"
#include "../../OtherObject/TitleScene/Net.h"
#include "../../OtherObject/TitleScene/NetAround.h"
#include "../../OtherObject/TitleScene/Water.h"
#include "../../OtherObject/TitleScene/Ball.h"
#include "../../Player/PlayerBase.h"
#include <fstream>


//コンストラクタ
CreateStage::CreateStage()
	:createShineController_(false)
{
}

//オブジェクト作成
void CreateStage::CreateObject(GameObject* parent, std::string ModelPathName, std::string inName, Transform t, XMFLOAT3 camPos)
{
	
	/////////////////////Player///////////////////////

	if (inName == "Player")
	{
		GameManager::SetpPlayer(InstantiateNormal<PlayerBase>(parent, ModelPathName, inName, t));
	}

	/////////////////////Base///////////////////////

	if (inName == "Mob")
	{
		InstantiateMob3D<Mob>(parent, ModelPathName, inName, t);
	}
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
		InstantiateNormal<Ball>(parent, ModelPathName, inName, t);
	}

	/////////////////////Camera////////////////////////

	if (inName == "Camera")
	{
		//カメラ情報を入れる変数用意
		StageCameraTransition information;

		//各情報初期化
		information.CameraPosition = camPos;
		information.CameraTarget = t.rotate_;
		information.CollisionSize = t.scale_;

		//コンストラクタ呼ぶ
		CameraTransitionObject* pNewObject = new CameraTransitionObject(parent, information);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}

		//回転と拡大を0に初期化する
		ARGUMENT_INITIALIZE(t.rotate_, XMFLOAT3(0, 0, 0));
		ARGUMENT_INITIALIZE(t.scale_, XMFLOAT3(0, 0, 0));

		pNewObject->SetTransform(t);
		pNewObject->Initialize();
		createStageAllObject_.push_back(pNewObject);
	}

	/////////////////////Light/////////////////////////

	if (inName == "Light")
	{
		Light::CreateLight(XMFLOAT4(t.position_.x, t.position_.y, t.position_.z, 0), t.scale_.x);
	}

	/////////////////////Gimmick///////////////////////

}

//各ステージのファイルロードしステージを作成してくれる
void CreateStage::LoadFileCreateStage(GameObject* parent, std::string filename)
{
	//ファイルオープン
	const char* fileName = filename.c_str();
	std::ifstream ifs(fileName);

	//データを1列入れる変数
	std::string buf;

	//必要な各パラメータを保存する用の文字列配列(pos.x,pos,y,pos.zとか)
	std::string data[14] = { "" };

	//,の数
	int sum = 0;

	//末尾まで読む
	while (!ifs.eof())
	{
		//1列bufに格納
		std::getline(ifs, buf);

		//bufのサイズ分ループ
		for (int i = 0; i < buf.size(); i++)
		{
			//各パラメータを一つずつdataに格納していく
			if (buf[i] != ',')
			{
				data[sum] += buf[i];
			}
			else
				sum++;
		}

		//各パラメータを変数に格納していく
		std::string ModelPathName = data[0];
		std::string Name = data[1];

		Transform t;

		t.position_ = { std::stof(data[2]),std::stof(data[3]),std::stof(data[4]) };
		t.rotate_ = { std::stof(data[5]),std::stof(data[6]),std::stof(data[7]) };
		t.scale_ = { std::stof(data[8]),std::stof(data[9]),std::stof(data[10]) };

		if(parent != nullptr)
			t.pParent_ = parent->GetTransform();
		else
			t.pParent_ = nullptr;

		//カメラのポジション入れる変数
		XMFLOAT3 camPos;

		//カメラのポジションを必要とするオブジェクトなら
		if (Name.find("Camera") != std::string::npos || Name == "ShineLight")
			camPos = { std::stof(data[11]),std::stof(data[12]),std::stof(data[13]) };
		//それ以外は使わないので0にしておく
		else
			camPos = { 0,0,0 };

		//パラメータを基にオブジェクト作成
		CreateObject(parent,ModelPathName, Name, t, camPos);

		//すべて初期化
		for (int i = 0; i < 14; i++)
		{
			data[i] = "";
		}
		sum = 0;
	}


}

//各ステージのファイルロードだけしてくれる
void CreateStage::LoadFile(GameObject* parent, std::string filename)
{
	//ファイルオープン
	const char* fileName = filename.c_str();
	std::ifstream ifs(fileName);

	//データを1列入れる変数
	std::string buf;

	//必要な各パラメータを保存する用の文字列配列(pos.x,pos,y,pos.zとか)
	std::string data[14] = { "" };

	//,の数
	int sum = 0;

	//末尾まで読む
	while (!ifs.eof())
	{
		//1列bufに格納
		std::getline(ifs, buf);

		//bufのサイズ分ループ
		for (int i = 0; i < buf.size(); i++)
		{
			//各パラメータを一つずつdataに格納していく
			if (buf[i] != ',')
			{
				data[sum] += buf[i];
			}
			else
				sum++;
		}

		//情報を格納しておく変数
		CreateStageInfo info;


		//各パラメータを変数に格納していく
		info.parent = parent;
		info.ModelPathName = data[0];
		info .inName = data[1];

		Transform t;

		info.t.position_ = { std::stof(data[2]),std::stof(data[3]),std::stof(data[4]) };
		info.t.rotate_ = { std::stof(data[5]),std::stof(data[6]),std::stof(data[7]) };
		info.t.scale_ = { std::stof(data[8]),std::stof(data[9]),std::stof(data[10]) };


		//カメラのポジションを必要とするオブジェクトなら
		if (info.inName.find("Camera") != std::string::npos || info.inName == "ShineLight")
			info.camPos = { std::stof(data[11]),std::stof(data[12]),std::stof(data[13]) };
		//それ以外は使わないので0にしておく
		else
			info.camPos = { 0,0,0 };

		info_.push_back(info);

		//すべて初期化
		for (int i = 0; i < 14; i++)
		{
			data[i] = "";
		}
		sum = 0;
	}

}

//LoadFileを使ってロードしたファイルを元にステージを作成
void CreateStage::LoadFileBasedCreateStage()
{
	for (auto i = info_.begin(); i != info_.end(); i++)
	{
		CreateObject((*i).parent, (*i).ModelPathName, (*i).inName, (*i).t, (*i).camPos);
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
T* CreateStage::InstantiateNormal(GameObject* pParent,std::string modelPath, std::string name, Transform t)
{
	T* pNewObject = new T(pParent, modelPath,name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetTransform(t);
	pNewObject->Initialize();
	createStageAllObject_.push_back(pNewObject);

	return pNewObject;
}

//普通型の生成(名前とモデルパス指定しない)
template <class T>
T* CreateStage::InstantiateNormal(GameObject* pParent, Transform t)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetTransform(t);
	pNewObject->Initialize();

	return pNewObject;
}

//Mobを継承した3Dオブジェ生成
template <class T>
T* CreateStage::InstantiateMob3D(GameObject* pParent, std::string modelPath, std::string name, Transform t)
{
	T* pNewObject = new T(pParent, modelPath, name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetTransform(t);
	pNewObject->SetAngle(t.rotate_.y);
	pNewObject->Initialize();
	createStageAllObject_.push_back(pNewObject);

	return pNewObject;
}

//ボタンの生成
template <class T>
T* CreateStage::InstantiateButton(GameObject* pParent, std::string modelPath, std::string name, Transform t)
{
	T* p = InstantiateNormal<T>(pParent, modelPath, name, t);
	ButtonManager::AddButton(p);

	return p;
}

//星の生成
template <class T>
T* CreateStage::InstantiatePlanet(GameObject* pParent, std::string modelPath, std::string name, Transform t)
{
	T* pNewObject = new T(pParent, modelPath, name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetTransform(t);
	pNewObject->Initialize();

	return pNewObject;
}