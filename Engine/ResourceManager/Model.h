#pragma once
#include <DirectXMath.h>
#include <assert.h>
#include <vector>
#include <string>
#include "../DirectX/Fbx.h"
#include "../GameObject/Transform.h"
#include "Global.h"
#include "../GameObject/GameObject.h"

//�O��`
class Block;

//-----------------------------------------------------------
//3D���f���iFBX�t�@�C���j���Ǘ�����
//-----------------------------------------------------------
namespace Model
{
	//���f�����
	struct ModelData
	{
		//�t�@�C����
		std::string fileName;

		//���C�ŏ�Q���Ɠ�����������m�肽���̂ŗp�ӂ��Ă���
		GameObject* pObstacle;

		//���C�Ńu���b�N�ɓ��������������������̂ŗp�ӂ��Ă���
		Block* pBlock;

		//���[�h�������f���f�[�^�̃A�h���X
		Fbx* pFbx;

		//�ǂ̃V�F�[�_���g����
		Direct3D::SHADER_TYPE  shaderType;

		//�s��
		Transform 	transform;

		//�A���t�@
		float		alpha;

		//�A���r�G���g
		XMFLOAT4    ambient;

		//�X�y�L�����[
		XMFLOAT4    speculer;

		//�A�E�g���C����\�����鎞�̐F
		XMFLOAT4    outLineColor;

		//���邳
		float brightness;

		//uv�X�N���[���̒l
		float uvScroll;

		//���C�̓����蔻���t���邩
		bool isRay;

		//�A�E�g���C���`�悷�邩
		bool isOutLineDraw;

		//�A�j���[�V�����Đ����邩
		bool isAnim;

		//�A�j���[�V�����̃t���[��
		float nowFrame, animSpeed;
		int startFrame, endFrame;


		//������
		ModelData() : pFbx(nullptr), isRay(false), nowFrame(ZERO), startFrame((int)ZERO), endFrame((int)ZERO), animSpeed(ZERO), shaderType(Direct3D::SHADER_3D), outLineColor(ZERO, ZERO, ZERO, 1.0f),
			alpha(1), ambient(ZERO, ZERO, ZERO, ZERO), isAnim(false), speculer(ZERO, ZERO, ZERO, ZERO), brightness(ZERO), pBlock(nullptr), pObstacle(nullptr), uvScroll(ZERO), isOutLineDraw(false)
		{
		}

		//�A�j���[�V�����̃t���[�������Z�b�g
		//�����FstartFrame	�J�n�t���[��
		//�����FendFrame	�I���t���[��
		//�����FanimSpeed	�A�j���[�V�������x
		void SetAnimFrame(int start, int end, float speed)
		{
			nowFrame = (float)start;
			startFrame = start;
			endFrame = end;
			animSpeed = speed;
		}
	};


	//������
	void Initialize();

	//���f�������[�h
	//�����FfileName�@�t�@�C����
	//�ߒl�F���̃��f���f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(std::string fileName);

	//�`��
	//�����Fhandle	�`�悵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void Draw(int handle);

	//�C�ӂ̃��f�����J��
	//�����Fhandle	�J�����������f���̔ԍ�
	void Release(int handle);

	//�S�Ẵ��f�������
	//�i�V�[�����؂�ւ��Ƃ��͕K�����s�j
	void AllRelease();

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetAlpha(int handle, float Alpha);

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetAmbient(int handle, XMFLOAT4 ambt = { ZERO,ZERO,ZERO,ZERO });

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetSpeculer(int handle, XMFLOAT4 Speculer = { ZERO,ZERO,ZERO,ZERO });

	/// <summary>
	/// �A�E�g���C���̐F���Z�b�g
	/// </summary>
	/// <param name="handle">���f���ԍ�</param>
	/// <param name="OutLine">�ݒ肵�����A�E�g���C���̐F</param>
	void SetOutLineColor(int handle, XMFLOAT4 OutLine = { ZERO,ZERO,ZERO,1.0f });

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetBrightness(int handle, float Brightness = ZERO);

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetRayFlag(int handle, bool flag);

	/// <summary>
	/// �A�E�g���C����`�悷�邩�Z�b�g
	/// </summary>
	/// <param name="handle">���f���̔ԍ�</param>
	/// <param name="flag">true�Ȃ�`�悷��</param>
	void SetOutLineDrawFlag(int handle, bool flag);

	/// <summary>
	/// �u���b�N�I�u�W�F�̃|�C���^���Z�b�g
	/// </summary>
	/// <param name="handle">���f���ԍ�</param>
	/// <param name="block">�u���b�N�I�u�W�F�̃|�C���^</param>
	void SetBlockObj(int handle, Block* block);

	/// <summary>
	/// ��Q���̃|�C���^���Z�b�g
	/// </summary>
	/// <param name="handle">���f���ԍ�</param>
	/// <param name="block">Obstacle�̃|�C���^</param>
	void SetObstacleObj(int handle, GameObject* Obstacle);

	/// <summary>
	/// �g���V�F�[�_���Z�b�g
	/// </summary>
	/// <param name="type">�g�������V�F�[�_</param>
	void SetShederType(int handle, Direct3D::SHADER_TYPE type);

	/// <summary>
	/// UV�X�N���[���̒l���Z�b�g
	/// </summary>
	/// <param name="handle">���f���ԍ�</param>
	/// <param name="scroll">scroll�̒l</param>
	void SetUvScroll(int handle, float scroll);

	//�A�j���[�V�����̃t���[�������Z�b�g
	//�����Fhandle		�ݒ肵�������f���̔ԍ�
	//�����FstartFrame	�J�n�t���[��
	//�����FendFrame	�I���t���[��
	//�����FanimSpeed	�A�j���[�V�������x
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed);

	//�A�j���[�V�������邩���Ȃ���
	void SetAnimFlag(int handle, bool flag);

	//�A�j���[�V�����̃X�s�[�h���Z�b�g����֐�
	void SetAnimSpeed(int handle, float speed);

	//���݂̃A�j���[�V�����̃t���[�����擾
	int GetAnimFrame(int handle);

	//�C�ӂ̃{�[���̈ʒu���擾
	//�����Fhandle		���ׂ������f���̔ԍ�
	//�����FboneName	���ׂ����{�[���̖��O
	//�ߒl�F�{�[���̈ʒu�i���[���h���W�j
	XMFLOAT3 GetBonePosition(int handle, std::string boneName);

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetTransform(int handle, Transform& transform);

	//���[���h�s��̎擾
	//�����Fhandle	�m�肽�����f���̔ԍ�
	//�ߒl�F���[���h�s��
	XMMATRIX GetMatrix(int handle);


	//���C�L���X�g�i���C���΂��ē����蔻��j
	//�����Fhandle	���肵�������f���̔ԍ�
	//�����Fdata	�K�v�Ȃ��̂��܂Ƃ߂��f�[�^
	void RayCast(int handle, RayCastData* data);

	//��ԋ߂��|���S���̖@���ƃ|�W�V������RayCastData�Ɋi�[
	//�����Fhandle	���肵�������f���̔ԍ�
	//�����Fdata	�K�v�Ȃ��̂��܂Ƃ߂��f�[�^
	void NearPolyNormal(int handle, NearPolyData* data);

	//���C�L���X�g(�����������f���̃A�E�g���C����\��������)
	//�����Fdata	�K�v�Ȃ��̂��܂Ƃ߂��f�[�^
	void RayCastOutLineSet(RayCastData* data, XMFLOAT4 outLineColor = {0,0,0,1});

	//���C�L���X�g(�w�肳�ꂽ�I�u�W�F�N�g�ƃX�e�[�W�Ƃ̓����蔻��)
	//�����Fdata	�K�v�Ȃ��̂��܂Ƃ߂��f�[�^
	void AllRayCast(int handle, RayCastData* data);

};