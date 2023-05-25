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

//�X�g���[�N
enum class Stroke{
	FOREHAND,  //�t�H�A
	BACKHAND,  //�o�b�N
	MAX
};

//�ł��̕K�v�ȏ��
struct HitStrength {
	XMFLOAT2 strength_;   //����(X��Y������)
	float moveTime_;	  //�n�_����I�_�܂œ�������
};

/// <summary>
/// ���P�b�g
/// </summary>
class Racket : public NormalObject
{

	map<Type, XMFLOAT4> lineColor_;         //���킲�Ƃ̃��C���F
	map<Type, string> effectFilePath_;      //���킲�Ƃ̃G�t�F�N�g�̃t�@�C���p�X
	map<Type, HitStrength> hitStrength_;    //���킲�Ƃ̑ł��̋���
	Stroke stroke_;                         //�X�g���[�N
	Type type_;						        //����
	XMFLOAT3 colliderPos_;                  //�R���C�_�[�̃|�W�V����
	float ratio_;                           //�{��

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

	/// <summary>
	/// ���͂ɑ΂����_�̃|�C���g�̖��O���擾
	/// </summary>
	/// <returns></returns>
	string GetInputBasePoint();

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	/// <summary>
	/// �^��ݒ�
	/// </summary>
	/// <param name="t">�ݒ肵�����^</param>
	void SetType(Type t) { type_ = t; }

	/// <summary>
	/// �X�g���[�N��ݒ�
	/// </summary>
	/// <param name="t">�ݒ肵�����X�g���[�N</param>
	void SetStroke(Stroke t) { stroke_ = t; }

	/// <summary>
	/// �{����ݒ�
	/// </summary>
	/// <param name="ratio">�ݒ肵�����{��</param>
	void SetRatio(float ratio) { ratio_ = ratio; }

	/// <summary>
	/// �{�����擾
	/// </summary>
	/// <returns>�{��</returns>
	float GetRatio() { return ratio_; }

	/// <summary>
	/// �����_���ɑł��̋������擾
	/// </summary>
	/// <returns>�ł��̋���</returns>
	HitStrength GetRamdomHitStrength();

	/// <summary>
	/// �^�C�v���Ƃ̐F���擾
	/// </summary>
	/// <returns>�^�C�v���Ƃ̐F</returns>
	XMFLOAT4 GetTypeColor() { return lineColor_[type_]; }
};

