#pragma once
#include <list>
#include "../DirectX/Direct3D.h"
#include "../DirectX/Texture.h"
#include <DirectXMath.h>
#include <string>
#include "../DirectX/BillBoard.h"

using namespace DirectX;
using namespace std;

class PolyLine
{
	float width_;		//����
	int length_;		//����

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;	            //�摜


	list<XMFLOAT3> positions_;	    //�ߋ�length_�񕪂̈ʒu

	XMFLOAT3 color_;                //�F
	float alpha_;                   //�����x
	bool  moveAlpha_;               //���X�ɓ����ɂ��Ă���

public:
	//�R���X�g���N�^
	PolyLine();


	//���݂̈ʒu���L��������
	//�����Fpos	���݂̈ʒu
	void AddPosition(XMFLOAT3 pos);

	//���[�h
	//�����FfileName	�摜�t�@�C����
	//�ߒl�F����/���s
	HRESULT Load(std::string fileName);

	//�`��
	void Draw();

	//���X�ɓ����ɂȂ�悤�ɐݒ�
	void SetMoveAlphaFlag() { moveAlpha_ = true; }

	//���
	void Release();

	/// <summary>
	/// �F�Z�b�g
	/// </summary>
	void SetColor(XMFLOAT3 color) { color_ = color; }

	/// <summary>
	/// �����Z�b�g
	/// </summary>
	/// <param name="len">�Z�b�g����������</param>
	void SetLengh(int len) { length_ = len; }

	/// <summary>
	/// �����Z�b�g
	/// </summary>
	/// <param name="width">�Z�b�g����������</param>
	void SetWidth(float width) { width_ = width; }
};

