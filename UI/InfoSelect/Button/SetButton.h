#pragma once
#include "../../Button/EasingButton.h"
#include "../../../Engine/ResourceManager/Text.h"

/// <summary>
/// �Z�b�g���{�^��
/// </summary>
class SetButton : public EasingButton
{
	std::unique_ptr<EasingMove> easingSelectPict_; //�I������Ă���Ƃ��̉摜�̃C�[�W���O�p
	std::unique_ptr<Text>       setNumText_;       //�Z�b�g���̃e�L�X�g
	Transform tSelectPict_;                        //�I������Ă���Ƃ��̉摜�̃g�����X�t�H�[��
	int hSelectPict_;                              //�I������Ă���Ƃ��̉摜�ԍ�
	int hTextPict_;								   //�����摜�ԍ�
	int setNum_;                                   //�Q�[����

public:

	//�R���X�g���N�^
	SetButton(GameObject* parent, std::string modelPath, std::string name);

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

