#include "Signboard.h"
#include "../GameObject/Camera.h"
#include "../GameObject/Light.h"
#include "../GUI/ImGuiSet.h"

//�萔
namespace
{
	static int ROTATION_ANGLE_Y = 180; //Y���̉�]�p�x
}

//�R���X�g���N�^
Signboard::Signboard(GameObject* parent,std::string fileName,std::string name)
    :GameObject(parent, name),
	pVertexBuffer_(nullptr),pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr), polySize_(5.0f), fileName_(fileName), isLookCamera_(false)
{
}

//�摜�����[�h���ă|���S�����쐬
HRESULT Signboard::Load()
{
	HRESULT hr;

	// ���_���
	VERTEX vertices[] =
	{
		{ XMFLOAT3(-5.0f,  5.0f, 0.0f),XMFLOAT3(0.0f, 0.0f, 1.0f),XMFLOAT3(0.0f, 0.0f, 0.0f) },   // �l�p�`�̒��_�i����j
		{ XMFLOAT3(5.0f,  5.0f, 0.0f),XMFLOAT3(0.0f, 0.0f, 1.0f),XMFLOAT3(1.0f, 0.0f, 0.0f) },   // �l�p�`�̒��_�i�E��j
		{ XMFLOAT3(5.0f, -5.0f, 0.0f),XMFLOAT3(0.0f, 0.0f, 1.0f),XMFLOAT3(1.0f, 1.0f, 0.0f) },   // �l�p�`�̒��_�i�E���j
		{ XMFLOAT3(-5.0f, -5.0f, 0.0f),XMFLOAT3(0.0f, 0.0f, 1.0f),XMFLOAT3(0.0f, 1.0f, 0.0f) },   // �l�p�`�̒��_�i�����j
	};

	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		return hr;
	}

	//�C���f�b�N�X���
	int index[] = { 0,1,2,0,2,3 };

	// �C���f�b�N�X�o�b�t�@�𐶐�����
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		return hr;
	}

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
	pTexture_->Load(fileName_.c_str());
	ARGUMENT_INITIALIZE(pathName_, fileName_);

	return S_OK;
}

//������
void Signboard::Initialize()
{
	//�摜���[�h�|���S���쐬
	Load();

	transform_ = AddComponent<Transform>();
}

//�`��
void Signboard::Draw()
{
	//�V�F�[�_���Z�b�g
	Direct3D::SetShader(Direct3D::SHADER_SIGNBOARD);
	Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);

	XMMATRIX matWorld;
	XMMATRIX matTrans = XMMatrixTranslation(transform_->position_.x, transform_->position_.y, transform_->position_.z);
	XMMATRIX matRotate = XMMatrixRotationX(XMConvertToRadians(transform_->rotate_.x)) * XMMatrixRotationY(XMConvertToRadians(transform_->rotate_.y)) * XMMatrixRotationZ(XMConvertToRadians(transform_->rotate_.z));
	XMMATRIX matScale = XMMatrixScaling(transform_->scale_.x, transform_->scale_.y, 1.0f);

	//�����J�����̕�������Ȃ�
	if(isLookCamera_)
		matWorld = matScale * Camera::GetBillboardMatrix() * matTrans;
	else
		matWorld = matScale * matRotate * matTrans;

	// �p�����[�^�̎󂯓n��
	CONSTANT_BUFFER cb;
	cb.worldVewProj = XMMatrixTranspose(matWorld * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());						// ���\�[�X�֑���l���Z�b�g
	cb.world = XMMatrixTranspose(matWorld);

	//�����J�����̕�������Ȃ�
	if (isLookCamera_)
		cb.normalTrans = XMMatrixTranspose(Camera::GetBillboardMatrix() * XMMatrixInverse(nullptr, Camera::GetBillboardMatrix()));
	else
		cb.normalTrans = XMMatrixTranspose(matRotate * XMMatrixInverse(nullptr, matRotate));
	cb.lightDirection = Light::GetDirection();
	cb.cameraPosition = XMFLOAT4(Camera::GetPosition().x, Camera::GetPosition().y, Camera::GetPosition().z, 0);
	cb.lightPosition = Light::GetPosition(0);

	for (int i = 0; i < LIGHT_TOTAL_NUM; i++)
	{
		cb.pos[i] = Light::GetPosition(i);
		cb.intensity[i] = XMFLOAT4(Light::GetIntensity(i), Light::GetIntensity(i), Light::GetIntensity(i), Light::GetIntensity(i));
	}

	//�����J�����̕��������Ȃ�
	if (GetObjectName() == "LookCamSignboard")
		cb.isBrightness = 10;
	//�������邢�ŔȂ�
	else if(GetObjectName() == "BrightSignboard")
		cb.isBrightness = 10;
	else
		cb.isBrightness = ZERO;

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃��\�[�X�A�N�Z�X���ꎞ�~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		// ���\�[�X�֒l�𑗂�

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	//������`�悷�钸�_�����V�F�[�_�ɓ`����
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	//�g�p����R���X�^���g�o�b�t�@���V�F�[�_�ɓ`����
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ

	Direct3D::pContext_->DrawIndexed(6, 0, 0);

	//�V�F�[�_���Z�b�g
	Direct3D::SetShader(Direct3D::SHADER_3D);
}

//���
void Signboard::Release()
{
}
