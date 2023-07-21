#pragma once
#include "../Base/NormalObject.h"
#include "../Engine/GameObject/GameObject.h"
#include "../State/PlayerState/PlayerStateManager.h"
#include "../Engine/ResourceManager/ModelManager.h"
#include "../Engine/Component/Transform/Transform.h"
#include "../OtherObject/PlayScene/TennisCourt.h"
#include "../Engine/Component/HermiteSplineMove.h"

class Racket;

/// <summary>
/// Playerの基底クラス
/// </summary>
class PlayerBase : public NormalObject
{
protected:

	///////////////キャラの必要な情報///////////////////

	Racket* pRacket_;                   //ラケット
	PlayerStateManager* pState_;        //Playerの状態を表す変数
	TennisCourtName nowMyCourtName_;    //自身がいるコートの名前
	XMFLOAT3 initialPosition_;          //Playerの初期位置 
	float power_;                       //パワー
	float technique_;                   //テクニック

	/////////////////////カメラ//////////////////////

	
	vector<std::unique_ptr<HermiteSplineMove>> hermiteMoveTable_; //エルミートスプラインを使ってカメラを動かす(連続して動きを変更したいのでvectorにしておく)
	int nowLookNum_;    //現在見ている番号                       

	XMVECTOR camVec_;   //Playerからカメラまでのベクトル
	XMVECTOR camVec2_;  //Playerからカメラまでのベクトル

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	PlayerBase(GameObject* parent, std::string modelFilePath_, std::string name);


	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	///////////////////////////関数////////////////////////////

	/// <summary>
	/// カメラの処理
	/// </summary>
	void CameraBehavior();

	/// <summary>
	///ゲームスタート時のカメラ 
	/// </summary>
	void GameStartCamera();

	/// <summary>
	/// サーブレシーブ時のカメラの処理
	/// </summary>
	void ServeReceiveCameraBehavior();

	/// <summary>
	/// データセット
	/// </summary>
	void SetData(string posFileName);

	/////////////////////セットゲット関数//////////////////////

	/// <summary>
	/// 自身がいるテニスコートの名前を設定
	/// </summary>
	/// <param name="n">テニスコートの名前</param>
	void SetTennisCourtName(TennisCourtName n) { nowMyCourtName_ = n; }

	/// <summary>
	/// 自身がいるテニスコートの名前を取得
	/// </summary>
	/// <returns>自身がいるテニスコートの名前</returns>
	TennisCourtName GetTennisCourtName() { return nowMyCourtName_; }

	/// <summary>
	/// モデル番号取得
	/// </summary>
	/// <returns>モデル番号</returns>
	int GetModelNum() { return hModel_; } 

	/// <summary>
	/// ラケット取得
	/// </summary>
	/// <returns>ラケット</returns>
	Racket* GetRacket() { return pRacket_; }

	/// <summary>
	/// 状態を取得
	/// </summary>
	/// <returns>状態</returns>
	PlayerStateManager* GetState() { return pState_; }

	/// <summary>
	/// テクニックを取得
	/// </summary>
	/// <returns>テクニック</returns>
	float GetTechnique() { return technique_; }

	/// <summary>
	/// パワーを取得
	/// </summary>
	/// <returns>パワー</returns>
	float GetPower() { return power_; }
};

