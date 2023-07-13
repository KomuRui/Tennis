#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/Component/EasingMove.h"
#include <map>

/// <summary>
/// �L�����I���V�[����UI
/// </summary>
class CharaSelectSceneUI : public GameObject
{

	//�eUI�쐬�p
	std::unique_ptr<CreateStage> pCreateImage_ = std::make_unique<CreateStage>();

	//�I���摜�̏��
	struct selectPictInfo
	{
		int hPict_;                                    //�摜�ԍ�
		int hPictOK_;								   //OK�����Ƃ��̉摜�ԍ�
		bool isOK_;									   //OK�������ǂ���
		std::shared_ptr<Transform> transform_;         //�g�����X�t�H�[��
		std::unique_ptr<EasingMove> easingSelectPict_; //�I������Ă���Ƃ��̉摜�̃C�[�W���O�p
	};

	//Controller0,1�̑I�����Ă鎞�̏����i�[
	map<int, selectPictInfo> selectPict_;

public:

	//�R���X�g���N�^
	CharaSelectSceneUI(GameObject* parent);

	//�f�X�g���N�^
	~CharaSelectSceneUI() {};

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	/// <summary>
	/// �g�����X�t�H�[���ݒ�
	/// </summary>
	/// <param name="t">�ݒ肵�����g�����X�t�H�[��</param>
	/// <param name="numController">�R���g���[���[�ԍ�</param>
	void SetSelectPictTransform(const Transform& t, int numController);

	/// <summary>
	/// �e�R���g���[���[�̑I���摜�̃g�����X�t�H�[�����擾
	/// </summary>
	/// <param name="numController">�R���g���[���[�ԍ�</param>
	/// <returns>�g�����X�t�H�[��</returns>
	Transform* GetSelectPictTrasnform(int numController) { return selectPict_[numController].transform_.get(); }

	/// <summary>
	/// �C�[�W���O���Z�b�g
	/// </summary>
	/// <param name="t">�ړ���̃|�W�V����</param>
	/// <param name="numController">�R���g���[���[�ԍ�</param>
	void ResetEasing(const XMFLOAT3& t,int numController);

	/// <summary>
	/// �C�[�W���O�N���X���擾
	/// </summary>
	/// <param name="numController">�R���g���[���[�ԍ�</param>
	/// <returns>�C�[�W���O�N���X</returns>
	EasingMove& GetEasing(int numController) { return *selectPict_[numController].easingSelectPict_; };

	/// <summary>
	/// �L�����摜�̕\���ʒu
	/// </summary>
	/// <returns>�\���ʒu</returns>
	XMFLOAT3 GetCharaPictPos(int numController);

	/// <summary>
	/// OK�������ǂ����ݒ肷��
	/// </summary>
	/// <param name="flag">true�Ȃ�OK</param>
	void SetIsOK(bool flag, int numController) { selectPict_[numController].isOK_ = flag; }

	/// <summary>
	/// OK�������ǂ����擾����
	/// </summary>
	/// <returns>true�Ȃ�OK���Ă���</returns>
	bool IsOK(int numController) { return selectPict_[numController].isOK_; }
};

