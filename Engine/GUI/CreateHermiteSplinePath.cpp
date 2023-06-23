#include "CreateHermiteSplinePath.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../DirectX/Direct3D.h"
#include "../../Base/NormalObject.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "../../Engine/nlohmann/json.hpp"
#include <list>
#include <fstream>

using json = nlohmann::json;
using namespace std;

/// <summary>
/// エルミートスプラインのパス作成
/// </summary>
namespace CreateHermiteSplinePath
{

	//すべてのパスを格納をしておくリスト
	vector<NormalObject*> allPath_;

	//ウィンドウを描画
	bool isWindowDraw_ = false;

	//ウィンドウ描画
	void WindowDraw()
	{
		//window作る
		if (Direct3D::GetWindowHandle() == GetForegroundWindow())
			ImGui::Begin("CreateHermiteSplinePath", NULL);
		else
			ImGui::Begin("CreateHermiteSplinePath", NULL,ImGuiWindowFlags_NoInputs);

		//GUI描画
		AllPathInfoGuiDraw();

		//終わり
		ImGui::End();

	}

	//すべてのパス情報を描画
	void AllPathInfoGuiDraw()
	{
		//セーブボタン
		if (ImGui::Button("AddPath")) AddPath();

		//パスの数カウント用
		int count = 0;

		for (auto i = allPath_.begin(); i != allPath_.end(); i++)
		{
			//iをPathの後ろにたす
			char name[16];
			sprintf_s(name, "Path %d", count++);

			//Path
			if (ImGui::TreeNode(name)) {

				//ポジションを保存しておく
				XMFLOAT3 pos = (*i)->GetComponent<Transform>()->GetPosition();

				//Positionセット
				ImGui::SliderFloat("x", &pos.x, -200.0f, 200.0f);
				ImGui::SliderFloat("y", &pos.y, -200.0f, 200.0f);
				ImGui::SliderFloat("z", &pos.z, -200.0f, 200.0f);

				if (ImGui::TreeNode("InputPosition")) {

					ImGui::Text("x");
					ImGui::InputFloat("x", &pos.x, -200.0f, 200.0f);
					ImGui::Text("y");
					ImGui::InputFloat("y", &pos.y, -200.0f, 200.0f);
					ImGui::Text("z");
					ImGui::InputFloat("z", &pos.z, -200.0f, 200.0f);

					ImGui::TreePop();
				}

				//位置更新
				(*i)->GetComponent<Transform>()->SetPosition(pos);

				ImGui::TreePop();
			}
		}

		//セーブボタン
		if (ImGui::Button("Save")) Save();

		//終了ボタン
		if (ImGui::Button("Close")) ARGUMENT_INITIALIZE(isWindowDraw_, false);

	}

	//パス追加
	void AddPath()
	{
		//パスオブジェクト生成
		NormalObject* pNew = new NormalObject(GameManager::GetpSceneManager(),"Tool/ToolModel/HermiteSplinePath.fbx", "");
		if (GameManager::GetpSceneManager()->GetParent() != nullptr) GameManager::GetpSceneManager()->PushBackChild(pNew);
		pNew->Initialize();

		//ワイヤーフレーム状態にする
		ModelManager::SetShederType(pNew->GetModelNum(), Direct3D::SHADER_UNLIT);

		//パス追加
		allPath_.push_back(pNew);
	}

	//セーブ
	void Save()
	{
		char fileName[MAX_PATH] = "無題.json";  //ファイル名を入れる変数

		//「ファイルを保存」ダイアログの設定
		OPENFILENAME ofn;                         	               //名前をつけて保存ダイアログの設定用構造体
		ZeroMemory(&ofn, sizeof(ofn));            	               //構造体初期化
		ofn.lStructSize = sizeof(OPENFILENAME);   	               //構造体のサイズ
		ofn.lpstrFilter = TEXT("すべてのファイル(*.*)\0*.*\0\0");  //ファイルの種類
		ofn.lpstrFile = fileName;               	               //ファイル名
		ofn.nMaxFile = MAX_PATH;                 	               //パスの最大文字数
		ofn.Flags = OFN_OVERWRITEPROMPT;   		                   //フラグ（同名ファイルが存在したら上書き確認）
		ofn.lpstrDefExt = "json";                  	               //デフォルト拡張子

		//「ファイルを保存」ダイアログ
		BOOL selFile;
		selFile = GetSaveFileName(&ofn);

		//キャンセルしたら中断
		if (selFile == FALSE) return;

		HANDLE hFile_;
		hFile_ = CreateFile(
			fileName,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		CloseHandle(hFile_);

		//書き込み用
		json json_object;

		//パスの数カウント用
		int count = 0;

		//保存したい値を設定
		for (auto i = allPath_.begin(); i != allPath_.end(); i++)
		{
			//iをPathの後ろにたす
			char name[16];
			sprintf_s(name, "Path%d", count++);

			//位置格納
			XMFLOAT3 pos = (*i)->GetComponent<Transform>()->GetPosition();
			json_object[name]["Position"] = { pos.x,pos.y,pos.z };
		}

		//書き込み
		std::ofstream output_file(fileName);
		output_file << json_object;
		output_file.close();
	}

	////////////////////////////////////////セッター・ゲッター////////////////////////////////////////////

	//ウィンドウを描画するか設定
	void SetWindowDraw(bool flag) { isWindowDraw_ = flag; }

	//ウィンドウ描画しているか
	bool isWindowDraw() { return isWindowDraw_; }
}
