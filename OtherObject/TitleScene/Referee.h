#pragma once
#include "Score.h"
#include "../../Player/PlayerBase.h"

//�������
enum class GameStatus
{
	NOW_RALLY,         //�����[��
	NOW_SERVE_RECEIVE  //�T�[�u���V�[�u
};

/// <summary>
/// �R��
/// </summary>
class Referee
{
	Score* score_;	       //�X�R�A
	GameStatus status_;    //�������

	bool isPlayer1Server_; //Player1���T�[�o�[���ǂ���

public:

	//�R���X�g���N�^
	Referee();
	
	//�f�X�g���N�^
	~Referee() {};

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

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
	/// �v���C���[1���T�[�o�[���ǂ����ݒ�
	/// </summary>
	/// <param name="flag"></param>
	void SetPlayer1Server(bool flag) { isPlayer1Server_ = flag; }

	/// <summary>
	/// �v���C���[1���T�[�o�[���ǂ���
	/// </summary>
	/// <returns>true�Ȃ�T�[�o�[</returns>
	bool IsPlayer1Server() { return isPlayer1Server_; }

	/// <summary>
	/// �v���C���[2���T�[�o�[���ǂ���
	/// </summary>
	/// <returns>true�Ȃ�T�[�o�[</returns>
	bool IsPlayer2Server() { return !isPlayer1Server_; }
};

