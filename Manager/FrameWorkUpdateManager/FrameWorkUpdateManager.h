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
};

