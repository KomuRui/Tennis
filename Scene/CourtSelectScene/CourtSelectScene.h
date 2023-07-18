#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/HermiteSplineMove.h"

/// <summary>
/// �e�j�X�R�[�g�I���V�[��
/// </summary>
class CourtSelectScene : public GameObject
{

	//�G���~�[�g�X�v���C�����g���ăJ�����𓮂���(�A�����ē�����ύX�������̂�vector�ɂ��Ă���)
	vector<pair<std::unique_ptr<HermiteSplineMove>, std::unique_ptr<HermiteSplineMove>>> hermiteMoveTable_;

	//���݌��Ă���ԍ�
	int nowLookNum_;

public:

	//�R���X�g���N�^
	CourtSelectScene(GameObject* parent);

	//�f�X�g���N�^
	~CourtSelectScene();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	/// <summary>
	/// �J�����̓���
	/// </summary>
	void CameraMove();

	/// <summary>
	/// �J�������X�^�[�g
	/// </summary>
	void CameraReStart();

	/// <summary>
	/// �f�[�^�Z�b�g
	/// </summary>
	void SetData(string posFileName, string tarFileName);

};

