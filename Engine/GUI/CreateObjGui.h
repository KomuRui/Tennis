#pragma once


/// <summary>
/// オブジェクト作成用GUI
/// </summary>
namespace CreateObjGui
{
	////////////////////////////////////オブジェクト作成用ImGui///////////////////////////////////////

	/// <summary>
	/// オブジェクト作成するImGuiのUIを出してくれる
	/// </summary>
	void ObjectCreater();

	/// <summary>
	/// 自作3Dオブジェクト作成
	/// </summary>
	void CreateSelfMade3D();

	/// <summary>
	/// 3Dオブジェクト作成(丸、四角、カプセル、床とか)
	/// </summary>
	void CreateNormal3D();

	/// <summary>
	/// 画像作成
	/// </summary>
	void CreateImage();

	/// <summary>
	/// 看板作成
	/// </summary>
	void CreateSigeboard();

	/// <summary>
	/// カメラの遷移作成(コライダーに当たったらカメラのポジション変える機能)
	/// </summary>
	void CreateCameraTransition();

}