#include "FrameWorkUpdateManager.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/ResourceManager/VFX.h"
#include "../GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/GUI/ImGuiSet.h"

//フレームワーク管理するとこと
namespace FrameWorkUpdateManager
{
	//更新
	void Update(GameObject *root)
	{

		//入力（キーボード、マウス、コントローラー）情報を更新
		Input::Update();

		//時間止めていないのなら
		if (!Direct3D::GetTimeScale())
		{
			//タイム更新
			Time::Update();

			//全オブジェクトの更新処理
			//ルートオブジェクトのUpdateを呼んだあと、自動的に子、孫のUpdateが呼ばれる
			root->StartUpdateSub();
			root->UpdateSub();
		}

		//マネージャの更新処理を呼ぶ
		GameManager::Update();

		//時間止めていないかエフェクトエディタモードなら
		if (!Direct3D::GetTimeScale() || ImGuiSet::GetScreenMode() == static_cast<int>(Mode::EFFECT_EDIT))
		{
			//エフェクトの更新
			VFX::Update();
		}

		//カメラの更新
		Camera::Update();

		//描画
		Draw(root);
	}

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(GameObject* root)
	{
		//プレイ人数のよって処理を分ける
		switch (GameManager::GetPlayers())
		{

		//一人プレイ
		case Players::ONE:
			OnePlayerDraw(root);
			break;

		//二人プレイ
		case Players::TWO:
			TwoPlayerDraw(root);
			break;

		//それ以外
		default:
			break;
		}

		//プロジェクションを更新
		Camera::SetProj(Direct3D::vp.Width, Direct3D::vp.Height);

		//描画開始
		Direct3D::SetViewPort(Direct3D::vp);

		//エフェクトエディタモードじゃないのなら
		if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
		{
			//様々な描画処理をする
			GameManager::Draw();
		}
		
		//ゲーム画面のサイズごとの各GUI描画
		Direct3D::GetGameFull() ? ImGuiSet::GameScreenFullDraw()
								: ImGuiSet::GameScreenNotFullDraw();
		//描画終了
		Direct3D::EndDraw();

		//二つ目のウィンドウ描画
		TwoWindowDraw(root);
	}

	/// <summary>
	/// 二つ目のウィンドウ描画
	/// </summary>
	void TwoWindowDraw(GameObject* root)
	{
		//二つ目のウィンドウ描画
		Camera::TwoWindowUpdate();
		Direct3D::BeginDrawTwo();
		root->TwoWindowDrawSub();

		//GUI表示
		ImGuiSet::TwoWindowDraw();

		//描画終了
		Direct3D::EndDraw();
	}

	/// <summary>
	/// 一人プレイの描画
	/// </summary>
	void OnePlayerDraw(GameObject* root)
	{
		//プロジェクションを更新
		Camera::SetProj(Direct3D::vp.Width, Direct3D::vp.Height);

		//ビューポート設定
		Direct3D::SetViewPort(Direct3D::vp);
		Direct3D::SetClipToUv(Direct3D::vp);
		
		//先に影用のテクスチャを作成
		ShadowDraw(root);

		//描画開始
		Direct3D::BeginDraw();

		//エフェクトエディタモードじゃないのなら
		if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
			root->DrawSub();

		//エフェクトの描画
		VFX::Draw();

		//エフェクトエディタモードじゃないのなら
		if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
		{
			//透明・半透明描画
			root->TransparentDrawSub();

			//様々な描画処理をする
			GameManager::Draw();
		}

	}

	/// <summary>
	/// 二人プレイの描画
	/// </summary>
	void TwoPlayerDraw(GameObject* root)
	{
		/////////////左

		//プロジェクションとビューポートを更新
		Camera::SetProj(Direct3D::vpLeft.Width, Direct3D::vpLeft.Height);
		Direct3D::SetViewPort(Direct3D::vpLeft);
		Direct3D::SetClipToUv(Direct3D::vpLeft);

		//影描画
		ShadowDraw(root);

		//描画開始
		Direct3D::BeginDraw();

		//エフェクトエディタモードじゃないのなら
		if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
			root->DrawSub();

		//エフェクトの描画
		VFX::Draw();

		//エフェクトエディタモードじゃないのなら
		if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
		{
			//透明・半透明描画
			root->TransparentDrawSub();
		}

		/////////////右

		//カメラ替える
		XMFLOAT3 pos = Camera::GetPosition();
		XMFLOAT3 tar = Camera::GetTarget();
		XMVECTOR up = Camera::GetUp();
		Camera::SetPosition(Camera::GetPositionTwo());
		Camera::SetTarget(Camera::GetTargetTwo());
		Camera::SetUpDirection(Camera::GetUpTwo());
		Camera::UpdateTwo();

		//プロジェクションとビューポートを更新
		Camera::SetProj(Direct3D::vpRight.Width, Direct3D::vpRight.Height);
		Direct3D::SetViewPort(Direct3D::vpRight);

		//エフェクトエディタモードじゃないのなら
		if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
			root->DrawSub();

		//エフェクトの描画
		VFX::Draw();

		//エフェクトエディタモードじゃないのなら
		if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
		{
			//透明・半透明描画
			root->TransparentDrawSub();
		}

		Camera::SetPosition(pos);
		Camera::SetTarget(tar);
		Camera::SetUpDirection(up);
	}

	/// <summary>
	/// 影描画
	/// </summary>
	void ShadowDraw(GameObject* root)
	{
		//影描画開始
		ARGUMENT_INITIALIZE(Direct3D::isShadowDraw, true);

		//シャドウマップ作成
		//ライトの位置から見た画像を、遠くは白、近くは黒のグレースケールで表す
		XMFLOAT3 pos = Camera::GetPosition();
		XMFLOAT3 tar = Camera::GetTarget();
		XMVECTOR up = Camera::GetUp();
		Camera::SetPosition(XMFLOAT3(-25, 20, -25));
		Camera::SetTarget(XMFLOAT3(0, 0, 0));
		Camera::SetUpDirection(XMVectorSet(0,0,1,0));
		Camera::FrameCameraInitialize();
		Camera::UpdateTwo();
		Direct3D::lightView_ = Camera::GetViewMatrix();

		Direct3D::BrginDrawShadowToTexture();

		//オブジェクトの影描画
		root->ShadowDraw();

		//エフェクトの描画
		VFX::Draw();

		//エフェクトエディタモードじゃないのなら
		if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
		{
			//透明・半透明描画
			root->TransparentDrawSub();
		}

		//描画終了
		Direct3D::EndDraw();

		//カメラ元に戻す
		Camera::SetPosition(pos);
		Camera::SetTarget(tar);
		Camera::SetUpDirection(up);
		Camera::FrameCameraInitialize();
		Camera::UpdateTwo();

		//影描画終了
		ARGUMENT_INITIALIZE(Direct3D::isShadowDraw, false);
	}

};

