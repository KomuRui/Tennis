#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Component/HermiteSplineMove.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public GameObject
{

	//�G���~�[�g�X�v���C�����g���ăJ�����𓮂���
	std::unique_ptr<HermiteSplineMove> hermiteMoveCamPos_ = std::make_unique<HermiteSplineMove>(); 
	std::unique_ptr<HermiteSplineMove> hermiteMoveCamTar_ = std::make_unique<HermiteSplineMove>(); 

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



};

