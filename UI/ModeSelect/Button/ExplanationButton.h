#pragma once
#include "../../Button/EasingButton.h"

/// <summary>
/// �����т����{�^��
/// </summary>
class ExplanationButton : public EasingButton
{
	//int a_;
	int hSelectPict_;    //�I������Ă���Ƃ��̉摜�ԍ�
	int hTextPict_;      //�����摜�ԍ�

public:

	//�R���X�g���N�^
	ExplanationButton(GameObject* parent, std::string modelPath, std::string name);
	~ExplanationButton() {};

	////////////////////�I�[�o�[���C�h����֐�/////////////////////////

	/// <summary>
	/// ������
	/// </summary>
	void ChildInitialize() override;

	/// <summary>
	/// �`��
	/// </summary>
	void ChildDraw() override;

	/// <summary>
	/// �{�^���������ꂽ�牽���邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
	void IsButtonPush() override;

	/// <summary>
	/// �{�^�����I�����ꂽ�u�Ԃɉ������邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
	void IsButtonSelect() override;

	/// <summary>
	/// �{�^�����I���������ꂽ�u�Ԃɉ������邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
	void IsButtonSelectRelease() override;
};

