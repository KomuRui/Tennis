#include "FrameWorkUpdateManager.h"
#include "../../Engine/DirectX/Direct3D.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/ResourceManager/VFX.h"
#include "../GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/Time.h"
#include "../../Engine/GUI/ImGuiSet.h"

//�t���[�����[�N�Ǘ�����Ƃ���
namespace FrameWorkUpdateManager
{
	//�X�V
	void Update(GameObject *root)
	{
		//���́i�L�[�{�[�h�A�}�E�X�A�R���g���[���[�j�����X�V
		Input::Update();

		//���Ԏ~�߂Ă��Ȃ��̂Ȃ�
		if (!Direct3D::GetTimeScale())
		{
			//�^�C���X�V
			Time::Update();

			//�S�I�u�W�F�N�g�̍X�V����
			//���[�g�I�u�W�F�N�g��Update���Ă񂾂��ƁA�����I�Ɏq�A����Update���Ă΂��
			root->StartUpdateSub();
			root->UpdateSub();
		}

		//�}�l�[�W���̍X�V�������Ă�
		GameManager::Update();

		//���Ԏ~�߂Ă��Ȃ����G�t�F�N�g�G�f�B�^���[�h�Ȃ�
		if (!Direct3D::GetTimeScale() || ImGuiSet::GetScreenMode() == static_cast<int>(Mode::EFFECT_EDIT))
		{
			//�G�t�F�N�g�̍X�V
			VFX::Update();
		}

		//�J�����̍X�V
		Camera::Update();

		//�`��
		Draw(root);
	}

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(GameObject* root)
	{
		//�`��J�n
		Direct3D::BeginDraw();

		//�G�t�F�N�g�G�f�B�^���[�h����Ȃ��̂Ȃ�
		if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
			root->DrawSub();

		//�G�t�F�N�g�̕`��
		VFX::Draw();

		//�G�t�F�N�g�G�f�B�^���[�h����Ȃ��̂Ȃ�
		if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
		{
			//�����E�������`��
			root->TransparentDrawSub();

			//�l�X�ȕ`�揈��������
			GameManager::Draw();
		}

		//�Q�[����ʂ̃T�C�Y���Ƃ̊eGUI�`��
		Direct3D::GetGameFull() ? ImGuiSet::GameScreenFullDraw()
								: ImGuiSet::GameScreenNotFullDraw();

		//�`��I��
		Direct3D::EndDraw();

		//��ڂ̃E�B���h�E�`��
		TwoWindowDraw(root);
	}

	/// <summary>
	/// ��ڂ̃E�B���h�E�`��
	/// </summary>
	void TwoWindowDraw(GameObject* root)
	{
		//��ڂ̃E�B���h�E�`��
		Camera::Update2();
		Direct3D::BeginDrawTwo();
		root->TwoWindowDrawSub();

		//GUI�\��
		ImGuiSet::TwoWindowDraw();

		//�`��I��
		Direct3D::EndDraw();
	}
};

