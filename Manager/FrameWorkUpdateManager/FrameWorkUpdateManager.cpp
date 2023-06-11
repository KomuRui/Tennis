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
		//�v���C�l���̂���ď����𕪂���
		switch (GameManager::GetPlayers())
		{

		//��l�v���C
		case Players::ONE:
			OnePlayerDraw(root);
			break;

		//��l�v���C
		case Players::TWO:
			TwoPlayerDraw(root);
			break;

		//����ȊO
		default:
			break;
		}

		//�v���W�F�N�V�������X�V
		Camera::SetProj(Direct3D::vp.Width, Direct3D::vp.Height);

		//�`��J�n
		Direct3D::SetViewPort(Direct3D::vp);

		//�G�t�F�N�g�G�f�B�^���[�h����Ȃ��̂Ȃ�
		if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
		{
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
		Camera::TwoWindowUpdate();
		Direct3D::BeginDrawTwo();
		root->TwoWindowDrawSub();

		//GUI�\��
		ImGuiSet::TwoWindowDraw();

		//�`��I��
		Direct3D::EndDraw();
	}

	/// <summary>
	/// ��l�v���C�̕`��
	/// </summary>
	void OnePlayerDraw(GameObject* root)
	{
		//�v���W�F�N�V�������X�V
		Camera::SetProj(Direct3D::vp.Width, Direct3D::vp.Height);

		//�r���[�|�[�g�ݒ�
		Direct3D::SetViewPort(Direct3D::vp);
		Direct3D::SetClipToUv(Direct3D::vp);
		
		//��ɉe�p�̃e�N�X�`�����쐬
		ShadowDraw(root);

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

	}

	/// <summary>
	/// ��l�v���C�̕`��
	/// </summary>
	void TwoPlayerDraw(GameObject* root)
	{
		/////////////��

		//�v���W�F�N�V�����ƃr���[�|�[�g���X�V
		Camera::SetProj(Direct3D::vpLeft.Width, Direct3D::vpLeft.Height);
		Direct3D::SetViewPort(Direct3D::vpLeft);
		Direct3D::SetClipToUv(Direct3D::vpLeft);

		//�e�`��
		ShadowDraw(root);

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
		}

		/////////////�E

		//�J�����ւ���
		XMFLOAT3 pos = Camera::GetPosition();
		XMFLOAT3 tar = Camera::GetTarget();
		XMVECTOR up = Camera::GetUp();
		Camera::SetPosition(Camera::GetPositionTwo());
		Camera::SetTarget(Camera::GetTargetTwo());
		Camera::SetUpDirection(Camera::GetUpTwo());
		Camera::UpdateTwo();

		//�v���W�F�N�V�����ƃr���[�|�[�g���X�V
		Camera::SetProj(Direct3D::vpRight.Width, Direct3D::vpRight.Height);
		Direct3D::SetViewPort(Direct3D::vpRight);

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
		}

		Camera::SetPosition(pos);
		Camera::SetTarget(tar);
		Camera::SetUpDirection(up);
	}

	/// <summary>
	/// �e�`��
	/// </summary>
	void ShadowDraw(GameObject* root)
	{
		//�e�`��J�n
		ARGUMENT_INITIALIZE(Direct3D::isShadowDraw, true);

		//�V���h�E�}�b�v�쐬
		//���C�g�̈ʒu���猩���摜���A�����͔��A�߂��͍��̃O���[�X�P�[���ŕ\��
		XMFLOAT3 pos = Camera::GetPosition();
		XMFLOAT3 tar = Camera::GetTarget();
		XMVECTOR up = Camera::GetUp();
		Camera::SetPosition(XMFLOAT3(-25, 20, -25));
		Camera::SetTarget(XMFLOAT3(0, 0, 0));
		Camera::SetUpDirection(XMVectorSet(0,0,1,0));
		Camera::FrameCameraInitialize();
		Camera::UpdateTwo();
		Direct3D::lightView_ = Camera::GetViewMatrix();

		Direct3D::BrginDrawShadowToTexture();

		//�I�u�W�F�N�g�̉e�`��
		root->ShadowDraw();

		//�G�t�F�N�g�̕`��
		VFX::Draw();

		//�G�t�F�N�g�G�f�B�^���[�h����Ȃ��̂Ȃ�
		if (ImGuiSet::GetScreenMode() != static_cast<int>(Mode::EFFECT_EDIT))
		{
			//�����E�������`��
			root->TransparentDrawSub();
		}

		//�`��I��
		Direct3D::EndDraw();

		//�J�������ɖ߂�
		Camera::SetPosition(pos);
		Camera::SetTarget(tar);
		Camera::SetUpDirection(up);
		Camera::FrameCameraInitialize();
		Camera::UpdateTwo();

		//�e�`��I��
		ARGUMENT_INITIALIZE(Direct3D::isShadowDraw, false);
	}

};

