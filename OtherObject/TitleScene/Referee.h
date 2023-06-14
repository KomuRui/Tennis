#pragma once
#include "Score.h"
#include "../../Player/PlayerBase.h"

//�������
enum class GameStatus
{
	NOW_RALLY,         //�����[��
	NOW_SERVE_RECEIVE  //�T�[�u���V�[�u
};

//�e�T�C�h
enum class Side {
	DEUCE_SIDE,        //�f���[�X�T�C�h
	AD_SIDE            //�A�h�T�C�h
};

/// <summary>
/// �R��
/// </summary>
class Referee
{
	Score* score_;	       //�X�R�A
	GameStatus status_;    //�������
	Side side_;            //�T�C�h��

	PlayerBase* server_;   //�T�[�o�[
	PlayerBase* receiver_; //���V�[�o�[

	//�T�[�o�[�̓�����͈�
	map<pair<TennisCourtName, Side>, pair<float, float>> serverMoveRange_;

	//�T�[�o�[�E���V�[�o�[�̏����ʒu
	map<pair<TennisCourtName, Side>, pair<XMFLOAT3,XMFLOAT3>> serverInitialPosition_;
	map<pair<TennisCourtName, Side>, pair<XMFLOAT3,XMFLOAT3>> receiverInitialPosition_;

public:

	//�R���X�g���N�^
	Referee();
	
	//�f�X�g���N�^
	~Referee() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �|�C���g�I����
	/// </summary>
	/// <param name="n">�_���������e�j�X�R�[�g�̖��O</param>
	void EndPoint(TennisCourtName n);

	/// <summary>
	/// �ǂ��炩���|�C���g�擾��
	/// </summary>
	void GetPoint();

	/// <summary>
	/// �ǂ��炩���Q�[���擾��
	/// </summary>
	void GetGame();

	/// <summary>
	/// �����I����
	/// </summary>
	void GameMatch();

	/// <summary>
	/// �T�C�h�`�F���W
	/// </summary>
	void ChangeSide();

	/// <summary>
	/// �T�C�h���Z�b�g
	/// </summary>
	void SideReset() { side_ = Side::DEUCE_SIDE; }

	/////////////////////////////�Q�b�^�[�E�Z�b�^�[////////////////////////////////////

	/// <summary>
	/// ������Ԃ��擾
	/// </summary>
	/// <returns>�������</returns>
	GameStatus GetGameStatus() { return status_; }

	/// <summary>
	/// ������Ԃ�ݒ�
	/// </summary>
	/// <param name="s">�ݒ肵�����������</param>
	void SetGameStatus(GameStatus s) { status_ = s; }

	/// <summary>
	/// �v���C���[���T�[�o�[���ǂ���
	/// </summary>
	/// <returns>true�Ȃ�T�[�o�[</returns>
	bool IsServer(PlayerBase* p) { return (server_ == p); }

	/// <summary>
	/// �T�[�o�[�̃v���C���[���擾
	/// </summary>
	/// <returns>�T�[�o�[�̃v���C���[</returns>
	PlayerBase* GetServer() { return server_; }

	/// <summary>
	/// ���V�[�o�[�̃v���C���[���擾
	/// </summary>
	/// <returns>���V�[�o�[�̃v���C���[</returns>
	PlayerBase* GetReceiver() { return receiver_; }

	/// <summary>
	/// �T�[�o�[���Z�b�g
	/// </summary>
	/// <param name="p">�v���C���[</param>
	void SetServer(PlayerBase* p) { server_ = p; }
	
	/// <summary>
	/// ���V�[�o�[���Z�b�g
	/// </summary>
	/// <param name="p">�v���C���[</param>
	void SetReceiver(PlayerBase* p) { receiver_ = p; }

	/// <summary>
	/// �T�C�h���擾
	/// </summary>
	/// <returns>�T�C�h</returns>
	Side GetSide() { return side_; }

	/// <summary>
	/// �T�[�o�[�̓�����͈͂��擾
	/// </summary>
	/// <returns>X���ł̓�����ŏ��l�ƍő�l</returns>
	pair<float, float> GetServerMoveRange() { return serverMoveRange_[{server_->GetTennisCourtName(), side_}]; }

	/// <summary>
	/// ���V�[�o�[�̃|�W�V�������擾
	/// </summary>
	/// <returns>���V�[�o�[�̃|�W�V����</returns>
	XMFLOAT3 GetReceiverPosition() { return receiverInitialPosition_[{receiver_->GetTennisCourtName(), side_}].first; }

	/// <summary>
	/// �T�[�o�[�̃|�W�V�������擾
	/// </summary>
	/// <returns>�T�[�o�[�̃|�W�V����</returns>
	XMFLOAT3 GetServerPosition() { return serverInitialPosition_[{server_->GetTennisCourtName(), side_}].first; }
};

