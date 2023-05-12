#include <Windows.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "GUI/imgui/imgui.h"
#include "GUI/imgui/imgui_impl_win32.h"
#include "GUI/imgui/imgui_impl_dx11.h"
#include "ResourceManager/Global.h"
#include "GameObject/RootObject.h"
#include "ResourceManager/Model.h"
#include "ResourceManager/Image.h"
#include "GameObject/Camera.h"
#include "DirectX/Input.h"
#include "ResourceManager/Audio.h"
#include "GameObject/Light.h"
#include "ResourceManager/Time.h"
#include "ResourceManager/VFX.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/BasePointManager/BasePointManager.h"
#include "GUI/ImGuiSet.h"

#pragma comment(lib,"Winmm.lib")

//�萔�錾
const char* WIN_CLASS_NAME = "�e�j�X�Q�[��";	//�E�B���h�E�N���X��

//�v���g�^�C�v�錾
HWND InitApp(HINSTANCE hInstance, int screenWidth, int screenHeight, int nCmdShow,const char* winName);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


// �G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
//#if defined(DEBUG) | defined(_DEBUG)
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif

	srand((unsigned)time(NULL));
	SetCurrentDirectory("Assets");

	//�������t�@�C���isetup.ini�j����K�v�ȏ����擾
	int screenWidth = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");		//�X�N���[���̕�
	int screenHeight = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");	//�X�N���[���̍���
	int fpsLimit = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");				//FPS�i��ʍX�V���x�j
	int isDrawFps = GetPrivateProfileInt("DEBUG", "ViewFps", 0, ".\\setup.ini");		//�L���v�V�����Ɍ��݂�FPS��\�����邩�ǂ���

	//�E�B���h�E���쐬
	HWND hWnd = InitApp(hInstance, screenWidth, screenHeight, nCmdShow, WIN_CLASS_NAME);
	HWND hWndTool = InitApp(hInstance, 960, 540, nCmdShow, WIN_CLASS_NAME);

	//Direct3D����
	Direct3D::Initialize(hWnd, screenWidth, screenHeight);
	Direct3D::InitializeTwo(hWndTool, 960, 540);

	//�J����������
	Camera::Initialize();

	//���C�g������
	Light::Initialize();

	//���͏����i�L�[�{�[�h�A�}�E�X�A�R���g���[���[�j�̏���
	Input::Initialize(hWnd, hWndTool);

	//�I�[�f�B�I�i���ʉ��j�̏���
	Audio::Initialize(hWnd);

	//�^�C���̏�����
	Time::Initialize(fpsLimit);

	//�Q�[���}�l�W���[�̏���
	GameManager::Initialize();

	//ImGui�̏�����
	ImGuiSet::Initialize();

	//���[�g�I�u�W�F�N�g����
	//���ׂẴQ�[���I�u�W�F�N�g�̐e�ƂȂ�I�u�W�F�N�g
	RootObject* pRootObject = new RootObject;
	pRootObject->Initialize();

	//Imgui�Z�b�g
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& ui = ImGui::GetIO();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(Direct3D::pDevice_, Direct3D::pContext_);
	ImGui::StyleColorsDark();
	ui.Fonts->Clear();
	ui.Fonts->AddFontFromFileTTF("Text/GuiFont.ttf", 25);
	ui.FontDefault = ui.Fonts->Fonts[0];
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);

	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����i���������D��j
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ��i�����ŃQ�[���̏����j
		else
		{
			//���Ԍv��
			timeBeginPeriod(1);	//���Ԍv���̐��x���グ��
			static int FPS = 0;								//��ʍX�V�񐔂̃J�E���^
			static DWORD lastFpsResetTime = timeGetTime();	//�Ō�ɃL���v�V������FPS��\������
			static DWORD lastUpdateTime = timeGetTime();	//�Ō�ɉ�ʂ��X�V��������
			DWORD nowTime = timeGetTime();					//���݂̎���

			//�L���v�V�����Ɍ��݂�FPS��\������
			if (isDrawFps)
			{
				//1�b�i1000�~���b�j�o������
				if (nowTime - lastFpsResetTime > 1000)
				{
					//FPS�̒l��\��
					char string[16];
					wsprintf(string, "FPS:%d", FPS);
					SetWindowText(GetActiveWindow(), string);
					FPS = 0;
					lastFpsResetTime = nowTime;
				}
			}


			//�w�肵�����ԁiFPS��60�ɐݒ肵���ꍇ��60����1�b�j�o�߂��Ă�����X�V����
			if ((nowTime - lastUpdateTime) * fpsLimit > 1000.0f)
			{
				//���Ԍv���֘A
				lastUpdateTime = nowTime;	//���݂̎��ԁi�Ō�ɉ�ʂ��X�V�������ԁj���o���Ă���
				FPS++;						//��ʍX�V�񐔂��J�E���g����

			    //���́i�L�[�{�[�h�A�}�E�X�A�R���g���[���[�j�����X�V
				Input::Update();

				//���Ԏ~�߂Ă��Ȃ��̂Ȃ�
				if (!Direct3D::GetTimeScale())
				{
					//�^�C���X�V
					Time::Update();

					//�S�I�u�W�F�N�g�̍X�V����
					//���[�g�I�u�W�F�N�g��Update���Ă񂾂��ƁA�����I�Ɏq�A����Update���Ă΂��
					pRootObject->StartUpdateSub();
					pRootObject->UpdateSub();
				}
				
				//�}�l�[�W���̍X�V�������Ă�
				GameManager::Update();

				//�J�����̍X�V
				Camera::Update();

				//�`��J�n
				Direct3D::BeginDraw();

				//�G�t�F�N�g�G�f�B�^���[�h����Ȃ��̂Ȃ�
				if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
					pRootObject->DrawSub();   

				//���Ԏ~�߂Ă��Ȃ����G�t�F�N�g�G�f�B�^���[�h�Ȃ�
				if (!Direct3D::GetTimeScale() || ImGuiSet::GetScreenMode() == static_cast<int>(Mode::EFFECT_EDIT))
				{
					//�G�t�F�N�g�̍X�V
					VFX::Update();
				}

				//�G�t�F�N�g�̕`��
				VFX::Draw();

				//�G�t�F�N�g�G�f�B�^���[�h����Ȃ��̂Ȃ�
				if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
				{
					//�����E�������`��
					pRootObject->TransparentDrawSub();
				
					//�l�X�ȕ`�揈��������
					GameManager::Draw();
				}

				//�Q�[����ʂ̃T�C�Y���Ƃ̊eGUI�`��
				Direct3D::GetGameFull() ? ImGuiSet::GameScreenFullDraw()
										: ImGuiSet::GameScreenNotFullDraw();

				//��ڂ̃E�B���h�E�`��
				Camera::Update2();
				Direct3D::BeginDrawTwo();
				pRootObject->TwoWindowDrawSub();

				//GUI�\��
				ImGuiSet::TwoWindowDraw();

				Direct3D::EndDraw();

				//������Ƌx�܂���
				Sleep(1);
			}
			timeEndPeriod(1);	//���Ԍv���̐��x��߂�
		}
	}

	//��������
	BasePointManager::BasePointExport();

	//���낢����
	Audio::AllRelease();
	Model::AllRelease();
	Image::AllRelease();
	pRootObject->ReleaseSub();
	SAFE_DELETE(pRootObject);
	Direct3D::Release();

	return 0;
}

//�E�B���h�E�̍쐬
HWND InitApp(HINSTANCE hInstance, int screenWidth, int screenHeight, int nCmdShow, const char* winName)
{
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);					//���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;						//�C���X�^���X�n���h��
	wc.lpszClassName = winName;						//�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;						//�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;				//�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);	//�A�C�R��
	wc.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);	//�������A�C�R��
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	//�}�E�X�J�[�\��
	wc.lpszMenuName = nullptr;						//���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//�w�i�i���j
	RegisterClassEx(&wc);

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, screenWidth, screenHeight };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);

	//�^�C�g���o�[�ɕ\��������e
	char caption[64];
	GetPrivateProfileString("SCREEN", "Caption", "***", caption, 64, ".\\setup.ini");

	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		winName,						//�E�B���h�E�N���X��
		caption,						//�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW,			//�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,					//�\���ʒu���i���܂����j
		CW_USEDEFAULT,					//�\���ʒu��i���܂����j
		winRect.right - winRect.left,	//�E�B���h�E��
		winRect.bottom - winRect.top,	//�E�B���h�E����
		nullptr,						//�e�E�C���h�E�i�Ȃ��j
		nullptr,						//���j���[�i�Ȃ��j
		hInstance,						//�C���X�^���X
		nullptr							//�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	return hWnd;
}

//Imgui�̂��
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lparam);

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	//�E�B���h�E�����
	case WM_DESTROY:
		PostQuitMessage(0);	//�v���O�����I��
		return 0;

	//�}�E�X��������
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}