#pragma once
#include "../GameObject/GameObject.h"
#include "../DirectX/Texture.h"
#include "../DirectX/BillBoard.h"
#include "../GameObject/Light.h"
#include "../Component/Transform/Transform.h"

//�ŔN���X(�|���S���Ƀe�N�X�`�����͂�)
//�`��͔̕��������Ȃ��̂�Mob���p�����Ȃ���GameObject���p������
class Signboard : public GameObject
{
	// ��̒��_�����i�[����\����
	struct VERTEX
	{
		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT3 uv;
	};

	//�y�R���X�^���g�o�b�t�@�[�z
	// GPU(�V�F�[�_��)�֑��鐔�l���܂Ƃ߂��\����
	//Simple3D.hlsl�̃O���[�o���ϐ��ƑΉ�������
	struct CONSTANT_BUFFER
	{
		XMMATRIX worldVewProj; 			     //���[���h�A�r���[�A�v���W�F�N�V�����s��̍����i���_�ϊ��Ɏg�p�j
		XMMATRIX normalTrans;				 //��]�s��Ɗg��s��̋t�s��������������́i�@���̕ό`�Ɏg�p�j
		XMMATRIX world;						 //���[���h�s��
		XMFLOAT4 lightDirection;			 //���C�g�̌���
		XMFLOAT4 cameraPosition;			 //�J�����̈ʒu�i�n�C���C�g�̌v�Z�ɕK�v�j
		XMFLOAT4 lightPosition;				 //���C�g�̈ʒu
		XMFLOAT4 pos[LIGHT_TOTAL_NUM];       //���C�g�̐����̈ʒu
		XMFLOAT4 intensity[LIGHT_TOTAL_NUM]; //���C�g�̐����̋���
		FLOAT    isBrightness;				 //���邳
	};

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	std::string fileName_; //�t�@�C���l�[��
	Texture* pTexture_;	   //�摜

	float polySize_;       //�|���S���̃T�C�Y

	bool isLookCamera_;    //�J�����̕��Ɍ����邩�ǂ���

	Transform *transform_;  //�g�����X�t�H�[��

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Signboard(GameObject* parent, std::string fileName, std::string name);

	//���[�h
	//�����FfileName	�摜�t�@�C����
	//�ߒl�F����/���s
	HRESULT Load();

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////
	
	//������
	void Initialize() override;

	//�X�V
	void Update() override {};

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override {};

	/// <summary>
	/// �J�����̕������邩�ǂ����Z�b�g
	/// </summary>
	/// <param name="flag">������Ȃ�true,�����Ȃ��̂Ȃ�false</param>
	void SetLookCamera(const bool& flag) { isLookCamera_ = flag; }
};

