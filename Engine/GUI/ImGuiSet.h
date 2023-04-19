#pragma once
#include "../GameObject/GameObject.h"
#include "../../Player/PlayerBase.h"

//�ő��Imgui�ŏo����I�u�W�F�N�g�T�C�Y
static const int MAX_OBJECT_SIZE = 50;

//�G�f�B�^���[�h
enum class Mode
{
	GAME = 0,
	SCENE,
	EFFECT_EDIT,
	START,
	STOP
};

/// <summary>
/// Debug�p��UI��\������
/// </summary>
namespace ImGuiSet
{

	//������
	void Initialize();

	//�Q�[����ʂ��t���T�C�Y�ł͂Ȃ����̕`��
	void GameScreenNotFullDraw();

	//�Q�[����ʂ��t���T�C�Y�̎��̕`��
	void GameScreenFullDraw();

	//�J��
	void Release();

	////////////////////////////////////�X�e�[�W�쐬�pImGui///////////////////////////////////////

	/// <summary>
	/// �X�e�[�W�쐬����ImGui��UI���o���Ă����
	/// </summary>
	void StageCreater();

	/// <summary>
	/// 3D�I�u�W�F�N�g�쐬
	/// </summary>
	void Create3D();

	/// <summary>
	/// �Ŕ쐬
	/// </summary>
	void CreateSigeboard();

	/// <summary>
	/// �J�����̑J�ڍ쐬(�R���C�_�[�ɓ���������J�����̃|�W�V�����ς���@�\)
	/// </summary>
	void CreateCameraTransition();

	/// <summary>
	/// �摜�쐬
	/// </summary>
	void CreateImage();

	//////////////////////////////�X�e�[�W�̃I�u�W�F�N�g�̃g�����X�t�H�[���\��////////////////////////////

	/// <summary>
	/// �X�e�[�W�I�u�W�F�̃g�����X�t�H�[�����ׂĕ\������ImGui��\��
	/// </summary>
	void StageObjImGuiDisplay();

	/// <summary>
	/// �X�e�[�W�I�u�W�F�̃g�����X�t�H�[�����ׂĕ\��
	/// </summary>
	void StageObjTransformDisplay(GameObject* pObj);

	//////////////////////////////////////���O�\��///////////////////////////////////////

	/// <summary>
	/// �f�o�b�O���O���Ǘ�����(ImGui�͂����ŕ\������)
	/// </summary>
	void DebugLogManager();

	/// <summary>
	/// �C�ӂ̒l��\�����Ă����
	/// </summary>
	/// <param name="text">�\���������ϐ��̖��O</param>
	/// <param name="num">�\���������l</param>
	void DebugLog(std::string text ,int num);
	void DebugLog(std::string text, float num);
	void DebugLog(std::string text, bool num);
	void DebugLog(std::string text, XMFLOAT3 num);
	void DebugLog(std::string text, std::string str);

	///////////////////////////////�V�[���ύX�\��///////////////////////////////////////

	/// <summary>
	/// �V�[���ύX�p�{�^���\��
	/// </summary>
	void SceneChangeButton();

	///////////////////////////////�Q�[����ʐݒ�///////////////////////////////////////

	/// <summary>
	/// �Q�[����ʂ��t���T�C�Y�ł͂Ȃ����̐ݒ�
	/// </summary>
	void GameScreenNotFullPreference();

	/// <summary>
	/// �Q�[����ʂ��t���T�C�Y�̎��̐ݒ�
	/// </summary>
	void GameScreenFullPreference();

	/// <summary>
	/// �G�t�F�N�g�G�f�B�^��GUI
	/// </summary>
	void EffectEditGui();

	/// <summary>
	/// ��ʂ̏�Ԑݒ�
	/// </summary>
	void ScreenStatusPreference();

	/// <summary>
	/// �G�t�F�N�g�G�N�X�|�[�g
	/// </summary>
	void EffectExport();

	/// <summary>
	/// �G�t�F�N�g�C���|�[�g
	/// </summary>
	void EffectImport();

	/// <summary>
	/// �e�Z�b�g�֐�
	/// </summary>
	/// <param name="mode">�Z�b�g���������[�h</param>
	void SetScreenMode(int mode);
	void SetGameMode(int mode);

	/// <summary>
	/// �e�Q�b�g�֐�
	/// </summary>
	/// <returns>�G�f�B�^���[�h���擾</returns>
	int GetScreenMode();

	///////////////////////////////�v���Z�X�������\��///////////////////////////////////////

	/// <summary>
	/// �v���Z�X�������\��
	/// </summary>
	void ProcessMemory();

	///////////////////////////////�t�@�C��(�C���|�[�g�E�G�N�X�|�[�g)///////////////////////////////////////

	/// <summary>
	/// �t�@�C�����\��
	/// </summary>
	void File();

	/// <summary>
	/// �X�e�[�W�C���|�[�g
	/// </summary>
	void Import();

	/// <summary>
	/// �X�e�[�W�I�u�W�F�G�N�X�|�[�g���邽�߂̊֐�
	/// </summary>
	/// <param name="pObj">SceneManager������</param>
	void ExportStageObjTransform(GameObject* pObj);

	/// <summary>
	/// �X�e�[�W�G�N�X�|�[�g
	/// </summary>
	void Export();
};