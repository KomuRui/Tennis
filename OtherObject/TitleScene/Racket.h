#pragma once
#include "../../Base/NormalObject.h"

//�{�[����ł��̋�
enum class Type {
	FLAT,      //�t���b�g
	TOP_SPIN,  //�g�b�v�X�s��
	SLICE,     //�X���C�X
	LOB,       //���u
	MAX
};

/// <summary>
/// ���P�b�g
/// </summary>
class Racket : public NormalObject
{

	//�{�[����ł��̋�
	Type type_;

public:

	//�R���X�g���N�^
	Racket(GameObject* parent, std::string modelPath, std::string name);
	Racket(GameObject* parent);

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

	//�f�X�g���N�^
	~Racket() {};
};

