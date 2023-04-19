#pragma once
#include "../GameObject/Transform.h"
#include "../GameObject/GameObject.h"
#include <vector>

//�e�X�e�[�W�ŃJ�����J�ڂ���Ƃ��̕K�v�ȏ��
struct StageCameraTransition
{
	XMFLOAT3 CameraPosition;  //�J�����̃|�W�V����
	XMFLOAT3 CameraTarget;    //�J�����̃^�[�Q�b�g
	XMFLOAT3 CollisionSize;   //�R���C�_�[�̃T�C�Y
};

//�e�V�[���̃X�e�[�W����Ă����
class CreateStage
{
	//�X�e�[�W�쐬�ɕK�v�ȏ��
	struct CreateStageInfo
	{
		GameObject* parent;         //�e�I�u�W�F�N�g
		std::string ModelPathName;  //���f���p�X�l�[��
		std::string inName;         //�I�u�W�F�N�g�̖��O
		Transform   t;              //�g�����X�t�H�[��
		XMFLOAT3    camPos;         //�J�����̃|�W�V����(�K�v�ȃI�u�W�F�N�g�ƕK�v����Ȃ��I�u�W�F�N�g������)
	};

	//���郉�C�g�̃R���g���[���[����x�������Ȃ��̂�flag�ō�������ǂ����m�F����
	bool createShineController_;

	//�t�@�C�����[�h���ē�������ۑ����Ă���(LoadFile�Ƃ����֐��Ŏg��)
	//�D���ȃ^�C�~���O�ŃX�e�[�W����ł���悤��
	std::vector<CreateStageInfo> info_;

	//�쐬�����X�e�[�W�̃I�u�W�F�N�g�S�ĕۑ����Ă���
	std::vector<GameObject*> createStageAllObject_;

public:

	//�R���X�g���N�^
	CreateStage();

	//�I�u�W�F�N�g�쐬
	void CreateObject(GameObject* parent,std::string ModelPathName, std::string inName, Transform t, XMFLOAT3 camPos);

	/// <summary>
	/// �e�X�e�[�W�̃t�@�C�����[�h���X�e�[�W���쐬���Ă����
	/// </summary>
	/// <param name="parent">�쐬����X�e�[�W�̐e�I�u�W�F�N�g</param>
	/// <param name="filename">���[�h�������t�@�C��</param>
	void LoadFileCreateStage(GameObject* parent, std::string filename);

	/// <summary>
	/// �e�X�e�[�W�̃t�@�C�����[�h�������Ă���� 
	/// </summary>
	/// <param name="parent">�쐬����X�e�[�W�̐e�I�u�W�F�N�g</param>
	/// <param name="filename">���[�h�������t�@�C��</param>
	void LoadFile(GameObject* parent, std::string filename);

	/// <summary>
	/// LoadFile���g���ă��[�h�����t�@�C�������ɃX�e�[�W���쐬
	/// </summary>
	void LoadFileBasedCreateStage();

	/// <summary>
	/// �쐬�����X�e�[�W�����ׂč폜
	/// </summary>
	void AllCreateStageDelete(bool isKillPlayer = true);

	/// <summary>
	/// �쐬�����X�e�[�W���ׂĕ`��ƍX�V���Ȃ��悤��
	/// </summary>
	void AllCreateStageInvisibleAndLeave();

	/// <summary>
	/// �쐬�����X�e�[�W���ׂĕ`��ƍX�V����悤��
	/// </summary>
	void AllCreateStageVisibleAndEnter();

	/// <summary>
	/// �쐬�����S�ẴX�e�[�W���X�V����
	/// </summary>
	void AllCreateStageUpdate();

	/// <summary>
	/// �쐬�����S�ẴX�e�[�W��`�悷��
	/// </summary>
	void AllCreateStageDraw();

	/// <summary>
	/// ���ʌ^�̐���(�摜��Mob���p�����Ă��Ȃ��Q�[���I�u�W�F�N�g)
	/// </summary>
	/// <typeparam name="T">�����������N���X�̖��O</typeparam>
	/// <param name="pParent">�e</param>
	template <class T>
	T* InstantiateNormal(GameObject* pParent,std::string modelPath,std::string name, Transform t);

	//���ʌ^�̐���(���O�ƃ��f���p�X�w�肵�Ȃ�)
	template <class T>
	T* InstantiateNormal(GameObject* pParent,Transform t);

	//Mob���p������3D�I�u�W�F����
	template <class T>
	T* InstantiateMob3D(GameObject* pParent, std::string modelPath, std::string name, Transform t);

	//�{�^���̐���
	template <class T>
	T* InstantiateButton(GameObject* pParent, std::string modelPath, std::string name, Transform t);

	//���̐���
	template <class T>
	T* InstantiatePlanet(GameObject* pParent, std::string modelPath, std::string name, Transform t);
};
