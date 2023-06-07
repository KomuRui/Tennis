#pragma once
#include "../Base/NormalObject.h"
#include "../Engine/GameObject/GameObject.h"
#include "../State/PlayerState/PlayerStateManager.h"
#include "../Engine/ResourceManager/ModelManager.h"
#include "../Engine/Component/Transform/Transform.h"

class Racket;

/// <summary>
/// Playerの基底クラス
/// </summary>
class PlayerBase : public NormalObject
{
protected:

	///////////////キャラの必要な情報///////////////////

	Racket* pRacket_;                   //ラケット
	PlayerStateManager* pState_;        // Playerの状態を表す変数

	/////////////////////カメラ//////////////////////

	XMVECTOR camVec_;                   //Playerからカメラまでのベクトル
	XMVECTOR camVec2_;                   //Playerからカメラまでのベクトル

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

	/////////////////////セットゲット関数//////////////////////

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
};

