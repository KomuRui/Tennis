#pragma once
#include "../../Engine/GameObject/GameObject.h"

//�t���[�����[�N�X�V����Ƃ���
namespace FrameWorkUpdateManager
{
	/// <summary>
	/// �X�V
	/// </summary>
	void Update(GameObject* root);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(GameObject* root);

	/// <summary>
	/// ��ڂ̃E�B���h�E�`��
	/// </summary>
	void TwoWindowDraw(GameObject* root);

	/// <summary>
	/// ��l�v���C�̕`��
	/// </summary>
	void OnePlayerDraw(GameObject* root);

	/// <summary>
	/// ��l�v���C�̕`��
	/// </summary>
	void TwoPlayerDraw(GameObject* root);

	//�X�N���[���V���b�g���Ƃ邽�߂̊֐�
	void GameScreenDraw(GameObject* root);

	/// <summary>
	/// �e�`��
	/// </summary>
	void ShadowDraw(GameObject* root);
};

