#pragma once
#include "../../OtherObject/TitleScene/TennisCourt.h"

class PlayerBase;

//テニスボールが飛んでいく基準点を管理している名前空間
namespace BasePointManager
{
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 基準点モデルを生成
	/// </summary>
	void InstantiateBasePointModel();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 基準点エクスポート
	/// </summary>
	void BasePointExport();

	/// <summary>
	/// 基準点を取得
	/// </summary>
	/// <param name="name">基準点の名前</param>
	/// <param name="TennisCourtName">基準点を取得したいコートの名前</param>
	/// <returns>基準点</returns>
	XMFLOAT3 GetBasePoint(string name, TennisCourtName isPlayer);

	/// <summary>
	/// 基準点をランダムに取得
	/// </summary>
	/// <param name="TennisCourtName">基準点を取得したいコートの名前</param>
	/// <returns>基準点</returns>
	XMFLOAT3 GetRandomBasePoint(TennisCourtName n);

	/// <summary>
	/// 入力に対する基準点の名前を取得
	/// </summary>
	/// <returns>基準点の名前</returns>
	string GetInputBasePoint(PlayerBase* p);

	/// <summary>
	/// 入力に対する基準点の名前を取得(ラリー中)
	/// </summary>
	/// <returns>基準点の名前</returns>
	string GetRallyInputBasePoint(PlayerBase* p);

	/// <summary>
	/// 入力に対する基準点の名前を取得(サーブレシーブ中)
	/// </summary>
	/// <returns>基準点の名前</returns>
	string GetServeReceiveInputBasePoint(PlayerBase* p);

	/// <summary>
	/// 基準点の名前をランダムに取得
	/// </summary>
	/// <returns>基準点の名前</returns>
	string GetRandomBasePointName();
};

