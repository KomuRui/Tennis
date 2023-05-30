#include "GameObjectInfoGui.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "../../Manager/GameManager/GameManager.h"

/// <summary>
/// �Q�[���I�u�W�F�N�g�̏���\������GUI
/// </summary>
namespace GameObjectInfoGui
{
    //���f���ԍ�
    int hModelNum = -1;

    //�e���
    bool isEnable = true;   //�������ǂ���
    char objName[50] = {};  //�I�u�W�F�N�g�̖��O�i�[�p
    XMFLOAT3 position;      //�ʒu
    XMFLOAT3 rotate;        //��]
    XMFLOAT3 scale;         //�g��k��

	/// �Q�[���I�u�W�F�N�g�̏���`��
	void GameObjectInfoDraw()
	{
        //window���
        if (Direct3D::GetWindowHandle() == GetForegroundWindow())
            ImGui::Begin("SelectGameObjectInfo", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        else
            ImGui::Begin("SelectGameObjectInfo", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs);

        //���O�ƃg�����X�t�H�[���`��
        NameAndTransformDraw();

        //�F���`��
        ColorInfoDraw();

        //�I���
        ImGui::End();
	}

    //���O�ƃg�����X�t�H�[���`��
    void NameAndTransformDraw()
    {
        /////���O�ƃ`�F�b�N�{�^��
        ImGui::Checkbox("isEnable", &isEnable);                //�����ɂ��邩�ǂ���
        ImGui::InputText("objName", objName, sizeof(objName)); //�I�u�W�F�N�g�̖��O

        /////�g�����X�t�H�[��
        float windowFontScale = 1.5f;
        ImGui::SetWindowFontScale(windowFontScale);
        ImGui::Text("Transform");  
        ImGui::SetWindowFontScale(1.0f);  

        //�ʒu
        float pos[3] = { 0,0 ,0 };
        ImGui::DragFloat3("position", pos);

        //��]
        float rotate[3] = { 0,0,0 };
        ImGui::DragFloat3("rotate", rotate);

        //�g��k��
        float scale[3] = { 0,0,0 };
        ImGui::DragFloat3("scale", scale);
    }

    //�F���`��
    void ColorInfoDraw()
    {

    }
}