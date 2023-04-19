#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public GameObject
{
	int hModel_; 	       //���f���ԍ��i�[�p

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//�f�X�g���N�^
	~TitleScene();

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};

