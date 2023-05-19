#pragma once
#include "../../Base/NormalObject.h"
#include <map>

//����
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

	map<Type, XMFLOAT4> lineColor_;     //���킲�Ƃ̃��C���F
	map<Type, string> effectFilePath_;  //���킲�Ƃ̃t�@�C���p�X
	Type type_;						    //����
	XMFLOAT3 colliderPos_;              //�R���C�_�[�̃|�W�V����

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

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	/// <summary>
	/// �^��ݒ�
	/// </summary>
	/// <param name="t">�ݒ肵�����^</param>
	void SetType(Type t) { type_ = t; }
};

