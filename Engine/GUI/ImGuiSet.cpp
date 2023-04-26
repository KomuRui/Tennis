#include "../ResourceManager/Image.h"
#include "../ResourceManager/CreateStage.h"
#include "../DirectX/Input.h"
#include "ImGuiSet.h"
#include "../ResourceManager/Model.h"
#include "../Collider/SphereCollider.h"
#include "imgui/imgui.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "../../Base/Mob.h"
#include "../../UI/ImageBase.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"
#include "../ResourceManager/VFX.h"
#include "../GameObject/Camera.h"
#include "../DirectX/Fbx.h"
#include <fstream>
#include <vector>
#include <windows.h>
#include <psapi.h>

//�萔
namespace
{
    static const int MAX_DEBUG_LOG_NUM = 1000; //�f�o�b�O���O�̍ő��
}

/// <summary>
/// Debug�p��UI��\������
/// </summary>
namespace ImGuiSet
{
    ////////////////////////////////////�X�e�[�W�쐬�pImGui///////////////////////////////////////

    //�e�I�u�W�F�N�g�̕K�v�ȕϐ�
    int objectStatus_[MAX_OBJECT_SIZE] = {};
    Mob* pNewObject_[MAX_OBJECT_SIZE];
    XMFLOAT3 objectPos_[MAX_OBJECT_SIZE];
    XMFLOAT3 objectRotate_[MAX_OBJECT_SIZE];
    XMFLOAT3 objectScale_[MAX_OBJECT_SIZE];

    //�e�Ŕ̕K�v�ȕϐ�
    int sigeboardStatus_[MAX_OBJECT_SIZE] = {};
    //Signboard* pNewSigeboard_[MAX_OBJECT_SIZE];
    XMFLOAT3 sigeboardPos_[MAX_OBJECT_SIZE];
    XMFLOAT3 sigeboardRotate_[MAX_OBJECT_SIZE];
    XMFLOAT3 sigeboardScale_[MAX_OBJECT_SIZE];

    //�e�J�����J�ڂ̕K�v�ȕϐ�
    int cameraTransitionStatus_[MAX_OBJECT_SIZE] = {};
    Mob* pNewCameraTransition_[MAX_OBJECT_SIZE];
    XMFLOAT3 cameraTransitionPos_[MAX_OBJECT_SIZE];
    XMFLOAT3 cameraPos_[MAX_OBJECT_SIZE];
    XMFLOAT3 cameraTar_[MAX_OBJECT_SIZE];
    XMFLOAT3 colliderSize_[MAX_OBJECT_SIZE];

    //�e�摜�̕K�v�ȕϐ�
    int imageStatus_[MAX_OBJECT_SIZE] = {};
    ImageBase* pNewImage_[MAX_OBJECT_SIZE];
    XMFLOAT3 imagePos_[MAX_OBJECT_SIZE];
    XMFLOAT3 imageRotate_[MAX_OBJECT_SIZE];
    XMFLOAT3 imageScale_[MAX_OBJECT_SIZE];

    //�G�t�F�N�g�̕K�v�ȕϐ�
    EmitterData data;
    int effectNum = -1;
    std::string textureFileName_ = "Image/Effect/flashB_B.png";//�摜�t�@�C����
    XMFLOAT3 position_ = XMFLOAT3(0,0,0);		               //�ʒu
    XMFLOAT3 positionRnd_ = XMFLOAT3(4, 4, 4);	               //�ʒu�̌덷
    XMFLOAT3 direction_ = XMFLOAT3(-1, 0, -1);		           //�p�[�e�B�N���̈ړ�����
    XMFLOAT3 directionRnd_ = XMFLOAT3(0, 0, 0);	               //�ړ������̌덷�i�e���̊p�x�j
    float	 speed_ = 0.2f;			                           //1�t���[���̑��x
    float	 speedRnd_ = 0.8f;	                               //���x�덷�i0�`1�j
    float	 accel_ = 1.0f;			                           //�����x
    float	 gravity_ = 0.0f;		                           //�d��
    XMFLOAT4 color_ = XMFLOAT4(1, 1, 0, 1);			           //�F�iRGBA 0�`1�j
    XMFLOAT4 deltaColor_ = XMFLOAT4(0, -0.05f, 0, -0.033f);	   //�F�̕ω���
    XMFLOAT3 rotate_ = XMFLOAT3(0, 0, 0);	 	               //�e���ł̊p�x
    XMFLOAT3 rotateRnd_ = XMFLOAT3(0, 0, 0);	 	           //�p�x�덷
    XMFLOAT3 spin_ = XMFLOAT3(0, 0, 5);	 		               //��]���x
    XMFLOAT2 size_ = XMFLOAT2(1.2f, 1.2f);			           //�T�C�Y
    XMFLOAT2 sizeRnd_ = XMFLOAT2(0.4f, 0.4f);	               //�T�C�Y�덷�i0�`1�j
    XMFLOAT2 scale_ = XMFLOAT2(1.05f, 1.05f);			       //1�t���[���̊g�嗦
    float    lifeTime_ = 180.0f;		                       //�p�[�e�B�N���̎����i�t���[�����j
    int delay_ = 1;			                                   //���t���[�������Ƀp�[�e�B�N���𔭐������邩
    int number_ = 2;				                           //1�x�ɏo���p�[�e�B�N����
    bool isBillBoard_ = true;	                               //�r���{�[�h���ǂ���

    //�\���������I�u�W�F�N�g���i�[����ꏊ
    //first->���f���ԍ�
    //second->���f���ԍ����Ƃ̃g�����X�t�H�[��
    std::vector<std::pair<int, Transform>>obj_;

    //first->��������ǂ���
    //second->���������
    std::pair<bool, int> create3D_;               //3D�I�u�W�F�N�g
    std::pair<bool, int> createSigeboard_;        //�Ŕ�
    std::pair<bool, int> createCameraTransition_; //�J�����J��
    std::pair<bool, int> createImage_;            //�摜

    //�e�V�[���̃X�e�[�W��񂪓����Ă�t�@�C���̃p�X
    const char* stageInfoFilePath_[SCENE_ID_MAX];

    //////////////////////////////�X�e�[�W�̃I�u�W�F�N�g�̃g�����X�t�H�[���\��////////////////////////////

    //�I�u�W�F�N�g�̐�
    int objectCount_;

    //////////////////////////////////////���O�\��///////////////////////////////////////

    /// <summary>
    ///���O�\�����邽�߂�vector
    /// </summary>
    ///first->�ϐ��̖��O
    ///second->�l
    std::vector<std::pair<std::string, std::string>> variable_;

    //////////////////////////////////////�v���Z�X�������\��///////////////////////////////////////

    float processMemory_[500] = { 0 };

    ///////////////////////////////�Q�[����ʐݒ�///////////////////////////////////////

    //0->�Q�[����� 1->�V�[����� 2->�G�t�F�N�g�G�f�B�^���
    int screenMode_;

    //3->�X�^�[�g 4->�X�g�b�v
    int gameMode_;

    //�Q�[����ʂ��t���T�C�Y���ǂ���
    bool isGameScreenFull_;

    //�w�i�F
    XMFLOAT4 backScreenColor_ = XMFLOAT4(0, 0, 0, 0);

    //�G�t�F�N�g�G�f�B�^�̎��̕\�����郂�f��
    Fbx* pBaseFbx = new Fbx;
    Fbx* pStickFbx = new Fbx;

    //////////////////////////////////////�t�@�C��(�C���|�[�g�E�G�N�X�|�[�g)///////////////////////////////////////
    
    std::string info_;

    //������
    void ImGuiSet::Initialize()
    {

        //�e�ϐ�������
        ARGUMENT_INITIALIZE(create3D_.first, false);
        ARGUMENT_INITIALIZE(create3D_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(createSigeboard_.first, false);
        ARGUMENT_INITIALIZE(createSigeboard_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(createCameraTransition_.first, false);
        ARGUMENT_INITIALIZE(createCameraTransition_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(createImage_.first, false);
        ARGUMENT_INITIALIZE(createImage_.second, (int)ZERO);
        ARGUMENT_INITIALIZE(objectCount_, (int)ZERO);
        ARGUMENT_INITIALIZE(screenMode_, static_cast<int>(Mode::GAME));
        ARGUMENT_INITIALIZE(gameMode_, static_cast<int>(Mode::STOP));
        ARGUMENT_INITIALIZE(isGameScreenFull_, false);
        ARGUMENT_INITIALIZE(info_,"");

        //�G�t�F�N�g�G�f�B�^�̎��ɕ\�����郂�f��
        pBaseFbx->Load("EffectEditModel/BaseModel.fbx");
        pStickFbx->Load("EffectEditModel/StickModel.fbx");

        //�e�V�[���̃X�e�[�W��񂪓����Ă�t�@�C���̃p�X�ݒ�
        stageInfoFilePath_[SCENE_ID_TITLE] = "Stage/Title/StageInformation/TitleScene.txt";
    }

    //�Q�[����ʂ��t���T�C�Y�ł͂Ȃ����̕`��
    void ImGuiSet::GameScreenNotFullDraw()
    {
        {
            //Imgui�X�^�[�g
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
        }

        //�X�e�[�W�쐬�pUI
        StageCreater();

        //�X�e�[�W�I�u�W�F�̃g�����X�t�H�[�����ׂĕ\������ImGui��\��
        StageObjImGuiDisplay();

        //�f�o�b�O�p�̃��O�\��
        DebugLogManager();

        //�V�[���`�F���W�p�̃{�^���\��
        SceneChangeButton();

        //�Q�[����ʐݒ�̕\��
        GameScreenNotFullPreference();

        //��ʂ̏�Ԑݒ�̕\��
        ScreenStatusPreference();
        
        //�v���Z�X���������\��
        ProcessMemory();

        //�t�@�C���ݒ�
        File();

        //�G�t�F�N�g�G�f�B�^���[�h�Ȃ�
        if (screenMode_ == static_cast<int>(Mode::EFFECT_EDIT))
            EffectEditGui();

        {
            ImGui::Render();
            //�`��
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }
    }

    //�Q�[����ʂ��t���T�C�Y�̎��̕`��
    void GameScreenFullDraw()
    {
        {
            //Imgui�X�^�[�g
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
        }

        //�Q�[����ʐݒ�̕\��
        GameScreenFullPreference();

        {
            ImGui::Render();
            //�`��
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }
    }

    ////////////////////////////////////�X�e�[�W�쐬�pImGui///////////////////////////////////////

    //�X�e�[�W�쐬����ImGui��UI���o���Ă����
    void ImGuiSet::StageCreater()
    {
        //window���
        ImGui::Begin("StageCreater", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //3D�����{�^��
        if (ImGui::Button("Create3D", ImVec2(300, 50)))
        {
            create3D_.first = true;
            create3D_.second++;
        }

        //�Ŕ����{�^��
        if (ImGui::Button("CreateSigeboard", ImVec2(300, 50)))
        {
            createSigeboard_.first = true;
            createSigeboard_.second++;
        }

        //�J�����{�^��
        if (ImGui::Button("CreateCameraTransition", ImVec2(300, 50)))
        {
            createCameraTransition_.first = true;
            createCameraTransition_.second++;
        }

        //�摜�{�^��
        if (ImGui::Button("CreateImage", ImVec2(300, 50)))
        {
            createImage_.first = true;
            createImage_.second++;
        }

        //flag��true�Ȃ�֐����Ăяo��
        if (create3D_.first)
        {
            Create3D();
        }

        //flag��true�Ȃ�֐����Ăяo��
        if (createSigeboard_.first)
        {
            CreateSigeboard();
        }

        //flag��true�Ȃ�֐����Ăяo��
        if (createCameraTransition_.first)
        {
            CreateCameraTransition();
        }

        //flag��true�Ȃ�֐����Ăяo��
        if (createImage_.first)
        {
            CreateImage();
        }

        ImGui::End();
    }

    //3D�I�u�W�F�N�g�쐬
    void ImGuiSet::Create3D()
    {

        //Create3D�����������E�B���h�E�����@
        for (int i = 0; i < create3D_.second; i++)
        {
            if (objectStatus_[i] == 1 || objectStatus_[i] == 0)
            {
                //i��FBX�̌��ɂ���
                char name[16];
                sprintf_s(name, "FBX %d", i);

                //window���
                ImGui::Begin(name);

                //�t�@�C���l�[�����͗�
                static char text1[MAX_OBJECT_SIZE][50] = {};

                //���͂��ꂽ������text1�Ɋi�[
                ImGui::InputText("FBX filename", text1[i], sizeof(text1[i]));

                //���[�h�{�^��
                if (ImGui::Button("Load"))
                {
                    //�����܂��������[�h���ĂȂ�������
                    if (objectStatus_[i] == 0)
                    {

                        //���[�h�����I�u�W�F�N�g�ɕK�v�ȃg�����X�t�H�[����p��
                        Transform t;

                        if (GameManager::GetpPlayer() != nullptr)
                        {
                            objectPos_[i] = GameManager::GetpPlayer()->GetPosition();
                            objectRotate_[i] = GameManager::GetpPlayer()->GetRotate();
                            objectScale_[i] = GameManager::GetpPlayer()->GetScale();
                        }
                        else
                        {
                            objectPos_[i] = XMFLOAT3(0, 0, 0);
                            objectRotate_[i] = XMFLOAT3(0, 0, 0);
                            objectScale_[i] = XMFLOAT3(1, 1, 1);
                        }

                        //�v�b�V�����邽�߂�pair�^�����
                        //first->���[�h�������f���ԍ�
                        //second->���[�h�������f����transform
                        std::pair<int, Transform> a(Model::Load(text1[i]), t);
                        assert(a.first > -1);

                        //vector�Ɋi�[����
                        obj_.push_back(a);

                        pNewObject_[i] = new Mob(GameManager::GetpSceneManager(), text1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(pNewObject_[i]);
                        }
                        pNewObject_[i]->Initialize();

                        //status�v���X
                        objectStatus_[i]++;

                    }
                }

                //��񃍁[�h���Ă�����
                if (objectStatus_[i] == 1)
                {

                    //Position�̖�
                    if (ImGui::TreeNode("position")) {

                        //Position�Z�b�g
                        ImGui::SliderFloat("x", &objectPos_[i].x, -200.0f, 200.0f);
                        ImGui::SliderFloat("y", &objectPos_[i].y, -200.0f, 200.0f);
                        ImGui::SliderFloat("z", &objectPos_[i].z, -200.0f, 200.0f);

                        if (ImGui::TreeNode("InputPosition")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &objectPos_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &objectPos_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &objectPos_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //Scale�̖�
                    if (ImGui::TreeNode("scale")) {

                        //Scale�Z�b�g
                        ImGui::SliderFloat("x", &objectScale_[i].x, -20.0f, 20.0f);
                        ImGui::SliderFloat("y", &objectScale_[i].y, -20.0f, 20.0f);
                        ImGui::SliderFloat("z", &objectScale_[i].z, -20.0f, 20.0f);

                        if (ImGui::TreeNode("InputScale")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &objectScale_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &objectScale_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &objectScale_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //rotate�̖�
                    if (ImGui::TreeNode("rotate")) {

                        //Rotate�Z�b�g
                        ImGui::SliderFloat("x", &objectRotate_[i].x, 0.0f, 360.0f);
                        ImGui::SliderFloat("y", &objectRotate_[i].y, 0.0f, 360.0f);
                        ImGui::SliderFloat("z", &objectRotate_[i].z, 0.0f, 360.0f);

                        if (ImGui::TreeNode("rotate")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &objectRotate_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &objectRotate_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &objectRotate_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    if (ImGui::TreeNode("StageSave")) {

                        //�t�@�C���l�[�����͗�
                        static char text2[MAX_OBJECT_SIZE][50] = {};

                        //���͂��ꂽ������text1�Ɋi�[
                        ImGui::InputText("ObjName", text2[i], sizeof(text2[i]));

                        if (ImGui::Button("Save"))
                        {

                            const char* fileName = stageInfoFilePath_[GameManager::GetpSceneManager()->GetSceneId()];
                            std::ofstream ofs;
                            ofs.open(fileName, std::ios::app);

                            ofs << std::endl;

                            ofs << text1[i] << "," << text2[i] << "," << objectPos_[i].x << "," << objectPos_[i].y << "," << objectPos_[i].z << ","
                                << objectRotate_[i].x << "," << objectRotate_[i].y << "," << objectRotate_[i].z << ","
                                << objectScale_[i].x << "," << objectScale_[i].y << "," << objectScale_[i].z;

                            ofs.close();
                        }
                        ImGui::TreePop();
                    }

                    //�E�B���h�E�폜
                    if (ImGui::Button("close"))
                    {
                        objectStatus_[i]++;
                    }
                }

                ImGui::End();
            }

            //�`�悳���
            if (objectStatus_[i] >= 1)
            {
                pNewObject_[i]->SetPosition(objectPos_[i]);
                pNewObject_[i]->SetAngle(objectRotate_[i].y);
                pNewObject_[i]->SetScale(objectScale_[i]);
            }
        }
    }

    //�Ŕ쐬
    void ImGuiSet::CreateSigeboard()
    {
        ////Player�̃|�W�V������ۑ����Ă���
        //XMFLOAT3 basicPos = GameManager::GetpPlayer()->GetPosition();
        //XMFLOAT3 basicRotate = GameManager::GetpPlayer()->GetRotate();
        //XMFLOAT3 basicScale = GameManager::GetpPlayer()->GetScale();

        ////Create3D�����������E�B���h�E�����@
        //for (int i = 0; i < createSigeboard_.second; i++)
        //{
        //    if (sigeboardStatus_[i] == 1 || sigeboardStatus_[i] == 0)
        //    {
        //        //i��FBX�̌��ɂ���
        //        char name[16];
        //        sprintf_s(name, "FBX %d", i);

        //        //window���
        //        ImGui::Begin(name);

        //        //�t�@�C���l�[�����͗�
        //        static char Stext1[MAX_OBJECT_SIZE][50] = {};

        //        //���͂��ꂽ������text1�Ɋi�[
        //        ImGui::InputText("FBX filename", Stext1[i], sizeof(Stext1[i]));

        //        //���[�h�{�^��
        //        if (ImGui::Button("Load"))
        //        {
        //            //�����܂��������[�h���ĂȂ�������
        //            if (sigeboardStatus_[i] == 0)
        //            {

        //                //���[�h�����I�u�W�F�N�g�ɕK�v�ȃg�����X�t�H�[����p��
        //                Transform t;

        //                sigeboardPos_[i] = basicPos;
        //                sigeboardRotate_[i] = basicRotate;
        //                sigeboardScale_[i] = basicScale;

        //                pNewSigeboard_[i] = new Signboard(GameManager::GetpSceneManager(), Stext1[i], "");
        //                if (GameManager::GetpSceneManager()->GetParent() != nullptr)
        //                {
        //                    GameManager::GetpSceneManager()->PushBackChild(pNewSigeboard_[i]);
        //                }
        //                pNewSigeboard_[i]->Initialize();

        //                //status�v���X
        //                sigeboardStatus_[i]++;

        //            }
        //        }

        //        //��񃍁[�h���Ă�����
        //        if (sigeboardStatus_[i] == 1)
        //        {

        //            //Position�̖�
        //            if (ImGui::TreeNode("position")) {

        //                //Position�Z�b�g
        //                ImGui::SliderFloat("x", &sigeboardPos_[i].x, -200.0f, 200.0f);
        //                ImGui::SliderFloat("y", &sigeboardPos_[i].y, -200.0f, 200.0f);
        //                ImGui::SliderFloat("z", &sigeboardPos_[i].z, -200.0f, 200.0f);

        //                if (ImGui::TreeNode("InputPosition")) {

        //                    ImGui::Text("x");
        //                    ImGui::InputFloat("x", &sigeboardPos_[i].x, -20.0f, 20.0f);
        //                    ImGui::Text("y");
        //                    ImGui::InputFloat("y", &sigeboardPos_[i].y, -20.0f, 20.0f);
        //                    ImGui::Text("z");
        //                    ImGui::InputFloat("z", &sigeboardPos_[i].z, -20.0f, 20.0f);

        //                    ImGui::TreePop();
        //                }

        //                ImGui::TreePop();
        //            }

        //            //Scale�̖�
        //            if (ImGui::TreeNode("scale")) {

        //                //Scale�Z�b�g
        //                ImGui::SliderFloat("x", &sigeboardScale_[i].x, -20.0f, 20.0f);
        //                ImGui::SliderFloat("y", &sigeboardScale_[i].y, -20.0f, 20.0f);
        //                ImGui::SliderFloat("z", &sigeboardScale_[i].z, -20.0f, 20.0f);

        //                if (ImGui::TreeNode("InputScale")) {

        //                    ImGui::Text("x");
        //                    ImGui::InputFloat("x", &sigeboardScale_[i].x, -20.0f, 20.0f);
        //                    ImGui::Text("y");
        //                    ImGui::InputFloat("y", &sigeboardScale_[i].y, -20.0f, 20.0f);
        //                    ImGui::Text("z");
        //                    ImGui::InputFloat("z", &sigeboardScale_[i].z, -20.0f, 20.0f);

        //                    ImGui::TreePop();
        //                }

        //                ImGui::TreePop();
        //            }

        //            //rotate�̖�
        //            if (ImGui::TreeNode("rotate")) {

        //                //Rotate�Z�b�g
        //                ImGui::SliderFloat("x", &sigeboardRotate_[i].x, 0.0f, 360.0f);
        //                ImGui::SliderFloat("y", &sigeboardRotate_[i].y, 0.0f, 360.0f);
        //                ImGui::SliderFloat("z", &sigeboardRotate_[i].z, 0.0f, 360.0f);

        //                if (ImGui::TreeNode("rotate")) {

        //                    ImGui::Text("x");
        //                    ImGui::InputFloat("x", &sigeboardRotate_[i].x, -20.0f, 20.0f);
        //                    ImGui::Text("y");
        //                    ImGui::InputFloat("y", &sigeboardRotate_[i].y, -20.0f, 20.0f);
        //                    ImGui::Text("z");
        //                    ImGui::InputFloat("z", &sigeboardRotate_[i].z, -20.0f, 20.0f);

        //                    ImGui::TreePop();
        //                }

        //                ImGui::TreePop();
        //            }

        //            if (ImGui::TreeNode("StageSave")) {

        //                //�t�@�C���l�[�����͗�
        //                static char Stext2[MAX_OBJECT_SIZE][50] = {};

        //                //���͂��ꂽ������text1�Ɋi�[
        //                ImGui::InputText("ObjName", Stext2[i], sizeof(Stext2[i]));

        //                if (ImGui::Button("Save"))
        //                {
        //                    basicPos = { sigeboardPos_[i] };
        //                    basicRotate = { sigeboardRotate_[i] };
        //                    basicScale = { sigeboardScale_[i] };

        //                    const char* fileName = stageInfoFilePath_[GameManager::GetpSceneManager()->GetSceneId()];
        //                    std::ofstream ofs;
        //                    ofs.open(fileName, std::ios::app);

        //                    ofs << std::endl;

        //                    ofs << Stext1[i] << "," << Stext2[i] << "," << sigeboardPos_[i].x << "," << sigeboardPos_[i].y << "," << sigeboardPos_[i].z << ","
        //                        << sigeboardRotate_[i].x << "," << sigeboardRotate_[i].y << "," << sigeboardRotate_[i].z << ","
        //                        << sigeboardScale_[i].x << "," << sigeboardScale_[i].y << "," << sigeboardScale_[i].z;

        //                    ofs.close();
        //                }
        //                ImGui::TreePop();
        //            }

        //            //�E�B���h�E�폜
        //            if (ImGui::Button("close"))
        //            {
        //                sigeboardStatus_[i]++;
        //            }
        //        }

        //        ImGui::End();
        //    }

        //    //�`�悳���
        //    if (sigeboardStatus_[i] >= 1)
        //    {
        //        pNewSigeboard_[i]->SetPosition(sigeboardPos_[i]);
        //        pNewSigeboard_[i]->SetRotate(sigeboardRotate_[i]);
        //        pNewSigeboard_[i]->SetScale(sigeboardScale_[i]);
        //    }
        //}
    }

    //�J�����̑J�ڍ쐬(�R���C�_�[�ɓ���������J�����̃|�W�V�����ς���@�\)
    void ImGuiSet::CreateCameraTransition()
    {
        //Player�̃|�W�V������ۑ����Ă���
        XMFLOAT3 basicPos = GameManager::GetpPlayer()->GetPosition();
        XMFLOAT3 basicRotate = GameManager::GetpPlayer()->GetRotate();
        XMFLOAT3 basicScale = GameManager::GetpPlayer()->GetScale();

        //Create3D�����������E�B���h�E�����@
        for (int i = 0; i < createCameraTransition_.second; i++)
        {
            if (cameraTransitionStatus_[i] == 1 || cameraTransitionStatus_[i] == 0)
            {
                //i��FBX�̌��ɂ���
                char name[16];
                sprintf_s(name, "FBX %d", i);

                //window���
                ImGui::Begin(name);

                //�t�@�C���l�[�����͗�
                static char text1[MAX_OBJECT_SIZE][50] = {};

                //���͂��ꂽ������text1�Ɋi�[
                ImGui::InputText("FBX filename", text1[i], sizeof(text1[i]));

                //���[�h�{�^��
                if (ImGui::Button("Load"))
                {
                    //�����܂��������[�h���ĂȂ�������
                    if (cameraTransitionStatus_[i] == 0)
                    {

                        //���[�h�����I�u�W�F�N�g�ɕK�v�ȃg�����X�t�H�[����p��
                        Transform t;

                        cameraTransitionPos_[i] = basicPos;
                        cameraTar_[i] = basicRotate;
                        colliderSize_[i] = basicScale;

                        //�v�b�V�����邽�߂�pair�^�����
                        //first->���[�h�������f���ԍ�
                        //second->���[�h�������f����transform
                        std::pair<int, Transform> a(Model::Load(text1[i]), t);
                        assert(a.first > 0);

                        //vector�Ɋi�[����
                        obj_.push_back(a);

                        pNewCameraTransition_[i] = new Mob(GameManager::GetpSceneManager(), text1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(pNewCameraTransition_[i]);
                        }
                        pNewCameraTransition_[i]->Initialize();

                        //status�v���X
                        cameraTransitionStatus_[i]++;

                    }
                }

                //��񃍁[�h���Ă�����
                if (cameraTransitionStatus_[i] == 1)
                {

                    //Position�̖�
                    if (ImGui::TreeNode("position")) {

                        //Position�Z�b�g
                        ImGui::SliderFloat("x", &cameraTransitionPos_[i].x, -200.0f, 200.0f);
                        ImGui::SliderFloat("y", &cameraTransitionPos_[i].y, -200.0f, 200.0f);
                        ImGui::SliderFloat("z", &cameraTransitionPos_[i].z, -200.0f, 200.0f);

                        if (ImGui::TreeNode("InputPosition")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &cameraTransitionPos_[i].x, -200.0f, 200.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &cameraTransitionPos_[i].y, -200.0f, 200.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &cameraTransitionPos_[i].z, -200.0f, 200.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //Position�̖�
                    if (ImGui::TreeNode("CameraPosition")) {

                        //Position�Z�b�g
                        ImGui::SliderFloat("x", &cameraPos_[i].x, -200.0f, 200.0f);
                        ImGui::SliderFloat("y", &cameraPos_[i].y, -200.0f, 200.0f);
                        ImGui::SliderFloat("z", &cameraPos_[i].z, -200.0f, 200.0f);

                        if (ImGui::TreeNode("CameraInputPosition")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &cameraPos_[i].x, -200.0f, 200.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &cameraPos_[i].y, -200.0f, 200.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &cameraPos_[i].z, -200.0f, 200.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //Scale�̖�
                    if (ImGui::TreeNode("scale")) {

                        //Scale�Z�b�g
                        ImGui::SliderFloat("x", &colliderSize_[i].x, -20.0f, 20.0f);
                        ImGui::SliderFloat("y", &colliderSize_[i].y, -20.0f, 20.0f);
                        ImGui::SliderFloat("z", &colliderSize_[i].z, -20.0f, 20.0f);

                        if (ImGui::TreeNode("InputScale")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &colliderSize_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &colliderSize_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &colliderSize_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //rotate�̖�
                    if (ImGui::TreeNode("rotate")) {

                        //Rotate�Z�b�g
                        ImGui::SliderFloat("x", &cameraTar_[i].x, 0.0f, 360.0f);
                        ImGui::SliderFloat("y", &cameraTar_[i].y, 0.0f, 360.0f);
                        ImGui::SliderFloat("z", &cameraTar_[i].z, 0.0f, 360.0f);

                        if (ImGui::TreeNode("rotate")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &cameraTar_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &cameraTar_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &cameraTar_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    if (ImGui::TreeNode("StageSave")) {

                        //�t�@�C���l�[�����͗�
                        static char text2[MAX_OBJECT_SIZE][50] = {};

                        //���͂��ꂽ������text1�Ɋi�[
                        ImGui::InputText("ObjName", text2[i], sizeof(text2[i]));

                        if (ImGui::Button("Save"))
                        {
                            basicPos = { cameraTransitionPos_[i] };
                            basicRotate = { cameraTar_[i] };
                            basicScale = { colliderSize_[i] };

                            const char* fileName = stageInfoFilePath_[GameManager::GetpSceneManager()->GetSceneId()];
                            std::ofstream ofs;
                            ofs.open(fileName, std::ios::app);

                            ofs << std::endl;

                            ofs << text1[i] << "," << text2[i] << "," << cameraTransitionPos_[i].x << "," << cameraTransitionPos_[i].y << "," << cameraTransitionPos_[i].z << ","
                                << cameraTar_[i].x << "," << cameraTar_[i].y << "," << cameraTar_[i].z << ","
                                << colliderSize_[i].x * 2 << "," << colliderSize_[i].y * 2 << "," << colliderSize_[i].z * 2 << ","
                                << cameraPos_[i].x << "," << cameraPos_[i].y << "," << cameraPos_[i].z;

                            ofs.close();
                        }
                        ImGui::TreePop();
                    }

                    //�E�B���h�E�폜
                    if (ImGui::Button("close"))
                    {
                        cameraTransitionStatus_[i]++;
                    }
                }

                ImGui::End();
            }

            //�`�悳���
            if (cameraTransitionStatus_[i] >= 1)
            {
                pNewCameraTransition_[i]->SetPosition(cameraTransitionPos_[i]);
                pNewCameraTransition_[i]->SetRotate(cameraTar_[i]);
                pNewCameraTransition_[i]->SetScale(colliderSize_[i]);
            }
        }
    }

    //�摜�쐬
    void ImGuiSet::CreateImage()
    {

        //Create3D�����������E�B���h�E�����@
        for (int i = 0; i < createImage_.second; i++)
        {
            if (imageStatus_[i] == 1 || imageStatus_[i] == 0)
            {
                //i��FBX�̌��ɂ���
                char name[16];
                sprintf_s(name, "FBX %d", i);

                //window���
                ImGui::Begin(name);

                //�t�@�C���l�[�����͗�
                static char text1[MAX_OBJECT_SIZE][100] = {};

                //���͂��ꂽ������text1�Ɋi�[
                ImGui::InputText("FBX filename", text1[i], sizeof(text1[i]));

                //���[�h�{�^��
                if (ImGui::Button("Load"))
                {
                    //�����܂��������[�h���ĂȂ�������
                    if (imageStatus_[i] == 0)
                    {

                        //���[�h�����I�u�W�F�N�g�ɕK�v�ȃg�����X�t�H�[����p��
                        Transform t;

                        imagePos_[i] = XMFLOAT3(0, 0, 0);
                        imageRotate_[i] = XMFLOAT3(0, 0, 0);
                        imageScale_[i] = XMFLOAT3(1, 1, 1);

                        //�v�b�V�����邽�߂�pair�^�����
                        //first->���[�h�������f���ԍ�
                        //second->���[�h�������f����transform
                        std::pair<int, Transform> a(Image::Load(text1[i]), t);
                        assert(a.first > 0);

                        //vector�Ɋi�[����
                        obj_.push_back(a);

                        pNewImage_[i] = new ImageBase(GameManager::GetpSceneManager(), text1[i], "");
                        if (GameManager::GetpSceneManager()->GetParent() != nullptr)
                        {
                            GameManager::GetpSceneManager()->PushBackChild(pNewImage_[i]);
                        }
                        pNewImage_[i]->Initialize();

                        //status�v���X
                        imageStatus_[i]++;

                    }
                }

                //��񃍁[�h���Ă�����
                if (imageStatus_[i] == 1)
                {

                    //Position�̖�
                    if (ImGui::TreeNode("position")) {

                        //Position�Z�b�g
                        ImGui::SliderFloat("x", &imagePos_[i].x, -200.0f, 200.0f);
                        ImGui::SliderFloat("y", &imagePos_[i].y, -200.0f, 200.0f);
                        ImGui::SliderFloat("z", &imagePos_[i].z, -200.0f, 200.0f);

                        if (ImGui::TreeNode("InputPosition")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &imagePos_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &imagePos_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &imagePos_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //Scale�̖�
                    if (ImGui::TreeNode("scale")) {

                        //Scale�Z�b�g
                        ImGui::SliderFloat("x", &imageScale_[i].x, -20.0f, 20.0f);
                        ImGui::SliderFloat("y", &imageScale_[i].y, -20.0f, 20.0f);
                        ImGui::SliderFloat("z", &imageScale_[i].z, -20.0f, 20.0f);

                        if (ImGui::TreeNode("InputScale")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &imageScale_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &imageScale_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &imageScale_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    //rotate�̖�
                    if (ImGui::TreeNode("rotate")) {

                        //Rotate�Z�b�g
                        ImGui::SliderFloat("x", &imageRotate_[i].x, 0.0f, 360.0f);
                        ImGui::SliderFloat("y", &imageRotate_[i].y, 0.0f, 360.0f);
                        ImGui::SliderFloat("z", &imageRotate_[i].z, 0.0f, 360.0f);

                        if (ImGui::TreeNode("rotate")) {

                            ImGui::Text("x");
                            ImGui::InputFloat("x", &imageRotate_[i].x, -20.0f, 20.0f);
                            ImGui::Text("y");
                            ImGui::InputFloat("y", &imageRotate_[i].y, -20.0f, 20.0f);
                            ImGui::Text("z");
                            ImGui::InputFloat("z", &imageRotate_[i].z, -20.0f, 20.0f);

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }

                    if (ImGui::TreeNode("StageSave")) {

                        //�t�@�C���l�[�����͗�
                        static char text2[MAX_OBJECT_SIZE][50] = {};

                        //���͂��ꂽ������text1�Ɋi�[
                        ImGui::InputText("ObjName", text2[i], sizeof(text2[i]));

                        if (ImGui::Button("Save"))
                        {

                            const char* fileName = stageInfoFilePath_[GameManager::GetpSceneManager()->GetSceneId()];
                            std::ofstream ofs;
                            ofs.open(fileName, std::ios::app);

                            ofs << std::endl;

                            ofs << text1[i] << "," << text2[i] << "," << imagePos_[i].x << "," << imagePos_[i].y << "," << imagePos_[i].z << ","
                                << imageRotate_[i].x << "," << imageRotate_[i].y << "," << imageRotate_[i].z << ","
                                << imageScale_[i].x << "," << imageScale_[i].y << "," << imageScale_[i].z;

                            ofs.close();
                        }
                        ImGui::TreePop();
                    }

                    //�E�B���h�E�폜
                    if (ImGui::Button("close"))
                    {
                        imageStatus_[i]++;
                    }
                }

                ImGui::End();
            }

            //�`�悳���
            if (imageStatus_[i] >= 1)
            {
                pNewImage_[i]->SetPosition(imagePos_[i]);
                pNewImage_[i]->SetScale(imageScale_[i]);
            }
        }

    }

    //////////////////////////////�X�e�[�W�̃I�u�W�F�N�g�̃g�����X�t�H�[���\��////////////////////////////

    //�X�e�[�W�I�u�W�F�̃g�����X�t�H�[�����ׂĕ\������ImGui��\��
    void ImGuiSet::StageObjImGuiDisplay()
    {
        //null�Ȃ炱�̐揈�����Ȃ�
        if (GameManager::GetpSceneManager() == nullptr) return;

        //window���
        ImGui::Begin("StageObjTransformDisplay", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //�X�e�[�W�I�u�W�F�̃g�����X�t�H�[�����ׂĕ\��
        StageObjTransformDisplay(GameManager::GetpSceneManager());

        //�I�u�W�F�N�g�̐�0�ɏ�����
        ARGUMENT_INITIALIZE(objectCount_, (int)ZERO);

        //�I���
        ImGui::End();
    }

    //�X�e�[�W�I�u�W�F�̃g�����X�t�H�[�����ׂĕ\��
    void ImGuiSet::StageObjTransformDisplay(GameObject* pObj)
    {
        //����null�Ȃ甲����
        if (pObj == nullptr) return;

        //�I�u�W�F�N�g�̐����₷
        objectCount_++;

        //�I�u�W�F�N�g�̖��O�����Ƃ��Ƃ̖��O�v���XobjectCount_�������O�ɂ���
        std::string objName = pObj->GetObjectName() + std::to_string(objectCount_);

        //�I�u�W�F�N�g�̖��O�Ŗ��O�\������
        if (ImGui::TreeNode(objName.c_str()))
        {
            //�ʒu
            float pos[3] = { pObj->GetPosition().x,pObj->GetPosition().y ,pObj->GetPosition().z };
            ImGui::DragFloat3("position", pos);
            pObj->SetPosition({ pos[0], pos[1], pos[2] });

            //��]
            float rotate[3] = { pObj->GetRotate().x,pObj->GetRotate().y ,pObj->GetRotate().z };
            ImGui::DragFloat3("rotation", rotate);
            pObj->SetRotate({ rotate[0],rotate[1],rotate[2] });

            //�g�嗦
            float scale[3] = { pObj->GetScale().x,pObj->GetScale().y ,pObj->GetScale().z };
            ImGui::DragFloat3("scale", scale);
            pObj->SetScale({ scale[0],scale[1],scale[2] });

            //�폜�{�^��
            if (ImGui::Button("Kill")) { pObj->KillMe(); }

            ImGui::TreePop();
        }

        for (auto itr = pObj->GetChildList()->begin(); itr != pObj->GetChildList()->end(); itr++)
        {
            StageObjTransformDisplay(*itr);
        }
    }

    //////////////////////////////////////���O�\��///////////////////////////////////////

    //�f�o�b�O���O���Ǘ�����(ImGui�͂����ŕ\������)
    void ImGuiSet::DebugLogManager()
    {
        //window���
        ImGui::Begin("DebugLog", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //���O�\��
        for (auto i = variable_.rbegin(); i != variable_.rend(); i++)
        {
            ImGui::Text((*i).first.c_str());
            ImGui::SameLine();
            ImGui::Text((*i).second.c_str());
        }

        //�T�C�Y��1000�ȏ㌾������폜
        if (variable_.size() >= MAX_DEBUG_LOG_NUM)
            variable_.clear();

        //�I���
        ImGui::End();
    }

    //�C�ӂ̒l��\�����Ă����
    void ImGuiSet::DebugLog(std::string text, int num)
    {
        std::pair<std::string, std::string> a;

        ARGUMENT_INITIALIZE(a.first, text);
        ARGUMENT_INITIALIZE(a.second, std::to_string(num));

        variable_.push_back(a);
    }
    void ImGuiSet::DebugLog(std::string text, float num)
    {
        std::pair<std::string, std::string> a;

        ARGUMENT_INITIALIZE(a.first, text);
        ARGUMENT_INITIALIZE(a.second, std::to_string(num));

        variable_.push_back(a);
    }
    void ImGuiSet::DebugLog(std::string text, bool num)
    {
        std::pair<std::string, std::string> a;

        ARGUMENT_INITIALIZE(a.first, text);

        //true,false�ŕς���
        if (num)
        {
            ARGUMENT_INITIALIZE(a.second, "true");
        }
        else
            ARGUMENT_INITIALIZE(a.second, "false");

        
        variable_.push_back(a);
    }
    void ImGuiSet::DebugLog(std::string text, XMFLOAT3 num)
    {
        std::pair<std::string, std::string> a;

        ARGUMENT_INITIALIZE(a.first, text);
        ARGUMENT_INITIALIZE(a.second, "x " + std::to_string(num.x) + " y " + std::to_string(num.y) + " z " + std::to_string(num.z));

        variable_.push_back(a);
    }
    void ImGuiSet::DebugLog(std::string text, std::string str)
    {
        std::pair<std::string, std::string> a;

        ARGUMENT_INITIALIZE(a.first, text);
        ARGUMENT_INITIALIZE(a.second, str);

        variable_.push_back(a);
    }

    ///////////////////////////////�V�[���ύX�\��///////////////////////////////////////

    /// <summary>
    /// �V�[���ύX�p�{�^���\��
    /// </summary>
    void ImGuiSet::SceneChangeButton()
    {
        //window���
        ImGui::Begin("SceneChangeButton", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //�{�^���쐬
        if (ImGui::Button("TITLE", ImVec2(300, 50)))                 { GameManager::GetpSceneManager()->SetLoadDrawFlag(false); GameManager::GetpSceneManager()->SameSceneInitializ(SCENE_ID_TITLE); }

        //�I���
        ImGui::End();
    }

    ///////////////////////////////�Q�[����ʐݒ�///////////////////////////////////////

    /// <summary>
    /// �Q�[����ʐݒ�
    /// </summary>
    void ImGuiSet::GameScreenNotFullPreference()
    {
        //window���
        ImGui::Begin("GameScreenNotFullPreference", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //���W�I�{�^���̃T�C�Y��2�{�ɕύX
        ImGuiStyle& style = ImGui::GetStyle();
        ARGUMENT_INITIALIZE(style.FramePadding, ImVec2(8, 8));

        //���[�h��Ԃ��L�^���Ă���
        int beforeMode = gameMode_;

        //���W�I�{�^���쐬
        ImGui::RadioButton("Start", &gameMode_, static_cast<int>(Mode::START));
        ImGui::SameLine();
        ImGui::RadioButton("Stop", &gameMode_, static_cast<int>(Mode::STOP));
        ImGui::SameLine();

        //����Stop��Ԃ���Start��Ԃɕς�����̂Ȃ�
        if (beforeMode == static_cast<int>(Mode::STOP) && gameMode_ == static_cast<int>(Mode::START))
        {
            Direct3D::SetTimeScale(false);
        }
        //����Start��Ԃ���Stop��Ԃɕς�����̂Ȃ�
        else if (beforeMode == static_cast<int>(Mode::START) && gameMode_ == static_cast<int>(Mode::STOP))
        {
            Direct3D::SetTimeScale(true);
        }

        //�O�̏�Ԃ�ۑ����Ă���
        bool beforeflag = isGameScreenFull_;

        //�`�F�b�N�{�b�N�X�\��
        ImGui::Checkbox("GameScreenFull", &isGameScreenFull_);

        //�t���T�C�Y�ɕύX���Ă�����
        if (!beforeflag && isGameScreenFull_)
            Direct3D::SetGameFull(true);

        //�T�C�Y�����ɖ߂�
        ARGUMENT_INITIALIZE(style.FramePadding, ImVec2(4, 4));

        //�I���
        ImGui::End();
    }

    /// <summary>
    /// �Q�[����ʂ��t���T�C�Y�̎��̐ݒ�
    /// </summary>
    void ImGuiSet::GameScreenFullPreference()
    {
        //window���
        ImGui::Begin("GameScreenFullPreference", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //���W�I�{�^���̃T�C�Y��2�{�ɕύX
        ImGuiStyle& style = ImGui::GetStyle();
        ARGUMENT_INITIALIZE(style.FramePadding, ImVec2(8, 8));

        //���[�h��Ԃ��L�^���Ă���
        int beforeMode = gameMode_;

        //���W�I�{�^���쐬
        ImGui::RadioButton("Start", &gameMode_, static_cast<int>(Mode::START));
        ImGui::SameLine();
        ImGui::RadioButton("Stop", &gameMode_, static_cast<int>(Mode::STOP));
        ImGui::SameLine();

        //����Stop��Ԃ���Start��Ԃɕς�����̂Ȃ�
        if (beforeMode == static_cast<int>(Mode::STOP) && gameMode_ == static_cast<int>(Mode::START))
        {
            Direct3D::SetTimeScale(false);
        }
        //����Start��Ԃ���Stop��Ԃɕς�����̂Ȃ�
        else if (beforeMode == static_cast<int>(Mode::START) && gameMode_ == static_cast<int>(Mode::STOP))
        {
            Direct3D::SetTimeScale(true);
        }

        //�O�̏�Ԃ�ۑ����Ă���
        bool beforeflag = isGameScreenFull_;

        //�`�F�b�N�{�b�N�X�\��
        ImGui::Checkbox("GameScreenFull", &isGameScreenFull_);

        //�t���T�C�Y����ύX���Ă�����
        if(beforeflag && !isGameScreenFull_)
            Direct3D::SetGameFull(false);

        //�T�C�Y�����ɖ߂�
        ARGUMENT_INITIALIZE(style.FramePadding, ImVec2(4, 4));

        //�I���
        ImGui::End();
    }

    /// <summary>
    /// ��ʂ̏�Ԑݒ�
    /// </summary>
    void ImGuiSet::ScreenStatusPreference()
    {
        //window���
        ImGui::Begin("ScreenStatus", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //���W�I�{�^���̃T�C�Y��2�{�ɕύX
        ImGuiStyle& style = ImGui::GetStyle();
        ARGUMENT_INITIALIZE(style.FramePadding,ImVec2(8, 8));

        //���[�h��Ԃ��L�^���Ă���
        int beforeMode = screenMode_;

        //���W�I�{�^���쐬
        ImGui::RadioButton("Game", &screenMode_, static_cast<int>(Mode::GAME));
        ImGui::SameLine();
        ImGui::RadioButton("Scene", &screenMode_, static_cast<int>(Mode::SCENE));
        ImGui::SameLine();
        ImGui::RadioButton("EffectEdit", &screenMode_, static_cast<int>(Mode::EFFECT_EDIT));

        //�����Q�[����ʂɐ؂�ւ�����̂Ȃ�
        if (beforeMode != static_cast<int>(Mode::GAME) && screenMode_ == static_cast<int>(Mode::GAME))
        {
            ARGUMENT_INITIALIZE(gameMode_, static_cast<int>(Mode::START));
            Direct3D::SetTimeScale(false);
            Direct3D::SetScreenGameStatus(true);
            Direct3D::SetBackScreenColor(XMFLOAT4(0.3f, 0.3f, 0.3f, 1));

            //�����O��̃��[�h���G�t�F�N�g�G�f�B�^�Ȃ�
            if(beforeMode == static_cast<int>(Mode::EFFECT_EDIT))Camera::UndoFiledAngle();
        }
        //�����V�[����ʂɐ؂�ւ�����̂Ȃ�
        else if(beforeMode != static_cast<int>(Mode::SCENE) && screenMode_ == static_cast<int>(Mode::SCENE))
        {
            ARGUMENT_INITIALIZE(gameMode_, static_cast<int>(Mode::STOP));
            Direct3D::SetTimeScale(true);
            Direct3D::SetScreenGameStatus(false);
            Camera::FrameCameraInitialize();
            Direct3D::SetBackScreenColor(XMFLOAT4(0.3f, 0.3f, 0.3f, 1));

            //�����O��̃��[�h���G�t�F�N�g�G�f�B�^�Ȃ�
            if (beforeMode == static_cast<int>(Mode::EFFECT_EDIT))Camera::UndoFiledAngle();
        }
        //�����G�t�F�N�g�G�f�B�^��ʂɐ؂�ւ�����̂Ȃ�
        else if (beforeMode != static_cast<int>(Mode::EFFECT_EDIT) && screenMode_ == static_cast<int>(Mode::EFFECT_EDIT))
        {
            ARGUMENT_INITIALIZE(gameMode_, static_cast<int>(Mode::STOP));
            Direct3D::SetTimeScale(true);
            Direct3D::SetScreenGameStatus(false);
            Camera::SetEffectEditCamera();
        }

        //�T�C�Y�����ɖ߂�
        ARGUMENT_INITIALIZE(style.FramePadding,ImVec2(4, 4));

        //�I���
        ImGui::End();
    }

    /// <summary>
    /// �G�t�F�N�g�G�f�B�^��GUI
    /// </summary>
    void ImGuiSet::EffectEditGui()
    {
        //���f���\��
        Transform t;
        pBaseFbx->Draw(t, ZERO, 1, XMFLOAT4(ZERO, ZERO, ZERO, ZERO), XMFLOAT4(ZERO, ZERO, ZERO, ZERO), ZERO, ZERO, XMFLOAT4(ZERO, ZERO, ZERO, ZERO), false, Direct3D::SHADER_UNLIT);
        pStickFbx->Draw(t, ZERO, 1, XMFLOAT4(ZERO, ZERO, ZERO, ZERO), XMFLOAT4(ZERO, ZERO, ZERO, ZERO), 1.0f, ZERO, XMFLOAT4(ZERO, ZERO, ZERO, ZERO), false, Direct3D::SHADER_3D);

        //window���
        ImGui::Begin("Effect", NULL, ImGuiWindowFlags_NoMove);

        //�G�t�F�N�g�̊e���ݒ�p
        if (ImGui::TreeNode("textureFileName")) {

            ImGui::InputText("textureFileName", const_cast<char*>(textureFileName_.c_str()), sizeof(textureFileName_.c_str()));
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("position")) {

            //Position�Z�b�g
            ImGui::SliderFloat("x", &position_.x, -200.0f, 200.0f);
            ImGui::SliderFloat("y", &position_.y, -200.0f, 200.0f);
            ImGui::SliderFloat("z", &position_.z, -200.0f, 200.0f);

            if (ImGui::TreeNode("InputPosition")) {

                ImGui::InputFloat("x", &position_.x, -200.0f, 200.0f);
                ImGui::InputFloat("y", &position_.y, -200.0f, 200.0f);
                ImGui::InputFloat("z", &position_.z, -200.0f, 200.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("positionRnd")) {

            //Position�Z�b�g
            ImGui::SliderFloat("x", &positionRnd_.x, -200.0f, 200.0f);
            ImGui::SliderFloat("y", &positionRnd_.y, -200.0f, 200.0f);
            ImGui::SliderFloat("z", &positionRnd_.z, -200.0f, 200.0f);

            if (ImGui::TreeNode("InputPositionRnd")) {

                ImGui::InputFloat("x", &positionRnd_.x, -200.0f, 200.0f);
                ImGui::InputFloat("y", &positionRnd_.y, -200.0f, 200.0f);
                ImGui::InputFloat("z", &positionRnd_.z, -200.0f, 200.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("direction")) {

            ImGui::SliderFloat("x", &direction_.x, -200.0f, 200.0f);
            ImGui::SliderFloat("y", &direction_.y, -200.0f, 200.0f);
            ImGui::SliderFloat("z", &direction_.z, -200.0f, 200.0f);

            if (ImGui::TreeNode("InputDirection")) {

                ImGui::InputFloat("x", &direction_.x, -200.0f, 200.0f);
                ImGui::InputFloat("y", &direction_.y, -200.0f, 200.0f);
                ImGui::InputFloat("z", &direction_.z, -200.0f, 200.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("directionRnd")) {

            ImGui::SliderFloat("x", &directionRnd_.x, 0.0f, 360.0f);
            ImGui::SliderFloat("y", &directionRnd_.y, 0.0f, 360.0f);
            ImGui::SliderFloat("z", &directionRnd_.z, 0.0f, 360.0f);

            if (ImGui::TreeNode("InputDirectionRnd")) {

                ImGui::InputFloat("x", &directionRnd_.x, 0.0f, 360.0f);
                ImGui::InputFloat("y", &directionRnd_.y, 0.0f, 360.0f);
                ImGui::InputFloat("z", &directionRnd_.z, 0.0f, 360.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("speed")) {

            ImGui::SliderFloat("speed", &speed_, 0.0f, 50.0f);

            if (ImGui::TreeNode("InputSpeed")) {
                ImGui::InputFloat("speed", &speed_, 0.0f, 50.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("speedRnd")) {

            ImGui::SliderFloat("speedRnd", &speedRnd_, 0.0f, 50.0f);

            if (ImGui::TreeNode("InputSpeedRnd")) {
                ImGui::InputFloat("speedRnd", &speed_, 0.0f, 50.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("accel")) {

            ImGui::SliderFloat("accel", &accel_, 0.0f, 50.0f);

            if (ImGui::TreeNode("InputAccel")) {
                ImGui::InputFloat("accel", &accel_, 0.0f, 50.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("gravity")) {

            ImGui::SliderFloat("gravity", &gravity_, 0.0f, 50.0f);

            if (ImGui::TreeNode("InputGravity")) {
                ImGui::InputFloat("gravity", &gravity_, 0.0f, 50.0f);
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("color")) {

            float color[4] = { color_.x, color_.y, color_.z, color_.w };
            ImGui::ColorPicker3("Color", color, ImGuiColorEditFlags_PickerHueWheel);
            color_ = XMFLOAT4(color[0], color[1], color[2], color[3]);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("deltaColor")) {

            float deltaColor[4] = { deltaColor_.x, deltaColor_.y, deltaColor_.z, deltaColor_.w };
            ImGui::ColorPicker3("deltaColor", deltaColor, ImGuiColorEditFlags_PickerHueWheel);
            deltaColor_ = XMFLOAT4(deltaColor[0], deltaColor[1], deltaColor[2], deltaColor[3]);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("rotate")) {

            ImGui::SliderFloat("x", &rotate_.x, 0.0f, 360.0f);
            ImGui::SliderFloat("y", &rotate_.y, 0.0f, 360.0f);
            ImGui::SliderFloat("z", &rotate_.z, 0.0f, 360.0f);

            if (ImGui::TreeNode("InputRotate")) {

                ImGui::InputFloat("x", &rotate_.x, 0.0f, 360.0f);
                ImGui::InputFloat("y", &rotate_.y, 0.0f, 360.0f);
                ImGui::InputFloat("z", &rotate_.z, 0.0f, 360.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("rotateRnd")) {

            ImGui::SliderFloat("x", &rotateRnd_.x, 0.0f, 360.0f);
            ImGui::SliderFloat("y", &rotateRnd_.y, 0.0f, 360.0f);
            ImGui::SliderFloat("z", &rotateRnd_.z, 0.0f, 360.0f);

            if (ImGui::TreeNode("InputRotateRnd")) {

                ImGui::InputFloat("x", &rotateRnd_.x, 0.0f, 360.0f);
                ImGui::InputFloat("y", &rotateRnd_.y, 0.0f, 360.0f);
                ImGui::InputFloat("z", &rotateRnd_.z, 0.0f, 360.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("spin")) {

            ImGui::SliderFloat("x", &spin_.x, 0.0f, 360.0f);
            ImGui::SliderFloat("y", &spin_.y, 0.0f, 360.0f);
            ImGui::SliderFloat("z", &spin_.z, 0.0f, 360.0f);

            if (ImGui::TreeNode("InputSpin")) {

                ImGui::InputFloat("x", &spin_.x, 0.0f, 360.0f);
                ImGui::InputFloat("y", &spin_.y, 0.0f, 360.0f);
                ImGui::InputFloat("z", &spin_.z, 0.0f, 360.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("size")) {

            ImGui::SliderFloat("x", &size_.x, 0.0f, 100.0f);
            ImGui::SliderFloat("y", &size_.y, 0.0f, 100.0f);

            if (ImGui::TreeNode("InputSize")) {

                ImGui::InputFloat("x", &size_.x, 0.0f, 100.0f);
                ImGui::InputFloat("y", &size_.y, 0.0f, 100.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("sizeRnd")) {

            ImGui::SliderFloat("x", &sizeRnd_.x, 0.0f, 100.0f);
            ImGui::SliderFloat("y", &sizeRnd_.y, 0.0f, 100.0f);

            if (ImGui::TreeNode("InputSizeRnd")) {

                ImGui::InputFloat("x", &sizeRnd_.x, 0.0f, 100.0f);
                ImGui::InputFloat("y", &sizeRnd_.y, 0.0f, 100.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("scale")) {

            ImGui::SliderFloat("x", &scale_.x, 0.0f, 100.0f);
            ImGui::SliderFloat("y", &scale_.y, 0.0f, 100.0f);

            if (ImGui::TreeNode("InputScale")) {

                ImGui::InputFloat("x", &scale_.x, 0.0f, 100.0f);
                ImGui::InputFloat("y", &scale_.y, 0.0f, 100.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("lifeTime")) {

            ImGui::SliderFloat("lifeTime", &lifeTime_, 0.0f, 3000.0f);

            if (ImGui::TreeNode("InputLifeTime")) {
                ImGui::InputFloat("lifeTime", &lifeTime_, 0.0f, 3000.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("delay")) {

            ImGui::SliderInt("delay", &delay_, 0.0f, 600.0f);

            if (ImGui::TreeNode("InputDelay")) {
                ImGui::InputInt("delay", &delay_, 0.0f, 600.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("number")) {

            ImGui::SliderInt("number", &number_, 0.0f, 100.0f);

            if (ImGui::TreeNode("InputNumber")) {
                ImGui::InputInt("number", &number_, 0.0f, 100.0f);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("isBillBoard")) {

            ImGui::Checkbox("GameScreenFull", &isBillBoard_);
            ImGui::TreePop();
        }

        //�e�����
        ARGUMENT_INITIALIZE(data.textureFileName, textureFileName_);
        ARGUMENT_INITIALIZE(data.position, position_);
        ARGUMENT_INITIALIZE(data.positionRnd, positionRnd_);
        ARGUMENT_INITIALIZE(data.direction, direction_);
        ARGUMENT_INITIALIZE(data.directionRnd, directionRnd_);
        ARGUMENT_INITIALIZE(data.speed, speed_);
        ARGUMENT_INITIALIZE(data.speedRnd, speedRnd_);
        ARGUMENT_INITIALIZE(data.accel, accel_);
        ARGUMENT_INITIALIZE(data.gravity, gravity_);
        ARGUMENT_INITIALIZE(data.color, color_);
        ARGUMENT_INITIALIZE(data.deltaColor, deltaColor_);
        ARGUMENT_INITIALIZE(data.rotate, rotate_);
        ARGUMENT_INITIALIZE(data.rotateRnd, rotateRnd_);
        ARGUMENT_INITIALIZE(data.spin, spin_);
        ARGUMENT_INITIALIZE(data.size, size_);
        ARGUMENT_INITIALIZE(data.sizeRnd, sizeRnd_);
        ARGUMENT_INITIALIZE(data.scale, scale_);
        ARGUMENT_INITIALIZE(data.lifeTime, lifeTime_);
        ARGUMENT_INITIALIZE(data.delay, delay_);
        ARGUMENT_INITIALIZE(data.number, number_);
        ARGUMENT_INITIALIZE(data.isBillBoard, isBillBoard_);

        //��񂪂���̂Ȃ�
        if(effectNum != -1)
            ARGUMENT_INITIALIZE(VFX::GetEmitter(effectNum)->data,data);

        //�X�^�[�g�{�^������������G�t�F�N�g�ăX�^�[�g
        if (ImGui::Button("START"))
        {
            VFX::End(effectNum);
            ARGUMENT_INITIALIZE(effectNum,VFX::Start(data));
        }

        //������G�t�F�N�g�G�N�X�|�[�g�@�\
        if (ImGui::Button("EXPORT"))
            EffectExport();

        //�����̃G�t�F�N�g�C���|�[�g�@�\
        if (ImGui::Button("IMPORT"))
            EffectImport();


        ImGui::End();

        //window���
        ImGui::Begin("BackScreenColor",NULL,ImGuiWindowFlags_NoMove);

        //�w�i�F��GUI��Ō��߂��悤��
        float color[4] = { backScreenColor_.x, backScreenColor_.y, backScreenColor_.z, backScreenColor_.w };
        ImGui::ColorPicker3("", color, ImGuiColorEditFlags_PickerHueWheel);
        backScreenColor_ = XMFLOAT4(color[0], color[1], color[2], color[3]);
        Direct3D::SetBackScreenColor(backScreenColor_);

        ImGui::End();
    }

    //�G�t�F�N�g�Z�[�u
    void ImGuiSet::EffectExport()
    {
        char fileName[MAX_PATH] = "����.txt";  //�t�@�C����������ϐ�

        //�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
        OPENFILENAME ofn;                         	               //���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
        ZeroMemory(&ofn, sizeof(ofn));            	               //�\���̏�����
        ofn.lStructSize = sizeof(OPENFILENAME);   	               //�\���̂̃T�C�Y
        ofn.lpstrFilter = TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");  //�t�@�C���̎��
        ofn.lpstrFile = fileName;               	               //�t�@�C����
        ofn.nMaxFile = MAX_PATH;                 	               //�p�X�̍ő啶����
        ofn.Flags = OFN_OVERWRITEPROMPT;   		                   //�t���O�i�����t�@�C�������݂�����㏑���m�F�j
        ofn.lpstrDefExt = "txt";                  	               //�f�t�H���g�g���q

        //�u�t�@�C����ۑ��v�_�C�A���O
        BOOL selFile;
        selFile = GetSaveFileName(&ofn);

        //�L�����Z�������璆�f
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

        //��������Ԃɂ��Ă���
        ARGUMENT_INITIALIZE(info_, "");

        //���
        info_ += textureFileName_ + "," + std::to_string(data.position.x) + "," + std::to_string(data.position.y) + "," + std::to_string(data.position.z) + "," +
            std::to_string(data.positionRnd.x) + "," + std::to_string(data.positionRnd.y) + "," + std::to_string(data.positionRnd.z) + "," +
            std::to_string(data.direction.x) + "," + std::to_string(data.direction.y) + "," + std::to_string(data.direction.z) + "," +
            std::to_string(data.directionRnd.x) + "," + std::to_string(data.directionRnd.y) + "," + std::to_string(data.directionRnd.z) + "," +
            std::to_string(data.speed) + "," + std::to_string(data.speedRnd) + "," + std::to_string(data.accel) + "," +
            std::to_string(data.gravity) + "," + std::to_string(data.color.x) + "," + std::to_string(data.color.y) + "," +
            std::to_string(data.color.z) + "," + std::to_string(data.color.w) + "," + std::to_string(data.deltaColor.x) + "," +
            std::to_string(data.deltaColor.y) + "," + std::to_string(data.deltaColor.z) + "," + std::to_string(data.deltaColor.w) + "," +
            std::to_string(data.rotate.x) + "," + std::to_string(data.rotate.y) + "," + std::to_string(data.rotate.z) + "," +
            std::to_string(data.rotateRnd.x) + "," + std::to_string(data.rotateRnd.y) + "," + std::to_string(data.rotateRnd.z) + "," +
            std::to_string(data.spin.x) + "," + std::to_string(data.spin.y) + "," + std::to_string(data.spin.z) + "," +
            std::to_string(data.size.x) + "," + std::to_string(data.size.y) + "," + std::to_string(data.sizeRnd.x) + "," +
            std::to_string(data.sizeRnd.y) + "," + std::to_string(data.scale.x) + "," + std::to_string(data.scale.y) + "," +
            std::to_string(data.lifeTime) + "," + std::to_string(data.delay) + "," + std::to_string(data.number) + "," + std::to_string(data.isBillBoard);

        DWORD byte = 0;
        WriteFile(
            hFile_,
            info_.c_str(),
            info_.length(),
            &byte,
            NULL
        );

        CloseHandle(hFile_);
    }

    //�G�t�F�N�g�C���|�[�g
    void ImGuiSet::EffectImport()
    {
        //���݂̃J�����g�f�B���N�g�����o���Ă���
        char defaultCurrentDir[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

        //�t�@�C����������ϐ�
        char fileName[MAX_PATH] = "����.map";

        //�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
        OPENFILENAME ofn;                                          //���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
        ZeroMemory(&ofn, sizeof(ofn));                             //�\���̏�����
        ofn.lStructSize = sizeof(OPENFILENAME);                    //�\���̂̃T�C�Y
        ofn.lpstrFilter = TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");  //�t�@�C���̎��
        ofn.lpstrFile = fileName;               	               //�t�@�C����
        ofn.nMaxFile = MAX_PATH;                 	               //�p�X�̍ő啶����
        ofn.Flags = OFN_FILEMUSTEXIST;   		                   //�t���O�i�����t�@�C�������݂�����㏑���m�F�j
        ofn.lpstrDefExt = "map";                  	               //�f�t�H���g�g���q

        //�u�t�@�C����ۑ��v�_�C�A���O
        BOOL selFile;
        selFile = GetOpenFileName(&ofn);

        //�L�����Z�������璆�f
        if (selFile == FALSE) return;

        //�J�����g�f�B���N�g�������̈ʒu�ɖ߂�
        SetCurrentDirectory(defaultCurrentDir);

        //�t�@�C���I�[�v��
        std::ifstream ifs(fileName);

        //�e�f�[�^��ۑ����Ă����p
        string info[44] = { "" };

        //�z��̌��Ă�ԍ�
        int index = 0;

        //�����܂œǂ�
        while (!ifs.eof())
        {
            //1��buf�Ɋi�[
            string str = { "" };
            std::getline(ifs, str);

            //str�̃T�C�Y�����[�v
            for (int i = 0; i < str.length(); i++)
            {
                //�e�p�����[�^�������data�Ɋi�[���Ă���
                if (str[i] != ',')
                {
                    info[index] += str[i];
                }
                else
                    index++;
            }
        }

        //�e�����
        ARGUMENT_INITIALIZE(textureFileName_, info[0]);
        ARGUMENT_INITIALIZE(position_, XMFLOAT3(std::stof(info[1]), std::stof(info[2]), std::stof(info[3])));
        ARGUMENT_INITIALIZE(positionRnd_, XMFLOAT3(std::stof(info[4]), std::stof(info[5]), std::stof(info[6])));
        ARGUMENT_INITIALIZE(direction_, XMFLOAT3(std::stof(info[7]), std::stof(info[8]), std::stof(info[9])));
        ARGUMENT_INITIALIZE(directionRnd_, XMFLOAT3(std::stof(info[10]), std::stof(info[11]), std::stof(info[12])));
        ARGUMENT_INITIALIZE(speed_, std::stof(info[13]));
        ARGUMENT_INITIALIZE(speedRnd_, std::stof(info[14]));
        ARGUMENT_INITIALIZE(accel_, std::stof(info[15]));
        ARGUMENT_INITIALIZE(gravity_, std::stof(info[16]));
        ARGUMENT_INITIALIZE(color_, XMFLOAT4(std::stof(info[17]), std::stof(info[18]), std::stof(info[19]), std::stof(info[20])));
        ARGUMENT_INITIALIZE(deltaColor_, XMFLOAT4(std::stof(info[21]), std::stof(info[22]), std::stof(info[23]), std::stof(info[24])));
        ARGUMENT_INITIALIZE(rotate_, XMFLOAT3(std::stof(info[25]), std::stof(info[26]), std::stof(info[27])));
        ARGUMENT_INITIALIZE(rotateRnd_, XMFLOAT3(std::stof(info[28]), std::stof(info[29]), std::stof(info[30])));
        ARGUMENT_INITIALIZE(spin_, XMFLOAT3(std::stof(info[31]), std::stof(info[32]), std::stof(info[33])));
        ARGUMENT_INITIALIZE(size_, XMFLOAT2(std::stof(info[34]), std::stof(info[35])));
        ARGUMENT_INITIALIZE(sizeRnd_, XMFLOAT2(std::stof(info[36]), std::stof(info[37])));
        ARGUMENT_INITIALIZE(scale_, XMFLOAT2(std::stof(info[38]), std::stof(info[39])));
        ARGUMENT_INITIALIZE(lifeTime_, std::stof(info[40]));
        ARGUMENT_INITIALIZE(delay_, std::stof(info[41]));
        ARGUMENT_INITIALIZE(number_, std::stof(info[42]));
        ARGUMENT_INITIALIZE(isBillBoard_, std::stoi(info[43]));
    }

    //�e�Z�b�g�֐�
    void ImGuiSet::SetScreenMode(int mode) { screenMode_ = mode; }
    void ImGuiSet::SetGameMode(int mode) { gameMode_ = mode; }

    //�e�Q�b�g�֐�
    int ImGuiSet::GetScreenMode() { return screenMode_; }

    ///////////////////////////////�v���Z�X�������\��///////////////////////////////////////

    void ImGuiSet::ProcessMemory()
    {
        //window���
        ImGui::Begin("ProcessMemory", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //�v���Z�X�������擾
        HANDLE processHandle = GetCurrentProcess();
        PROCESS_MEMORY_COUNTERS_EX pmc;

        for (int i = 0; i < 499; i++)
        {
            processMemory_[i] = processMemory_[i + 1];
        }

        if (GetProcessMemoryInfo(processHandle, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
            processMemory_[499] = (pmc.PrivateUsage / 1024) / 1024;
        }

        //�O���t�\��
        ImGui::PlotLines("", processMemory_, 500, 0, NULL, 1, 1000, ImVec2(580, 200));

        //�I���
        ImGui::End();
    }

    ///////////////////////////////�t�@�C��(�C���|�[�g�E�G�N�X�|�[�g)///////////////////////////////////////

    void ImGuiSet::File()
    {
        //window���
        ImGui::Begin("File", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        //�{�^���쐬
        if (ImGui::Button("Import", ImVec2(240, 55)))
        {
            Direct3D::SetTimeScale(true);
            Import();
        }
        ImGui::SameLine();

        if (ImGui::Button("Export", ImVec2(240, 55)))
        {
            Direct3D::SetTimeScale(true);
            Export();
        }
        ImGui::SameLine();

        //�I���
        ImGui::End();
    }

    //�X�e�[�W�C���|�[�g
    void ImGuiSet::Import()
    {
        //���݂̃J�����g�f�B���N�g�����o���Ă���
        char defaultCurrentDir[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

        //�t�@�C����������ϐ�
        char fileName[MAX_PATH] = "����.map"; 

        //�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
        OPENFILENAME ofn;                                          //���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
        ZeroMemory(&ofn, sizeof(ofn));                             //�\���̏�����
        ofn.lStructSize = sizeof(OPENFILENAME);                    //�\���̂̃T�C�Y
        ofn.lpstrFilter = TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");  //�t�@�C���̎��
        ofn.lpstrFile = fileName;               	               //�t�@�C����
        ofn.nMaxFile = MAX_PATH;                 	               //�p�X�̍ő啶����
        ofn.Flags = OFN_FILEMUSTEXIST;   		                   //�t���O�i�����t�@�C�������݂�����㏑���m�F�j
        ofn.lpstrDefExt = "map";                  	               //�f�t�H���g�g���q

        //�u�t�@�C����ۑ��v�_�C�A���O
        BOOL selFile;
        selFile = GetOpenFileName(&ofn);

        //�L�����Z�������璆�f
        if (selFile == FALSE) return;

        //�J�����g�f�B���N�g�������̈ʒu�ɖ߂�
        SetCurrentDirectory(defaultCurrentDir);

        //�X�e�[�W�쐬
        CreateStage* p = new CreateStage;
        p->LoadFileCreateStage((*GameManager::GetpSceneManager()->GetChildList()->begin()), fileName);
    }

    //�X�e�[�W�I�u�W�F�C���|�[�g���邽�߂̊֐�
    void ImGuiSet::ExportStageObjTransform(GameObject* pObj)
    {

        //�V�[���}�l�[�W���[���V�[���łȂ��̂Ȃ�
        if (pObj != GameManager::GetpSceneManager() && pObj->GetObjectName().find("Scene") != std::string::npos)
        {
            info_ += pObj->GetPathName() + ",";
            info_ += pObj->GetObjectName() + ",";
            info_ += std::to_string(pObj->GetPosition().x) + ",";
            info_ += std::to_string(pObj->GetPosition().y) + ",";
            info_ += std::to_string(pObj->GetPosition().z) + ",";
            info_ += std::to_string(pObj->GetRotate().x) + ",";
            info_ += std::to_string(pObj->GetRotate().y) + ",";
            info_ += std::to_string(pObj->GetRotate().z) + ",";
            info_ += std::to_string(pObj->GetScale().x) + ",";
            info_ += std::to_string(pObj->GetScale().y) + ",";
            info_ += std::to_string(pObj->GetScale().z) + "\r\n";
     
        }

        //�q���̕�������
        for (auto itr = pObj->GetChildList()->begin(); itr != pObj->GetChildList()->end(); itr++)
        {
            ExportStageObjTransform(*itr);
        }
    }

    //�X�e�[�W�G�N�X�|�[�g
    void ImGuiSet::Export()
    {
        char fileName[MAX_PATH] = "����.txt";  //�t�@�C����������ϐ�

        //�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
        OPENFILENAME ofn;                         	               //���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
        ZeroMemory(&ofn, sizeof(ofn));            	               //�\���̏�����
        ofn.lStructSize = sizeof(OPENFILENAME);   	               //�\���̂̃T�C�Y
        ofn.lpstrFilter = TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");  //�t�@�C���̎��
        ofn.lpstrFile = fileName;               	               //�t�@�C����
        ofn.nMaxFile = MAX_PATH;                 	               //�p�X�̍ő啶����
        ofn.Flags = OFN_OVERWRITEPROMPT;   		                   //�t���O�i�����t�@�C�������݂�����㏑���m�F�j
        ofn.lpstrDefExt = "txt";                  	               //�f�t�H���g�g���q

        //�u�t�@�C����ۑ��v�_�C�A���O
        BOOL selFile;
        selFile = GetSaveFileName(&ofn);

        //�L�����Z�������璆�f
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

        //��������Ԃɂ��Ă���
        ARGUMENT_INITIALIZE(info_, "");

        //�X�e�[�W����info�Ɋi�[
        ExportStageObjTransform(GameManager::GetpSceneManager());

        DWORD byte = 0;
        WriteFile(
            hFile_,
            info_.c_str(),
            info_.length(),
            &byte,
            NULL
        );

        CloseHandle(hFile_);
    }

    //�J��
    void ImGuiSet::Release()
    {
    }
}