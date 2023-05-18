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

	//�f�X�g���N�^
	~Racket() {};

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

	/// <summary>
	/// �^��ݒ�
	/// </summary>
	/// <param name="t">�ݒ肵�����^</param>
	void SetType(Type t) { type_ = t; }
};

