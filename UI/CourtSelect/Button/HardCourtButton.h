#pragma once
#include "../../Button/EasingButton.h"

/// <summary>
/// �n�[�h�R�[�g�{�^��
/// </summary>
class HardCourtButton : public EasingButton
{
	std::unique_ptr<EasingMove> easingSelectPict_; //�I������Ă���Ƃ��̉摜�̃C�[�W���O�p
	Transform tSelectPict_;                        //�I������Ă���Ƃ��̉摜�̃g�����X�t�H�[��
	Transform tCourtInfoPict_;                     //�R�[�g���̉摜�̃g�����X�t�H�[��
	int hSelectPict_;                              //�I������Ă���Ƃ��̉摜�ԍ�
	int hTextPict_;								   //�����摜�ԍ�
	int hCourtInfoPict_;                           //�R�[�g���̉摜�ԍ�

public:

	//�R���X�g���N�^
	HardCourtButton(GameObject* parent, std::string modelPath, std::string name);

	////////////////////�I�[�o�[���C�h����֐�/////////////////////////

	/// <summary>
	/// ������
	/// </summary>
	void ChildInitialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void EasingButtonChileUpdate() override;

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

