#include "GameObjectInfoGui.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "../../Manager/GameManager/GameManager.h"

/// <summary>
/// ゲームオブジェクトの情報を表示するGUI
/// </summary>
namespace GameObjectInfoGui
{
    //モデル番号
    int hModelNum = -1;

    //各情報
    bool isEnable = true;   //透明かどうか
    char objName[50] = {};  //オブジェクトの名前格納用
    XMFLOAT3 position;      //位置
    XMFLOAT3 rotate;        //回転
    XMFLOAT3 scale;         //拡大縮小

	/// ゲームオブジェクトの情報を描画
	void GameObjectInfoDraw()
	{
        //window作る
        if (Direct3D::GetWindowHandle() == GetForegroundWindow())
            ImGui::Begin("SelectGameObjectInfo", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        else
            ImGui::Begin("SelectGameObjectInfo", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs);

        //名前とトランスフォーム描画
        NameAndTransformDraw();

        //色情報描画
        ColorInfoDraw();

        //終わり
        ImGui::End();
	}

    //名前とトランスフォーム描画
    void NameAndTransformDraw()
    {
        /////名前とチェックボタン
        ImGui::Checkbox("isEnable", &isEnable);                //透明にするかどうか
        ImGui::InputText("objName", objName, sizeof(objName)); //オブジェクトの名前

        /////トランスフォーム
        float windowFontScale = 1.5f;
        ImGui::SetWindowFontScale(windowFontScale);
        ImGui::Text("Transform");  
        ImGui::SetWindowFontScale(1.0f);  

        //位置
        float pos[3] = { 0,0 ,0 };
        ImGui::DragFloat3("position", pos);

        //回転
        float rotate[3] = { 0,0,0 };
        ImGui::DragFloat3("rotate", rotate);

        //拡大縮小
        float scale[3] = { 0,0,0 };
        ImGui::DragFloat3("scale", scale);
    }

    //色情報描画
    void ColorInfoDraw()
    {

    }
}