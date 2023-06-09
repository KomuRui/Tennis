#pragma once
#include "../../Stage.h"
#include "../../Player/PlayerBase.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../OtherObject/TitleScene/Ball.h"


//��ʑ���
enum class Players
{
	ONE, //��l�v���C
	TWO, //��l�v���C
	MAX
};

class Referee;

//�Q�[���̂��낢��ȊǗ�������
namespace GameManager
{
	///////////////////////////////�֐�//////////////////////////////////
	
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �V�[���J�ڂ̎��̏�����
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��(�R�C���̎擾����Player���C�t�̕\��)
	/// </summary>
	void Draw();

	/// <summary>
	/// �v���C���[��ǉ�
	/// </summary>
	/// <param name="p">�v���C���[�̃|�C���^</param>
	void AddPlayer(PlayerBase* p);

	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////

	//�v���C���[�̃|�C���^�Z�b�g
	void SetpPlayer(PlayerBase* player);

	//�v���C���[�̃|�C���^�Q�b�g
	PlayerBase* GetpPlayer();

	//�X�e�[�W�̃|�C���^�Z�b�g
	void SetpStage(Stage* stage);

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GetpStage();

	//�V�[���}�l�[�W���[�̃|�C���^�Z�b�g
	void SetpSceneManager(SceneManager* scene);

	//�V�[���}�l�[�W���[�̃|�C���^�Q�b�g
	SceneManager* GetpSceneManager();

	//�{�[���̃|�C���^�Z�b�g
	void SetpBall(Ball* ball);

	//�{�[���̃|�C���^�Q�b�g
	Ball* GetpBall();

	//�v���C���[�l���̐ݒ�
	void SetPlayers(Players s);

	//�v���C���[�l���̎擾
	Players GetPlayers();

	/// <summary>
	/// �v���C���[�Z�b�g
	/// </summary>
	/// <returns>�v���C���[�ԍ�</returns>
	int  SetPlayer(PlayerBase* p);

	/// <summary>
	/// �R���擾
	/// </summary>
	/// <returns>�R��</returns>
	Referee* GetReferee();

	/// <summary>
	/// �����̃v���C���[�ȊO�̃v���C���[���擾
	/// </summary>
	/// <param name="p">�v���C���[</param>
	/// <returns>�v���C���[���擾</returns>
	PlayerBase* GetNotMyPlayer(PlayerBase* p);

};

