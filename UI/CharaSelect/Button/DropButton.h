#pragma once
#include "../../Button/EasingButton.h"
#include "../CharaSelectSceneUI.h"

/// <summary>
/// ���{�^��
/// </summary>
class DropButton : public EasingButton
{
	//UI�������Ă���
	CharaSelectSceneUI* charaSelectSceneUI;

	//�L�����摜
	int hCharaPict_;
	std::unique_ptr<Transform> tCharaPict_;        //�g�����X�t�H�[��
	std::unique_ptr<EasingMove> easingCharaPict_;  //�C�[�W���O�p

public:

	//�R���X�g���N�^
	DropButton(GameObject* parent, std::string modelPath, std::string name);

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

