#pragma once
#include "GameObject.h"
#include "../ResourceManager/ModelManager.h"

//-----------------------------------------------------------
//カメラ
//-----------------------------------------------------------
namespace Camera
{
	//初期化（プロジェクション行列作成）
	void Initialize();

	//更新（ビュー行列作成）
	void Update();
	void TwoWindowUpdate();
	void UpdateTwo();

	//カメラの振動
	XMFLOAT3 Vibration();

	//補間移動
	void InterpolationMove(const XMFLOAT3& pos, const XMFLOAT3& tar, const float& factor);

	//カメラをマウスで移動(フレームワーク上でのシーン画面の時だけ)
	void CamMouseMove();

	//視点（カメラの位置）を設定
	void SetPosition(const XMFLOAT3& position);
	void SetPositionTwo(const XMFLOAT3& position);
	void TwoWindowSetPosition(const XMFLOAT3& position);

	//焦点（見る位置）を設定
	void SetTarget(const XMFLOAT3& target);
	void SetTargetTwo(const XMFLOAT3& target);
	void TwoWindowSetTarget(const XMFLOAT3& target);

	//上方向のベクトルを設定
	void SetUpDirection(XMVECTOR direction);
	void SetUpDirectionTwo(XMVECTOR direction);
	void SetTwoWindowUpDirection(XMVECTOR direction);

	//画角を設定
	void SetFieldAngle(int angle);

	//カメラ振動を設定
	//引数 : 振動の強さ
	void SetCameraVibration(float strength, float attenuation = 0.01f);

	//エフェクトエディタのカメラにセット
	void SetEffectEditCamera();

	//プロジェクション行列をセット
	void SetProj(float width, float height);

	//画角を元に戻す
	void UndoFiledAngle();

	//ゲームシーンの画角を保存しておく
	void KeepGameSceneFieldAngle(int angle);

	//フレームワーク上のカメラを初期化
	void FrameCameraInitialize();

	//二つ目のウィンドウでレイキャストした時のデータを取得
	RayCastData GetTwoWindowClickRayCastData();

	//位置を取得
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetPositionTwo();
	XMFLOAT3 GetPositionF();

	//焦点を取得
	XMFLOAT3 GetTarget();
	XMFLOAT3 GetTargetTwo();
	XMFLOAT3 GetTargetF();

	//上ベクトルを取得
	XMVECTOR GetUp();
	XMVECTOR GetUpTwo();

	//ビュー行列を取得
	XMMATRIX GetViewMatrix();

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix();

	//ビルボード用回転行列を取得
	XMMATRIX GetBillboardMatrix();

	//スクリーン座標を取得
	XMFLOAT3 GetScreenPosition(XMFLOAT3 pos3d);
};