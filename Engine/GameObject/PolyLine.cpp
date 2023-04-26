#include "../ResourceManager/Global.h"
#include "Camera.h"
#include "PolyLine.h"
#include "../DirectX/Direct3D.h"
#include <vector>


PolyLine::PolyLine() :
	width_(1.0f),	   //����
	length_(400),	   //�����i�����܂ňʒu���L�����鐔�ŁA���ۂ̒����͈ړ����x�ɂ���ĕς��j
	alpha_(1.0f),      //�����x (�ŏ��͓����ɂ��Ȃ��ł���)
	moveAlpha_(false), //���X�ɓ����ɂ��Ă�
	color_(1,1,1),     //�F

	pVertexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr)
{
}

void PolyLine::AddPosition(XMFLOAT3 pos)
{
	//���X�g�̐擪�Ɍ��݈ʒu��ǉ�
	positions_.push_front(pos);

	//�w��̒����𒴂��Ă���I�[�̃f�[�^���폜
	if (positions_.size() > length_)
	{
		positions_.pop_back();
	}

	//���_�o�b�t�@���N���A�i�������邩��j
	SAFE_RELEASE(pVertexBuffer_);


	//���݂̃J�����̈ʒu���x�N�g���Ƃ��Ď擾
	XMFLOAT3 camPos = Camera::GetPosition();
	XMVECTOR vCamPos = XMLoadFloat3(&camPos);

	//���_�f�[�^����邽�߂̔z�������
	VERTEX* vertices = new VERTEX[length_ * 2];

	//���_�f�[�^�����
	int index = 0;
	auto itr = positions_.begin();
	for (int i = 0; i < length_; i++)
	{
		//�L�����Ă��ʒu
		XMVECTOR vPos = XMLoadFloat3(&(*itr));

		itr++;
		if (itr == positions_.end())	break;

		//�L�����Ă��ʒu����A���̎��ɋL�����Ă��ʒu�Ɍ������x�N�g��
		XMVECTOR vLine = XMLoadFloat3(&(*itr)) - vPos;

		//�����ƃ��C���ɐ����ȃx�N�g��
		XMVECTOR vArm = XMVector3Cross(vLine, vCamPos);
		vArm = XMVector3Normalize(vArm) * width_;


		//���_�������Ă���
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, vPos + vArm);
		VERTEX vertex1 = { pos, XMFLOAT3((float)i / length_, 0, 0) };

		XMStoreFloat3(&pos, vPos - vArm);
		VERTEX vertex2 = { pos, XMFLOAT3((float)i / length_, 1, 0) };

		int s = sizeof(VERTEX);

		vertices[index] = vertex1;
		index++;
		vertices[index] = vertex2;
		index++;
	}

	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * length_ * 2;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);


	delete[] vertices;
}

HRESULT PolyLine::Load(std::string fileName)
{
	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);


	//�e�N�X�`��
	pTexture_ = new Texture;
	pTexture_->Load(fileName.c_str());

	return S_OK;
}

void PolyLine::Draw()
{
	Direct3D::SetShader(Direct3D::SHADER_BILLBOARD);
	Direct3D::SetBlendMode(Direct3D::BLEND_ADD);

	if (moveAlpha_)
		alpha_ -= 0.005f;

	//�R���X�^���g�o�b�t�@�ɓn�����
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.color = XMFLOAT4(color_.x, color_.y, color_.z, alpha_);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ



	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);



	//�R���X�^���g�o�b�t�@
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p


	//���_�f�[�^�̕��ѕ����w��
	Direct3D::pContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�`��i�C���f�b�N�X�o�b�t�@����Ȃ��^�C�v�j
	Direct3D::pContext_->Draw((UINT)(positions_.size() - 1) * 2, (UINT)0);

	//���_�f�[�^�̕��ѕ����w���߂�
	Direct3D::pContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);
}

void PolyLine::Release()
{
	SAFE_DELETE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
	positions_.clear();
}