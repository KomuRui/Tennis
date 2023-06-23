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
/// �G���~�[�g�X�v���C���̃p�X�쐬
/// </summary>
namespace CreateHermiteSplinePath
{

	//���ׂẴp�X���i�[�����Ă������X�g
	vector<NormalObject*> allPath_;

	//�E�B���h�E��`��
	bool isWindowDraw_ = false;

	//�E�B���h�E�`��
	void WindowDraw()
	{
		//window���
		if (Direct3D::GetWindowHandle() == GetForegroundWindow())
			ImGui::Begin("CreateHermiteSplinePath", NULL);
		else
			ImGui::Begin("CreateHermiteSplinePath", NULL,ImGuiWindowFlags_NoInputs);

		//GUI�`��
		AllPathInfoGuiDraw();

		//�I���
		ImGui::End();

	}

	//���ׂẴp�X����`��
	void AllPathInfoGuiDraw()
	{
		//�Z�[�u�{�^��
		if (ImGui::Button("AddPath")) AddPath();

		//�p�X�̐��J�E���g�p
		int count = 0;

		for (auto i = allPath_.begin(); i != allPath_.end(); i++)
		{
			//i��Path�̌��ɂ���
			char name[16];
			sprintf_s(name, "Path %d", count++);

			//Path
			if (ImGui::TreeNode(name)) {

				//�|�W�V������ۑ����Ă���
				XMFLOAT3 pos = (*i)->GetComponent<Transform>()->GetPosition();

				//Position�Z�b�g
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

				//�ʒu�X�V
				(*i)->GetComponent<Transform>()->SetPosition(pos);

				ImGui::TreePop();
			}
		}

		//�Z�[�u�{�^��
		if (ImGui::Button("Save")) Save();

		//�I���{�^��
		if (ImGui::Button("Close")) ARGUMENT_INITIALIZE(isWindowDraw_, false);

	}

	//�p�X�ǉ�
	void AddPath()
	{
		//�p�X�I�u�W�F�N�g����
		NormalObject* pNew = new NormalObject(GameManager::GetpSceneManager(),"Tool/ToolModel/HermiteSplinePath.fbx", "");
		if (GameManager::GetpSceneManager()->GetParent() != nullptr) GameManager::GetpSceneManager()->PushBackChild(pNew);
		pNew->Initialize();

		//���C���[�t���[����Ԃɂ���
		ModelManager::SetShederType(pNew->GetModelNum(), Direct3D::SHADER_UNLIT);

		//�p�X�ǉ�
		allPath_.push_back(pNew);
	}

	//�Z�[�u
	void Save()
	{
		char fileName[MAX_PATH] = "����.json";  //�t�@�C����������ϐ�

		//�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
		OPENFILENAME ofn;                         	               //���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
		ZeroMemory(&ofn, sizeof(ofn));            	               //�\���̏�����
		ofn.lStructSize = sizeof(OPENFILENAME);   	               //�\���̂̃T�C�Y
		ofn.lpstrFilter = TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");  //�t�@�C���̎��
		ofn.lpstrFile = fileName;               	               //�t�@�C����
		ofn.nMaxFile = MAX_PATH;                 	               //�p�X�̍ő啶����
		ofn.Flags = OFN_OVERWRITEPROMPT;   		                   //�t���O�i�����t�@�C�������݂�����㏑���m�F�j
		ofn.lpstrDefExt = "json";                  	               //�f�t�H���g�g���q

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

		CloseHandle(hFile_);

		//�������ݗp
		json json_object;

		//�p�X�̐��J�E���g�p
		int count = 0;

		//�ۑ��������l��ݒ�
		for (auto i = allPath_.begin(); i != allPath_.end(); i++)
		{
			//i��Path�̌��ɂ���
			char name[16];
			sprintf_s(name, "Path%d", count++);

			//�ʒu�i�[
			XMFLOAT3 pos = (*i)->GetComponent<Transform>()->GetPosition();
			json_object[name]["Position"] = { pos.x,pos.y,pos.z };
		}

		//��������
		std::ofstream output_file(fileName);
		output_file << json_object;
		output_file.close();
	}

	////////////////////////////////////////�Z�b�^�[�E�Q�b�^�[////////////////////////////////////////////

	//�E�B���h�E��`�悷�邩�ݒ�
	void SetWindowDraw(bool flag) { isWindowDraw_ = flag; }

	//�E�B���h�E�`�悵�Ă��邩
	bool isWindowDraw() { return isWindowDraw_; }
}
