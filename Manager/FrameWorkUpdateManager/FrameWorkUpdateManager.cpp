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
		Camera::Update2();
		Direct3D::BeginDrawTwo();
		root->TwoWindowDrawSub();

		//GUI表示
		ImGuiSet::TwoWindowDraw();

		//描画終了
		Direct3D::EndDraw();
	}
};

