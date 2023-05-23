#pragma once
#include "../../Stage.h"
#include "../../Player/PlayerBase.h"
#include "../../Manager/SceneManager/SceneManager.h"

//��ʑ���
enum class Players
{
	ONE, //��l�v���C
	TWO, //��l�v���C
	MAX
};

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
	/// Player�����S��������LifeManager����Ă΂��
	/// </summary>
	void PlayerDie();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��(�R�C���̎擾����Player���C�t�̕\��)
	/// </summary>
	void Draw();

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

	//�v���C���[�l���̐ݒ�
	void SetPlayers(Players s);

	//�v���C���[�l���̎擾
	Players GetPlayers();

};

