#include "GameObjectInfoGui.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "../../Manager/GameManager/GameManager.h"
#include <map>


/// <summary>
/// ゲームオブジェクトの情報を表示するGUI
/// </summary>
namespace GameObjectInfoGui
{
    //モデル番号
    int hModelNum = -1;

    //各情報
    bool isEnable = true;                 //透明かどうか
    bool isRayHit = true;                 //レイに当たるかどうか
    bool isObstacle = true;               //障害物として登録するかどうか
    bool isAnim = true;                   //アニメーション再生するかどうか
    bool isAnimLoop = true;               //アニメーションループ再生するかどうか
    bool isShadow = true;                 //影つけるかどうか
    char objName[50] = {};                //オブジェクトの名前格納用
    XMFLOAT3 position;                    //位置
    XMFLOAT3 rotate;                      //回転
    XMFLOAT3 scale;                       //拡大縮小
    int shaderType = Direct3D::SHADER_3D; //シェーダの型
    map<int, string> shaderNameTable;     //シェーダの型に対する名前


    //初期化
    void Initialize()
    {
        //それぞれ名前設定
        ARGUMENT_INITIALIZE(shaderNameTable[Direct3D::SHADER_3D], "SHADER_3D");
        ARGUMENT_INITIALIZE(shaderNameTable[Direct3D::SHADER_2D], "SHADER_2D");
        ARGUMENT_INITIALIZE(shaderNameTable[Direct3D::SHADER_UNLIT], "SHADER_UNLIT");
        ARGUMENT_INITIALIZE(shaderNameTable[Direct3D::SHADER_BILLBOARD], "SHADER_BILLBOARD");
        ARGUMENT_INITIALIZE(shaderNameTable[Direct3D::SHADER_SIGNBOARD], "SHADER_SIGNBOARD");
        ARGUMENT_INITIALIZE(shaderNameTable[Direct3D::SHADER_FADE_IN], "SHADER_FADE_IN");
        ARGUMENT_INITIALIZE(shaderNameTable[Direct3D::SHADER_FADE_OUT], "SHADER_FADE_OUT");
        ARGUMENT_INITIALIZE(shaderNameTable[Direct3D::SHADER_REVERS_COLOR], "SHADER_REVERS_COLOR");
        ARGUMENT_INITIALIZE(shaderNameTable[Direct3D::SHADER_NORMALMAP], "SHADER_NORMALMAP");
        ARGUMENT_INITIALIZE(shaderNameTable[Direct3D::SHADER_OUTLINE], "SHADER_OUTLINE");
        ARGUMENT_INITIALIZE(shaderNameTable[Direct3D::SHADER_SHADOW], "SHADER_SHADOW");
    }

	/// ゲームオブジェクトの情報を描画
	void GameObjectInfoDraw()
	{

        //window作る
        if (Direct3D::GetWindowHandle() == GetForegroundWindow())
            ImGui::Begin("SelectGameObjectInfo", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        else
            ImGui::Begin("SelectGameObjectInfo", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs);

        //モデル番号がエラー値なら
        if (hModelNum != -1)
        {
            //名前とトランスフォーム描画
            NameAndTransformDraw();

            //色情報描画
            ColorInfoDraw();

            //モデル情報描画
            ModelInfoDraw();
        }

        //終わり
        ImGui::End();
	}

    //名前とトランスフォーム描画
    void NameAndTransformDraw()
    {
        /////名前とチェックボタン
        
        //オブジェクトの名前
        ImGui::InputText("objName", &ModelManager::GetModelName(hModelNum)[0], ModelManager::GetModelName(hModelNum).size()); 

        /////トランスフォーム
        float windowFontScale = 1.5f;
        ImGui::SetWindowFontScale(windowFontScale);
        ImGui::Text("Transform");  
        ImGui::SetWindowFontScale(1.0f);  

        //ゲームオブジェクト取得
        GameObject* p = ModelManager::GetGameObject(hModelNum);

        //トランスフォームコンポーネントがあるのならば
        if (p->GetComponent<Transform>())
        {
            //位置
            XMFLOAT3 xmPos = p->GetComponent<Transform>()->GetPosition();
            float pos[3] = { xmPos.x,xmPos.y,xmPos.z };
            ImGui::DragFloat3("position", pos);
            p->GetComponent<Transform>()->SetPosition(XMFLOAT3(pos[0], pos[1], pos[2]));

            //回転
            XMFLOAT3 xmRotate = p->GetComponent<Transform>()->GetRotate();
            float rotate[3] = { xmRotate.x,xmRotate.y,xmRotate.z };
            ImGui::DragFloat3("rotate", rotate);
            p->GetComponent<Transform>()->SetRotate(XMFLOAT3(rotate[0], rotate[1], rotate[2]));

            //拡大縮小
            XMFLOAT3 xmScale = p->GetComponent<Transform>()->GetScale();
            float scale[3] = { xmScale.x,xmScale.y,xmScale.z };
            ImGui::DragFloat3("scale", scale);
            p->GetComponent<Transform>()->SetScale(XMFLOAT3(scale[0], scale[1], scale[2]));
        }
    }

    //色情報描画
    void ColorInfoDraw()
    {
        float windowFontScale = 1.5f;
        ImGui::SetWindowFontScale(windowFontScale);
        ImGui::Text("Color");
        ImGui::SetWindowFontScale(1.0f);

        //アンビエント
        if (ImGui::TreeNode("AmbientColor")) {
           
            XMFLOAT4 xmColor = ModelManager::GetAmbient(hModelNum);
            float color[4] = { xmColor.x,xmColor.y,xmColor.z,xmColor.w };
            ImGui::ColorPicker4("AmbientColor", color, ImGuiColorEditFlags_PickerHueWheel);
            ModelManager::SetAmbient(hModelNum, XMFLOAT4(color[0], color[1], color[2], color[3]));

            ImGui::TreePop();
        }

        //スペキュラー
        if (ImGui::TreeNode("SpeculerColor")) {

            XMFLOAT4 xmColor = ModelManager::GetSpeculer(hModelNum);
            float color[4] = { xmColor.x,xmColor.y,xmColor.z,xmColor.w };
            ImGui::ColorPicker4("SpeculerColor", color, ImGuiColorEditFlags_PickerHueWheel);
            ModelManager::SetSpeculer(hModelNum, XMFLOAT4(color[0], color[1], color[2], color[3]));

            ImGui::TreePop();
        }

    }

    //モデル情報描画
    void ModelInfoDraw()
    {
        float windowFontScale = 1.5f;
        ImGui::SetWindowFontScale(windowFontScale);
        ImGui::Text("ModelInfo");
        ImGui::SetWindowFontScale(1.0f);

        //チェックボックス
        ImGui::Checkbox("isEnable", &isEnable);      //透明にするかどうか           
        ImGui::Checkbox("isRayHit", &isRayHit);      //レイに当たるかどうか
        ImGui::Checkbox("isObstacle", &isObstacle);  //障害物として登録するかどうか
        ImGui::Checkbox("isAnim", &isAnim);          //アニメーション再生するかどうか
        ImGui::Checkbox("isAnimLoop", &isAnimLoop);  //アニメーションループ再生するかどうか
        ImGui::Checkbox("isShadow", &isShadow);      //影付けるかどうか

        //ドラッグ
        float a = 1;
        ImGui::DragFloat("alpha", &a);        //透明度
        ImGui::DragFloat("brightness", &a);   //明るさ
        ImGui::DragFloat("uvScroll", &a);     //uvScrollの値

        //シェーダー
        ImGui::SetWindowFontScale(windowFontScale);
        ImGui::Text("Shader");
        ImGui::SetWindowFontScale(1.0f);

        //どのシェーダを使っているか表示
        string s = "Use : " + shaderNameTable[shaderType];
        ImGui::Text(s.c_str());

        //スクロールバー(どのシェーダを使うか選べるようにするため)
        ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(300, 200), ImGuiWindowFlags_NoTitleBar);
        for (int i = 0; i < Direct3D::SHADER_MAX; i++) {
            ImGui::RadioButton(shaderNameTable[i].c_str(), &shaderType, i);
        }

        ImGui::EndChild();
    }

    //モデル設定
    void SetModel(int ModelNum)
    {
        if (ModelNum == hModelNum || ModelNum < 0)
        {
            return;
        }

        //モデル設定
        ARGUMENT_INITIALIZE(hModelNum, ModelNum);
    }
}