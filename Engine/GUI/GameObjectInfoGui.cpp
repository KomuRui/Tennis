#include "GameObjectInfoGui.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "../../Manager/GameManager/GameManager.h"
#include <map>


/// <summary>
/// �Q�[���I�u�W�F�N�g�̏���\������GUI
/// </summary>
namespace GameObjectInfoGui
{
    //���f���ԍ�
    int hModelNum = -1;

    //�e���
    bool isEnable = true;                 //�������ǂ���
    bool isRayHit = true;                 //���C�ɓ����邩�ǂ���
    bool isObstacle = true;               //��Q���Ƃ��ēo�^���邩�ǂ���
    bool isAnim = true;                   //�A�j���[�V�����Đ����邩�ǂ���
    bool isAnimLoop = true;               //�A�j���[�V�������[�v�Đ����邩�ǂ���
    bool isShadow = true;                 //�e���邩�ǂ���
    char objName[50] = {};                //�I�u�W�F�N�g�̖��O�i�[�p
    XMFLOAT3 position;                    //�ʒu
    XMFLOAT3 rotate;                      //��]
    XMFLOAT3 scale;                       //�g��k��
    int shaderType = Direct3D::SHADER_3D; //�V�F�[�_�̌^
    map<int, string> shaderNameTable;     //�V�F�[�_�̌^�ɑ΂��閼�O


    //������
    void Initialize()
    {
        //���ꂼ�ꖼ�O�ݒ�
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

	/// �Q�[���I�u�W�F�N�g�̏���`��
	void GameObjectInfoDraw()
	{

        //window���
        if (Direct3D::GetWindowHandle() == GetForegroundWindow())
            ImGui::Begin("SelectGameObjectInfo", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        else
            ImGui::Begin("SelectGameObjectInfo", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs);

        //���f���ԍ����G���[�l�Ȃ�
        if (hModelNum != -1)
        {
            //���O�ƃg�����X�t�H�[���`��
            NameAndTransformDraw();

            //�F���`��
            ColorInfoDraw();

            //���f�����`��
            ModelInfoDraw();
        }

        //�I���
        ImGui::End();
	}

    //���O�ƃg�����X�t�H�[���`��
    void NameAndTransformDraw()
    {
        /////���O�ƃ`�F�b�N�{�^��
        
        //�I�u�W�F�N�g�̖��O
        ImGui::InputText("objName", &ModelManager::GetModelName(hModelNum)[0], ModelManager::GetModelName(hModelNum).size()); 

        /////�g�����X�t�H�[��
        float windowFontScale = 1.5f;
        ImGui::SetWindowFontScale(windowFontScale);
        ImGui::Text("Transform");  
        ImGui::SetWindowFontScale(1.0f);  

        //�Q�[���I�u�W�F�N�g�擾
        GameObject* p = ModelManager::GetGameObject(hModelNum);

        //�g�����X�t�H�[���R���|�[�l���g������̂Ȃ��
        if (p->GetComponent<Transform>())
        {
            //�ʒu
            XMFLOAT3 xmPos = p->GetComponent<Transform>()->GetPosition();
            float pos[3] = { xmPos.x,xmPos.y,xmPos.z };
            ImGui::DragFloat3("position", pos);
            p->GetComponent<Transform>()->SetPosition(XMFLOAT3(pos[0], pos[1], pos[2]));

            //��]
            XMFLOAT3 xmRotate = p->GetComponent<Transform>()->GetRotate();
            float rotate[3] = { xmRotate.x,xmRotate.y,xmRotate.z };
            ImGui::DragFloat3("rotate", rotate);
            p->GetComponent<Transform>()->SetRotate(XMFLOAT3(rotate[0], rotate[1], rotate[2]));

            //�g��k��
            XMFLOAT3 xmScale = p->GetComponent<Transform>()->GetScale();
            float scale[3] = { xmScale.x,xmScale.y,xmScale.z };
            ImGui::DragFloat3("scale", scale);
            p->GetComponent<Transform>()->SetScale(XMFLOAT3(scale[0], scale[1], scale[2]));
        }
    }

    //�F���`��
    void ColorInfoDraw()
    {
        float windowFontScale = 1.5f;
        ImGui::SetWindowFontScale(windowFontScale);
        ImGui::Text("Color");
        ImGui::SetWindowFontScale(1.0f);

        //�A���r�G���g
        if (ImGui::TreeNode("AmbientColor")) {
           
            XMFLOAT4 xmColor = ModelManager::GetAmbient(hModelNum);
            float color[4] = { xmColor.x,xmColor.y,xmColor.z,xmColor.w };
            ImGui::ColorPicker4("AmbientColor", color, ImGuiColorEditFlags_PickerHueWheel);
            ModelManager::SetAmbient(hModelNum, XMFLOAT4(color[0], color[1], color[2], color[3]));

            ImGui::TreePop();
        }

        //�X�y�L�����[
        if (ImGui::TreeNode("SpeculerColor")) {

            XMFLOAT4 xmColor = ModelManager::GetSpeculer(hModelNum);
            float color[4] = { xmColor.x,xmColor.y,xmColor.z,xmColor.w };
            ImGui::ColorPicker4("SpeculerColor", color, ImGuiColorEditFlags_PickerHueWheel);
            ModelManager::SetSpeculer(hModelNum, XMFLOAT4(color[0], color[1], color[2], color[3]));

            ImGui::TreePop();
        }

    }

    //���f�����`��
    void ModelInfoDraw()
    {
        float windowFontScale = 1.5f;
        ImGui::SetWindowFontScale(windowFontScale);
        ImGui::Text("ModelInfo");
        ImGui::SetWindowFontScale(1.0f);

        //�`�F�b�N�{�b�N�X
        ImGui::Checkbox("isEnable", &isEnable);      //�����ɂ��邩�ǂ���           
        ImGui::Checkbox("isRayHit", &isRayHit);      //���C�ɓ����邩�ǂ���
        ImGui::Checkbox("isObstacle", &isObstacle);  //��Q���Ƃ��ēo�^���邩�ǂ���
        ImGui::Checkbox("isAnim", &isAnim);          //�A�j���[�V�����Đ����邩�ǂ���
        ImGui::Checkbox("isAnimLoop", &isAnimLoop);  //�A�j���[�V�������[�v�Đ����邩�ǂ���
        ImGui::Checkbox("isShadow", &isShadow);      //�e�t���邩�ǂ���

        //�h���b�O
        float a = 1;
        ImGui::DragFloat("alpha", &a);        //�����x
        ImGui::DragFloat("brightness", &a);   //���邳
        ImGui::DragFloat("uvScroll", &a);     //uvScroll�̒l

        //�V�F�[�_�[
        ImGui::SetWindowFontScale(windowFontScale);
        ImGui::Text("Shader");
        ImGui::SetWindowFontScale(1.0f);

        //�ǂ̃V�F�[�_���g���Ă��邩�\��
        string s = "Use : " + shaderNameTable[shaderType];
        ImGui::Text(s.c_str());

        //�X�N���[���o�[(�ǂ̃V�F�[�_���g�����I�ׂ�悤�ɂ��邽��)
        ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(300, 200), ImGuiWindowFlags_NoTitleBar);
        for (int i = 0; i < Direct3D::SHADER_MAX; i++) {
            ImGui::RadioButton(shaderNameTable[i].c_str(), &shaderType, i);
        }

        ImGui::EndChild();
    }

    //���f���ݒ�
    void SetModel(int ModelNum)
    {
        if (ModelNum == hModelNum || ModelNum < 0)
        {
            return;
        }

        //���f���ݒ�
        ARGUMENT_INITIALIZE(hModelNum, ModelNum);
    }
}