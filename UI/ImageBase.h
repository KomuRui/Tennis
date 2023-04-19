#pragma once
#include "../Engine/GameObject/GameObject.h"

/// <summary>
/// �摜��\����������N���X
/// </summary>
class ImageBase : public GameObject
{
protected:

	int hPict_;                   //�摜�ԍ�
	std::string ModelNamePath_;   //�t�@�C���l�[���p�X

public:

	//�R���X�g���N�^
	ImageBase(GameObject* parent, std::string modelPath, std::string name);

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	///////////////////�p����p�֐�/////////////////////

	/// <summary>
	/// �p����p�̏�����
	/// </summary>
	virtual void ChildInitialize() {};

	/// <summary>
	/// �p����p�̃X�^�[�g�A�b�v�f�[�g
	/// </summary>
	virtual void ChildStartUpdate() {};

	/// <summary>
	/// �p���悲�Ƃ�Update�ł̓�������ς���
	/// </summary>
	virtual void ChildUpdate() {};

	/// <summary>
	/// �p����p�̕`��
	/// </summary>
	virtual void ChildDraw() {};
};

