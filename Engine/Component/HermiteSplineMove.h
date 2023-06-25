#pragma once
#include "../ResourceManager/Global.h"
#include <vector>

/// <summary>
/// エルミートスプライン曲線を使った動き 
/// </summary>
class HermiteSplineMove
{

	vector<pair<XMFLOAT3, XMFLOAT3>> pathData_; //移動する時に使うパスデータ

	int timerhNum_;     //タイマーのハンドル番号
	float moveTime_;    //移動時間
	float nowTime_;     //現在の時間

	int nowLookValue_;	//現在見ている値
		
	bool isMove_;		//動くかどうか
	bool isFinish_;     //終わったかどうか

public:

	//コンストラクタ
	HermiteSplineMove();

	//デストラクタ
	~HermiteSplineMove();

	/// <summary>
	/// 更新
	/// </summary>
	/// <returns>現在地</returns>
	XMFLOAT3 Updata();

	/// <summary>
	/// データ追加
	/// </summary>
	/// <param name="pos">パスの位置</param>
	/// <param name="tangent">正接ベクトル(開始パスの際だけ必要)</param>
	void AddPath(XMFLOAT3 pos, XMFLOAT3 tangent = { ZERO,ZERO,ZERO }) { pathData_.push_back({ pos,tangent }); }

	//最初から開始
	void ReStart();

	//開始
	void Start() { isMove_ = true; }

	//停止
	void Stop() { isMove_ = false; }

	//データリセット
	void ResetData() { pathData_.clear(); }

	//終わったかどうか取得
	bool IsFinish() { return isFinish_; }
};

