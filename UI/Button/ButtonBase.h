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
	
	//�����̑O�ɑI������Ă����{�^���̃|�W�V�������i�[
	XMFLOAT3 beforeButtonSelectPos_;

	//���Ԃ̃R���g���[���[�ɉ����ꂽ�̂�
	int numController_;

	//�I������Ă��邩�ǂ���
	bool isSelect_;

	//���������ǂ���
	bool isMove_;

	//���ł����������ǂ���
	bool isPush_;

	//�I�𒆂��ύX����邩�ǂ���
	bool isSelectNoChange_;

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
	void SetSelect(bool flag, int numController);

	/// <summary>
	/// �I������Ă��邩���擾
	/// </summary>
	/// <returns>true�Ȃ�I������Ă���</returns>
	bool IsSelect() { return isSelect_; }

	/// <summary>
	/// �����Ă��邩�Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ瓮���Ă���</param>
	void SetMove(bool flag);

	/// <summary>
	/// �����Ă��邩�擾
	/// </summary>
	/// <returns>true�Ȃ瓮���Ă���</returns>
	bool IsMove() { return isMove_; }

	/// <summary>
	/// �I�𒆂��ύX����邩�Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ瓮���Ă���</param>
	void SetSelectNoChange(bool flag) { isSelectNoChange_ = flag; }

	/// <summary>
	/// �I�𒆂��ύX����邩�ǂ����擾
	/// </summary>
	/// <returns>true�Ȃ�ύX����Ȃ�</returns>
	bool IsSelectNoChange() { return isSelectNoChange_; }

	/// <summary>
	/// �����̑O�ɑI������Ă����{�^���̃|�W�V�������Z�b�g
	/// </summary>
	/// <param name="pos">�ʃ|�W�V������u</param>
	void SetBeforeButtonSelectPos(XMFLOAT3 pos) { beforeButtonSelectPos_ = pos; }

	/// <summary>
	/// �R���g���[���[�ԍ����擾
	/// </summary>
	/// <returns>�R���g���[���[�ԍ�</returns>
	int GetControllerNum() { return numController_; }
};

