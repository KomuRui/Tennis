#pragma once
#include "../../Base/NormalObject.h"
#include  "../../Engine/GameObject/PolyLine.h"
#include "../../Engine/Component/Collider/SphereCollider.h"
#include <map>

//�������̌v�Z
//https://juken-philo.com/hobutsuundo/

//�{�[���̏��
enum class BallStatus
{
	PURPOSE_MOVE,   //�ړI�n�܂ňړ�
	BOUND_MOVE,     //�o�E���h�ړ�
	PLAYER_HAV_BALL,//�v���C���[���{�[���������Ă�����
	STOP            //��~
};

//�{�[�����
struct BallInfo
{
	BallStatus ballStatus_;      //�{�[���̏��

	int hTime_;                  //�^�C�}�[�n���h��
	int boundCount_;             //�o�E���h�̉�
	float ratio_;			     //����(�n�_����I�_�̂ǂ��̊����ɂ��邩)
	float moveTime_;			 //�n�_����I�_�܂œ�������
	float firstAngle_;           //�������̍ŏ��̊p�x
	bool isGoToBasePoint_;       //�v���C���[�̊�_�Ɍ�������
	bool isTossUp_;              //�g�X�A�b�v���������ǂ���

	string hLandEffectName_;     //���n�G�t�F�N�g�n���h��
	string hDropEffectName_;     //���G�t�F�N�g�n���h��
	string dropEffectFilePath_;  //���G�t�F�N�g�̃t�@�C���p�X

	XMVECTOR endPointDirection_; //�I�_�܂ł̃x�N�g��
	XMVECTOR progressVector_;    //�i�s�x�N�g��
	XMVECTOR tossUpVector_;      //�g�X�A�b�v���鎞�̃x�N�g��
	XMFLOAT2 strength_;          //����(X��Y������)
	XMFLOAT2 v0_;		         //�����x(X��Y������)
	XMFLOAT3 startPoint_;        //�{�[���̎n�_
	XMFLOAT3 endPoint_;          //�{�[���̏I�_

	PolyLine* pLine_;            //�{�[���̋O�Օ`��p
};

/// <summary>
/// �e�j�X�{�[��
/// </summary>
class Ball : public NormalObject
{
	//�{�[���̏��
	BallInfo ballInfo_;
	
	//�����蔻��
	SphereCollider* sphere_;     //���^�̓����蔻��

	//�e
	int hShadowModel_;           //�e�̃��f��
	Transform tShadow_;          //�e�̃g�����X�t�H�[��	

public:

	//�R���X�g���N�^
	Ball(GameObject* parent, std::string modelPath, std::string name);
	Ball(GameObject* parent);

	//�f�X�g���N�^
	~Ball() {};

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//�`��
	void ChildDraw() override;

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;
	
	//////////////////////////////////�֐�///////////////////////////////////////

	/// <summary>
	/// �ړI�n�܂ňړ�
	/// </summary>
	void MoveToPurpose();

	/// <summary>
	/// �o�E���h�ړ�
	/// </summary>
	void BoundMove();

	/// <summary>
	/// �v���C���[���{�[���������Ă����Ԃ̎��ɌĂԊ֐�
	/// </summary>
	void PlayerHavingBall();

	/// <summary>
	/// ��~��Ԃ̎��ɌĂԊ֐�
	/// </summary>
	void Stop() {};

	/// <summary>
	/// ���Z�b�g(�n�_�I�_���ׂčĐݒ�)
	/// </summary>
	void Reset(float strengthX, float strengthY,float moveTime,string basePpointName);

	/// <summary>
	/// �I�_�̃|�W�V�������擾
	/// </summary>
	/// <returns>�I�_�̃|�W�V����</returns>
	XMFLOAT3 GetEndPosition() { return ballInfo_.endPoint_; }

	/// <summary>
	/// �{�[���̋O�ՐF��ݒ�
	/// </summary>
	/// <param name="color">�ݒ肵�����O�ՐF</param>
	void SetBallLineColor(XMFLOAT4 color) { ballInfo_.pLine_->SetColor(color); }

	/// <summary>
	/// �{�[���̎��G�t�F�N�g�̃t�@�C���p�X��ݒ�
	/// </summary>
	void SetBallDropEffectFilePath(string file) { ballInfo_.dropEffectFilePath_ = file; }
	
	/// <summary>
	///�g�X�A�b�v�����Ă��邩�ݒ�
	/// </summary>
	/// <param name="flag">true�Ȃ炵�Ă���</param>
	void SetTossUp(bool flag) { ballInfo_.isTossUp_ = flag; }

	/// <summary>
	/// �v���C���[�̊�_�Ɍ������Ă��邩
	/// </summary>
	bool isGoToPlayerBasePoint() { return ballInfo_.isGoToBasePoint_; }

	/// <summary>
	/// �g�X�A�b�v�����ǂ����擾
	/// </summary>
	/// <returns>true�Ȃ�g�X�A�b�v��</returns>
	bool isTossUp() { return ballInfo_.isTossUp_; }

	/// <summary>
	/// �{�[���̏�Ԃ��擾
	/// </summary>
	/// <returns>�{�[���̏��</returns>
	BallStatus GetBallStatus() { return ballInfo_.ballStatus_; }

	/// <summary>
	/// �w�肵��Z�ʒu��ʉ߂���Ƃ��̃{�[���̈ʒu���擾
	/// </summary>
	/// <returns>�{�[���̏��</returns>
	XMFLOAT3 GetSpecifyPosZBallPosition(float zPos);
};

