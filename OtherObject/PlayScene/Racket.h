#pragma once
#include "../../Base/NormalObject.h"
#include "../../Engine/Component/Collider/BoxCollider.h"
#include "TennisCourt.h"
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
	BoxCollider* box1_;                     //���^�̓����蔻��
	map<Type, XMFLOAT4> lineColor_;         //���킲�Ƃ̃��C���F
	map<Type, string> hitEffectFilePath_;   //���킲�Ƃ̃q�b�g�G�t�F�N�g�̃t�@�C���p�X
	map<Type, string> dropEffectFilePath_;  //���킲�Ƃ̎��G�t�F�N�g�̃t�@�C���p�X
	map<Type, HitStrength> hitStrength_;    //���킲�Ƃ̑ł��̋���
	Stroke stroke_;                         //�X�g���[�N
	Type type_;						        //����
	XMFLOAT3 colliderPos_;                  //�R���C�_�[�̃|�W�V����
	float ratio_;                           //�{��
	TennisCourtName goTennisCourtName_;     //�ǂ̃e�j�X�R�[�g�Ɍ������đł�

public:

	//�R���X�g���N�^
	Racket(GameObject* parent, std::string modelPath, std::string name);
	Racket(GameObject* parent);

	//�f�X�g���N�^
	~Racket();

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//�����蔻��
	void HitColliderFunc(GameObject* pTarget);

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
