#pragma once
#include <string>

//�t�F�[�h�̏�Ԃ̗񋓌^
enum FadeStatus
{
	NOOP,			 //�������Ȃ�
	DRAW,			 //�摜�����\��
	FADE_CIRCLE_IN,  //�~�̃t�F�[�h�C��
	FADE_CIRCLE_OUT, //�~�̃t�F�[�h�A�E�g
	FADE_NORMAL_IN,  //�ʏ�̃t�F�[�h�C��
	FADE_NORMAL_OUT, //�ʏ�̃t�F�[�h�A�E�g
	FADE_GAME_OVER	 //�Q�[���I�[�o�[ 
};

/// <summary>
/// �t�F�[�h���s���Ƃ��Ɏg��(��̂P�x�ɂP�񂵂��g���Ȃ��̂�namespace)
/// </summary>
namespace Fade
{
	///////////////////////////////�֐�//////////////////////////////////

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	///////////////////////////////�t�F�[�h�p�֐�////////////////////////////////////

	/// <summary>
	/// ���ʂ̉摜��\��
	/// </summary>
	void NormalDraw();

	/// <summary>
	/// ��Ԃɂ���ČĂԊ֐�������
	/// </summary>
	void FadeDraw();

	/// <summary>
	/// �t�F�[�h�C���`��
	/// </summary>
	void FadeInCircleDraw();

	/// <summary>
	/// �t�F�[�h�A�E�g�`��
	/// </summary>
	void FadeOutCircleDraw();

	/// <summary>
	/// �t�F�[�h�C���`��
	/// </summary>
	void FadeInNormalDraw();

	/// <summary>
	/// �t�F�[�h�A�E�g�`��
	/// </summary>
	void FadeOutNormalDraw();

	/// <summary>
	/// �Q�[���I�[�o�[�`��
	/// </summary>
	void GameOverDraw();

	/// <summary>
	/// ��Ԃ��Z�b�g
	/// </summary>
	/// <param name="status">�Z�b�g���������</param>
	/// <param name="filename"></param>
	void SetFadeStatus(int status, std::string filename = "");

	/// <summary>
	/// ���݂̏�Ԃ��擾
	/// </summary>
	/// <returns>���݂̏��</returns>
	int GetFadeStatus();

	/// <summary>
	/// �ʏ�̃t�F�[�h����������Ȃ����ǂ���
	/// </summary>
	/// <returns>��������Ȃ��Ȃ�true</returns>
	bool isNormalFadeNotTransparency();
}

