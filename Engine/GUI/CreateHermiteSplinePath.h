#pragma once

/// <summary>
/// �G���~�[�g�X�v���C���̃p�X�쐬
/// </summary>
namespace CreateHermiteSplinePath
{
	/// <summary>
	/// �E�B���h�E�`��
	/// </summary>
	void WindowDraw();

	/// <summary>
	/// ���ׂẴp�X����`��
	/// </summary>
	void AllPathInfoGuiDraw();

	/// <summary>
	/// �p�X�ǉ�
	/// </summary>
	void AddPath();

	/// <summary>
	/// �Z�[�u
	/// </summary>
	void Save();

	////////////////////////////////////////�Z�b�^�[�E�Q�b�^�[////////////////////////////////////////////

	/// <summary>
	/// �E�B���h�E��`�悷�邩�ݒ�
	/// </summary>
	/// <param name="flag">true�Ȃ�`�悷��</param>
	void SetWindowDraw(bool flag);

	/// <summary>
	/// �E�B���h�E�`�悵�Ă��邩
	/// </summary>
	/// <returns>true�Ȃ�`�悵�Ă���</returns>
	bool isWindowDraw();
}
