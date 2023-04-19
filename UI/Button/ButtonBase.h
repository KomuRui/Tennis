#pragma once
#include "../ImageBase.h"

/// <summary>
/// �{�^���N���X
/// </summary>
class ButtonBase : public ImageBase
{
protected:

	//�{�^�����I������Ă���Ƃ��������邩�̊֐��|�C���^
	void(*ButtonSelectingFunc)(void);

	//�������Ƃ��̊֐��|�C���^
	void(*OnPushFunc)(void);

	//�{�^���I�����ꂽ�u�ԂɌĂԊ֐��|�C���^
	void(*ButtonSelectFunc)(void);

	//�{�^�����I���������ꂽ�u�ԂɌĂԊ֐��|�C���^
	void (*ButtonSelectReleaseFunc)(void);

	//�I������Ă��邩�ǂ���
	bool isSelect_;

	//�����̋����邩
	bool isPushOk_;

	//���ł����������ǂ���
	bool isPush_;        

public:

	//�R���X�g���N�^
	ButtonBase(GameObject* parent, std::string modelPath, std::string name);
	
	////////////////////�I�[�o�[���C�h����֐�/////////////////////////

	//�X�V
	void ChildUpdate() override;

	//������
	virtual void ChildInitialize() override {};

	//�`��
	virtual void ChildDraw() override {};

	/////////////////////////////�֐�////////////////////////////////

	/// <summary>
	/// �p����p�̍X�V
	/// </summary>
	virtual void ChildButtonUpdate() {};

	/// <summary>
	/// �{�^�����I������Ă���Ƃ��������邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
	virtual void IsButtonSelecting() {};

	/// <summary>
	/// �{�^���������ꂽ�牽���邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
	virtual void IsButtonPush() {};

	/// <summary>
	/// �{�^�����I�����ꂽ�u�Ԃɉ������邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
	virtual void IsButtonSelect() {};

	/// <summary>
	/// �{�^�����I���������ꂽ�u�Ԃɉ������邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
	virtual void IsButtonSelectRelease() {};

	//////////////////////////�Z�b�g�Q�b�g�֐�/////////////////////////////

	/// <summary>
	/// �I������Ă��邩���Z�b�g 
	/// </summary>
	/// <param name="flag">true�Ȃ�I������Ă�</param>
	void SetSelect(bool flag);

	/// <summary>
	/// �I������Ă��邩���擾
	/// </summary>
	/// <returns>true�Ȃ�I������Ă���</returns>
	bool IsSelect() { return isSelect_; }

	/// <summary>
	/// �����̂������邩�Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ狖����</param>
	void SetPushOk(bool flag);
};

