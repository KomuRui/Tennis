#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/HermiteSplineMove.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public GameObject
{

	//�G���~�[�g�X�v���C�����g���ăJ�����𓮂���(�A�����ē�����ύX�������̂�vector�ɂ��Ă���)
	vector<pair<std::unique_ptr<HermiteSplineMove>, std::unique_ptr<HermiteSplineMove>>> hermiteMoveTable_;

	//���݌��Ă���ԍ�
	int nowLookNum_;

public:

	//�R���X�g���N�^
	TitleScene(GameObject* parent);

	//�f�X�g���N�^
	~TitleScene();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	/// <summary>
	/// �J�����̓���
	/// </summary>
	void CameraMove();

	/// <summary>
	/// �f�[�^�Z�b�g
	/// </summary>
	void SetData(string posFileName,string tarFileName);

};

