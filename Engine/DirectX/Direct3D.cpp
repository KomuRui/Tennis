#include <d3dcompiler.h>
#include "Direct3D.h"
#include "../ResourceManager/Global.h"
#include "../GameObject/Transform.h"
#include "../GUI/imgui/imgui.h"
#include "../GUI/imgui/imgui_impl_win32.h"
#include "../GUI/imgui/imgui_impl_dx11.h"
#include "Sprite.h"


//��ʂ̕`��Ɋւ��鏈��
namespace Direct3D
{
	//�y�X���b�v�`�F�[���z
	//��p����2���p�����Ă����A�Е�����ʂɉf���Ă���Ԃɂ�������ɕ`��B
	//1�t���[�����̊G���o���オ�������p���������B����ɂ���ʂ�������Ȃ��B
	//���̕ӂ��i��̂��X���b�v�`�F�[��
	IDXGISwapChain* pSwapChain_ = nullptr;
	IDXGISwapChain* pSwapChain_2 = nullptr;

	//�y�����_�[�^�[�Q�b�g�r���[�z
	//�`�悵�������̂ƁA�`���i��ł�����p���j�̋��n�����������
	ID3D11RenderTargetView* pRenderTargetView_ = nullptr;
	ID3D11RenderTargetView* pRenderTargetView2 = nullptr;

	//�y�f�v�X�X�e���V���z
	//Z�o�b�t�@�@��p���āA3D���̂̑O��֌W�𐳂����\�����邽�߂̂���
	ID3D11Texture2D* pDepthStencil;

	//�y�f�v�X�X�e���V���r���[�z
	//�f�v�X�X�e���V���̏����V�F�[�_�[�ɓn�����߂̂���
	ID3D11DepthStencilView* pDepthStencilView;
	ID3D11DepthStencilState* pDepthStencilState[BLEND_MAX];

	//�y�u�����h�X�e�[�g�z
	//�������̂��̂��ǂ̂悤�ɕ\�����邩
	ID3D11BlendState* pBlendState[BLEND_MAX];

	bool		isDrawCollision_ = true;	//�R���W������\�����邩
	bool		_isLighting = false;		//���C�e�B���O���邩
	
	//���s�Ƃ߂邩�ĊJ���邩
	bool time_Scale = true;

	//�Q�[����ʂ��t�����ǂ���
	bool isGameFull = false;

	//��ʂ��Q�[����Ԃ��ǂ���
	bool isScreenGameStatus = true;

	//���ݎg���Ă���V�F�[�_�[�̃^�C�v
	SHADER_TYPE shaderType;

	//�w�i�F
	XMFLOAT4 backScreenColor = {0,0,0,0};

	//extern�錾�����ϐ��̏�����
	ID3D11Device*           pDevice_ = nullptr;
	ID3D11DeviceContext*    pContext_ = nullptr;
	SHADER_BUNDLE			shaderBundle[SHADER_MAX] = { 0 };
	int						screenWidth_ = 0;
	int						screenHeight_ = 0;

	D3D11_VIEWPORT vp, vpEmission, vpFull,vpMini;

	Sprite* pScreen;

	ID3D11Texture2D* pRenderTexture;

	int screenWidth;
	int screenHeight;
	Texture* pToonTexture;

	//���ԂƑ҂��Ă���̂��Q�b�g
	bool GetTimeScale()
	{
		return time_Scale;
	}

	//���Ԏ~�߂邩�Z�b�g
	void SetTimeScale(bool a)
	{
		time_Scale = a;
	}

	//�Q�[����ʂ��t���T�C�Y���擾
	bool GetGameFull()
	{
		return isGameFull;
	}

	//�Q�[����ʃt���ɂ��邩�ǂ����Z�b�g
	void SetGameFull(bool a)
	{
		//��ʂ̑傫���ɂ���ăr���[�|�[�g�̃T�C�Y��ύX����
		if (a)
			vp = vpFull;
		else
			vp = vpMini;

		//��Ԃ��Z�b�g
		isGameFull = a;
	}

	//��ʂ��Q�[����ԂȂ̂��擾
	bool GetScreenGameStatus()
	{
		return isScreenGameStatus;
	}

	//��ʂ��Q�[����Ԃɂ��邩�ǂ����Z�b�g
	void SetScreenGameStatus(bool a)
	{
		isScreenGameStatus = a;
	}

	//����������
	HRESULT Direct3D::Initialize(HWND hWnd, int screenWidth, int screenHeight)
	{
		///////////////////////////���낢�돀�����邽�߂̐ݒ�///////////////////////////////
		//���낢��Ȑݒ荀�ڂ��܂Ƃ߂��\����
		DXGI_SWAP_CHAIN_DESC scDesc;

		//�Ƃ肠�����S��0
		ZeroMemory(&scDesc, sizeof(scDesc));

		//�`���̃t�H�[�}�b�g
		scDesc.BufferDesc.Width = screenWidth;		//��ʕ�
		scDesc.BufferDesc.Height = screenHeight;		//��ʍ���
		scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// ���F�g���邩

		//FPS�i1/60�b��1��j
		scDesc.BufferDesc.RefreshRate.Numerator = 60;
		scDesc.BufferDesc.RefreshRate.Denominator = 1;

		//���̑�
		scDesc.Windowed = TRUE;				//�E�B���h�E���[�h���t���X�N���[����
		scDesc.OutputWindow = hWnd;			//�E�B���h�E�n���h��
		scDesc.BufferCount = 1;				//����ʂ̖���
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//��ʂɕ`�悷�邽�߂Ɏg��
		scDesc.SampleDesc.Count = 1;		//MSAA�i�A���`�G�C���A�X�j�̐ݒ�
		scDesc.SampleDesc.Quality = 0;		//�@�V



		///////////////////////////��L�ݒ�����ƂɃf�o�C�X�A�R���e�L�X�g�A�X���b�v�`�F�C�����쐬///////////////////////////////
		D3D_FEATURE_LEVEL level;
		HRESULT  hr;
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,					// �ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr��
			D3D_DRIVER_TYPE_HARDWARE,	// �h���C�o�̃^�C�v��n���B����ȊO�͊�{�I�Ƀ\�t�g�E�F�A�����ŁA�ǂ����Ă��Ƃ�������f�o�O�p�ɗp����ׂ�.
			nullptr,					// ��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵���ۂɁA���̏������s��DLL�̃n���h����n���B����ȊO���w�肵�Ă���ۂɂ͕K��nullptr��n��.
			0,							// ���炩�̃t���O���w�肷��B�i�f�o�b�O����D3D11_CREATE_DEVICE_DEBUG�H�j
			nullptr,					// �f�o�C�X�A�R���e�L�X�g�̃��x����ݒ�Bnullptr�ɂ��Ƃ��Ή\�Ȍ��荂�����x���ɂ��Ă����
			0,							// ��̈����Ń��x�������w�肵����
			D3D11_SDK_VERSION,			// SDK�̃o�[�W�����B�K�����̒l
			&scDesc,					// ��ł��낢��ݒ肵���\����
			&pSwapChain_,				// ������������SwapChain�̃A�h���X���Ԃ��Ă���
			&pDevice_,					// ������������Device�A�h���X���Ԃ��Ă���
			&level,						// ������������Device�AContext�̃��x�����Ԃ��Ă���
			&pContext_);				// ������������Context�̃A�h���X���Ԃ��Ă���

		//���s������I��
		if (FAILED(hr))	return hr;


		///////////////////////////�`��̂��߂̏���///////////////////////////////
		//�X���b�v�`�F�[������o�b�N�o�b�t�@���擾�i�o�b�N�o�b�t�@ �� ����� �� �`���j
		ID3D11Texture2D* pBackBuffer;
		hr = pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		//���s������I��
		if (FAILED(hr))	return hr;

		//�����_�[�^�[�Q�b�g�r���[���쐬
		hr = pDevice_->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView_);
		

		//���s������I��
		if (FAILED(hr))	return hr;

		//�ꎞ�I�Ƀo�b�N�o�b�t�@���擾���������Ȃ̂ŁA���
		pBackBuffer->Release();

		/////////////////��l�v���C/////////////////

		//���Full
		vpFull.Width = (float)screenWidth;	 //��
		vpFull.Height = (float)screenHeight; //����
		vpFull.MinDepth = 0.0f;				 //��O
		vpFull.MaxDepth = 1.0f;				 //��
		vpFull.TopLeftX = 0;				 //��
		vpFull.TopLeftY = 0;				 //��

		//��ʃ~�j
		vpMini.Width = (float)screenWidth / 1.5f;	//��
		vpMini.Height = (float)screenHeight / 1.5f;	//����
		vpMini.MinDepth = 0.0f;		//��O
		vpMini.MaxDepth = 1.0f;		//��
		vpMini.TopLeftX = 0;		//��
		vpMini.TopLeftY = 100;		//��

		//�ڂ����\������p
		vpEmission.Width = (float)screenWidth / TEX_DIV;		//��
		vpEmission.Height = (float)screenHeight / TEX_DIV;		//����
		vpEmission.MinDepth = 0.0f;		//��O
		vpEmission.MaxDepth = 1.0f;		//��
		vpEmission.TopLeftX = 0;		//��
		vpEmission.TopLeftY = 0;		//��

		//�ŏ��̉�ʂ̓~�j��Ԃɂ��Ă���
		vp = vpMini;

		//�e�p�^�[���̃V�F�[�_�[�Z�b�g����
		InitShaderBundle();
		Direct3D::SetShader(Direct3D::SHADER_3D);

		UINT SampleCount = 4;
		UINT Quality = 0;
		pDevice_->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, SampleCount, &Quality);
		Quality -= 1;

		//�[�x�X�e���V���r���[�̍쐬
		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width = screenWidth;
		descDepth.Height = screenHeight;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		pDevice_->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
		pDevice_->CreateDepthStencilView(pDepthStencil, NULL, &pDepthStencilView);

		//�[�x�e�X�g���s���[�x�X�e���V���X�e�[�g�̍쐬
		{
			//�f�t�H���g
			D3D11_DEPTH_STENCIL_DESC desc = {};
			desc.DepthEnable = true;
			desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
			desc.StencilEnable = true;
			pDevice_->CreateDepthStencilState(&desc, &pDepthStencilState[BLEND_DEFAULT]);
			pContext_->OMSetDepthStencilState(pDepthStencilState[BLEND_DEFAULT], 0);

			//���Z�����p�i�������݂Ȃ��j
			desc.StencilEnable = false;
			pDevice_->CreateDepthStencilState(&desc, &pDepthStencilState[BLEND_ADD]);
		}

		//�u�����h�X�e�[�g
		{
			//�ʏ�
			D3D11_BLEND_DESC BlendDesc;
			ZeroMemory(&BlendDesc, sizeof(BlendDesc));
			BlendDesc.AlphaToCoverageEnable = FALSE;
			BlendDesc.IndependentBlendEnable = FALSE;
			BlendDesc.RenderTarget[0].BlendEnable = TRUE;

			BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

			BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			pDevice_->CreateBlendState(&BlendDesc, &pBlendState[BLEND_DEFAULT]);
			float blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
			pContext_->OMSetBlendState(pBlendState[BLEND_DEFAULT], blendFactor, 0xffffffff);

			//���Z�����i�d�Ȃ�قǌ����Č�������ʁj
			BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
			pDevice_->CreateBlendState(&BlendDesc, &pBlendState[BLEND_ADD]);
		}

		////�p�C�v���C���̍\�z
		////�f�[�^����ʂɕ`�悷�邽�߂̈�ʂ�̐ݒ�
		pContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // �f�[�^�̓��͎�ނ��w��
		//pContext_->OMSetRenderTargets(1, &pRenderTargetView_, pDepthStencilView);  // �`����ݒ�i����̓����_�[�^�[�Q�b�g�r���[����ĕ`�悵�Ăˁj
		//pContext_->RSSetViewports(1, &vp);                                         // �r���[�|�[�g�̃Z�b�g


		//�R���W�����\�����邩
		isDrawCollision_ = GetPrivateProfileInt("DEBUG", "ViewCollider", 0, ".\\setup.ini") != 0;


		screenWidth_ = screenWidth;
		screenHeight_ = screenHeight;

		D3D11_TEXTURE2D_DESC texdec;
		texdec.Width = screenWidth / TEX_DIV;
		texdec.Height = screenHeight / TEX_DIV;
		texdec.MipLevels = 1;
		texdec.ArraySize = 1;
		texdec.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texdec.SampleDesc.Count = 1;
		texdec.SampleDesc.Quality = 0;
		texdec.Usage = D3D11_USAGE_DEFAULT;
		texdec.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		texdec.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		texdec.MiscFlags = 0;
		pDevice_->CreateTexture2D(&texdec, nullptr, &pRenderTexture);

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		ZeroMemory(&renderTargetViewDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;
		pDevice_->CreateRenderTargetView(pRenderTexture,
			&renderTargetViewDesc, &pRenderTargetView2);


		pScreen = new Sprite;
		pScreen->Initialize(pRenderTexture);

		return S_OK;
	}


	//�V�F�[�_�[�֘A�ŕK�v�ȃZ�b�g����
	void InitShaderBundle()
	{
		DWORD vectorSize = sizeof(XMFLOAT3);

		//3D
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob *pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_3D].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob *pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_3D].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//���_�ʒu
				{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�@��
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�e�N�X�`���iUV�j���W
			};
			pDevice_->CreateInputLayout(layout, 3, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_3D].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_3D].pRasterizerState);
		}

		//2D
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob *pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/Simple2D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_2D].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob *pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/Simple2D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_2D].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			pDevice_->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_2D].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_2D].pRasterizerState);
		}

		//DEBUG�p
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob *pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/Debug3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_UNLIT].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob *pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/Debug3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_UNLIT].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			pDevice_->CreateInputLayout(layout, 1, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_UNLIT].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_NONE;
			rdc.FillMode = D3D11_FILL_WIREFRAME;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_UNLIT].pRasterizerState);
		}

		//BillBoard
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/BillBoard.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_BILLBOARD].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/BillBoard.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_BILLBOARD].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			pDevice_->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_BILLBOARD].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_NONE;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_BILLBOARD].pRasterizerState);
		}

		//SignBoard
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/SignBoard.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_SIGNBOARD].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/SignBoard.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_SIGNBOARD].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//���_�ʒu
				{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�@��
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�e�N�X�`���iUV�j���W
			};
			pDevice_->CreateInputLayout(layout, 3, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_SIGNBOARD].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_NONE;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_SIGNBOARD].pRasterizerState);
		}

		//FadeIn
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/Fade.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_FADE_IN].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/Fade.hlsl", nullptr, nullptr, "PS_FadeIn", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_FADE_IN].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			pDevice_->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_FADE_IN].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_FADE_IN].pRasterizerState);
		}

		//FadeOut
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/Fade.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_FADE_OUT].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/Fade.hlsl", nullptr, nullptr, "PS_FadeOut", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_FADE_OUT].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			pDevice_->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_FADE_OUT].pVertexLayout);

			
			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_FADE_OUT].pRasterizerState);
		}

		//ReversColor
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/ReversColorImage.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_REVERS_COLOR].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/ReversColorImage.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_REVERS_COLOR].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			pDevice_->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_REVERS_COLOR].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_REVERS_COLOR].pRasterizerState);
		}

		//NormalMap
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/NormalMapShader.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_NORMALMAP].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/NormalMapShader.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_NORMALMAP].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//���_�ʒu
				{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�@��
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�e�N�X�`���iUV�j���W
				{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 } //�ڐ�
			};
			pDevice_->CreateInputLayout(layout, 4, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_NORMALMAP].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_NORMALMAP].pRasterizerState);
		}

		//OutLine
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/OutLine.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_OUTLINE].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/OutLine.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_OUTLINE].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//���_�ʒu
				{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�@��
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�e�N�X�`���iUV�j���W
			};
			pDevice_->CreateInputLayout(layout, 3, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_OUTLINE].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = FALSE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_OUTLINE].pRasterizerState);
		}
	}


	//������`�悷��ShaderBundle��ݒ�
	void SetShader(SHADER_TYPE type)
	{
		shaderType = type;
		pContext_->RSSetState(shaderBundle[type].pRasterizerState);
		pContext_->VSSetShader(shaderBundle[type].pVertexShader, NULL, 0);                         // ���_�V�F�[�_���Z�b�g
		pContext_->PSSetShader(shaderBundle[type].pPixelShader, NULL, 0);                          // �s�N�Z���V�F�[�_���Z�b�g
		pContext_->IASetInputLayout(shaderBundle[type].pVertexLayout);
	}

	//ShaderBundle���Q�b�g
	SHADER_TYPE GetShader() {
		return shaderType;
	}

	//�u�����h���[�h�̕ύX
	void SetBlendMode(BLEND_MODE blendMode)
	{
		//���Z����
		float blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
		pContext_->OMSetBlendState(pBlendState[blendMode], blendFactor, 0xffffffff);

		//Z�o�b�t�@�ւ̏�������
		pContext_->OMSetDepthStencilState(pDepthStencilState[blendMode], 0);
	}

	//�w�i�F��ݒ�
	void SetBackScreenColor(XMFLOAT4 color)
	{
		backScreenColor = color;
	}

	//�`��J�n
	void BeginDraw()
	{
		//���������ł��ĂȂ����̂�����������߂�
		if (NULL == pDevice_) return;
		if (NULL == pContext_) return;
		if (NULL == pRenderTargetView_) return;
		if (NULL == pSwapChain_) return;

		pContext_->OMSetRenderTargets(1, &pRenderTargetView_, pDepthStencilView);            // �`����ݒ�
		pContext_->RSSetViewports(1, &vp);

		//�w�i�̐F
		float clearColor[4] = { backScreenColor.x, backScreenColor.y, backScreenColor.z, 1 };//R,G,B,A

		//�[�x�o�b�t�@�N���A
		pContext_->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		//��ʂ��N���A
		pContext_->ClearRenderTargetView(pRenderTargetView_, clearColor);

	}

	void BeginDrawToTexture()
	{
		pContext_->RSSetViewports(1, &vpEmission);                                      // �r���[�|�[�g�̃Z�b�g
		pContext_->OMSetRenderTargets(1, &pRenderTargetView2, pDepthStencilView);

		//�w�i�̐F
		float clearColor[4] = { backScreenColor.x, backScreenColor.y, backScreenColor.z, 1 };//R,G,B,A

		//��ʂ��N���A
		pContext_->ClearRenderTargetView(pRenderTargetView2, clearColor);

		//�[�x�o�b�t�@�N���A
		pContext_->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		//�f�t�H���g�ɃZ�b�g
		Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);
	}

	void ScreenDraw()
	{
		//���Z�����ɃZ�b�g
		Direct3D::SetBlendMode(Direct3D::BLEND_ADD);

		Transform transform;
		transform.scale_.x = TEX_DIV;
		transform.scale_.y = TEX_DIV;

		transform.Calclation();
		pScreen->Draw(transform);
		
	}

	//�`��I��
	void EndDraw()
	{
		//�X���b�v�i�o�b�N�o�b�t�@��\�ɕ\������j
		pSwapChain_->Present(0, 0);
	}


	//�J������
	void Release()
	{

		SAFE_RELEASE(pDepthStencil);
		SAFE_RELEASE(pDepthStencilView);
		SAFE_RELEASE(pRenderTargetView_);
		SAFE_RELEASE(pSwapChain_);

		for (int i = 0; i < BLEND_MAX; i++)
		{
			SAFE_RELEASE(pBlendState[i]);
			SAFE_RELEASE(pDepthStencilState[i]);
		}

		for (int i = 0; i < SHADER_MAX; i++)
		{
			SAFE_RELEASE(shaderBundle[i].pRasterizerState);
			SAFE_RELEASE(shaderBundle[i].pVertexLayout);
			SAFE_RELEASE(shaderBundle[i].pVertexShader);
			SAFE_RELEASE(shaderBundle[i].pPixelShader);
		}

		if (pContext_)
		{
			pContext_->ClearState();
		}

		SAFE_RELEASE(pRenderTargetView_);
		SAFE_RELEASE(pSwapChain_);
		SAFE_RELEASE(pContext_);
		SAFE_RELEASE(pDevice_);
	}


	//�O�p�`�Ɛ����̏Փ˔���i�Փ˔���Ɏg�p�j
	//https://pheema.hatenablog.jp/entry/ray-triangle-intersection
	bool Intersect(XMFLOAT3 & start, XMFLOAT3 & direction, XMFLOAT3 & v0, XMFLOAT3 & v1, XMFLOAT3 & v2, float* distance,XMVECTOR* pos)
	{
		// �����Ȓ萔([M?ller97] �ł̒l)
		constexpr float kEpsilon = 1e-6f;

		//�O�p�`�̂Q��
		XMVECTOR edge1 = XMVectorSet(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z, 0.0f);
		XMVECTOR edge2 = XMVectorSet(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z, 0.0f);

		XMVECTOR alpha = XMVector3Cross(XMLoadFloat3(&direction), edge2);
		float det = XMVector3Dot(edge1, alpha).m128_f32[0];

		// �O�p�`�ɑ΂��āA���C�����s�ɓ��˂���悤�ȏꍇ det = 0 �ƂȂ�B
		// det ������������� 1/det ���傫���Ȃ肷���Đ��l�I�ɕs����ɂȂ�̂�
		// det ? 0 �̏ꍇ�͌������Ȃ����ƂƂ���B
		if (-kEpsilon < det && det < kEpsilon) 
		{
			return false;
		}

		float invDet = 1.0f / det;
		XMFLOAT3 r = XMFLOAT3(start.x - v0.x, start.y - v0.y, start.z - v0.z);

		// u �� 0 <= u <= 1 �𖞂����Ă��邩�𒲂ׂ�B
		float u = XMVector3Dot(alpha, XMLoadFloat3(&r)).m128_f32[0] * invDet;
		if (u < 0.0f || u > 1.0f)
		{
			return false;
		}

		XMVECTOR beta = XMVector3Cross(XMLoadFloat3(&r), edge1);

		// v �� 0 <= v <= 1 ���� u + v <= 1 �𖞂������Ƃ𒲂ׂ�B
		// ���Ȃ킿�Av �� 0 <= v <= 1 - u ���݂����Ă��邩�𒲂ׂ��OK�B
		float v = XMVector3Dot(XMLoadFloat3(&direction), beta).m128_f32[0] * invDet;
		if (v < 0.0f || u + v > 1.0f) 
		{
			return false;
		}

		// t �� 0 <= t �𖞂������Ƃ𒲂ׂ�B
		float t = XMVector3Dot(edge2, beta).m128_f32[0] * invDet;
		if (t < 0.0f) 
		{
			return false;
		}

		*distance = t;

		*pos = XMLoadFloat3(&v0) + (edge1 * u) + (edge2 * v);
		return true;
	}

	//Z�o�b�t�@�ւ̏�������ON/OFF
	void SetDepthBafferWriteEnable(bool isWrite)
	{
		//ON
		if (isWrite)
		{
			//Z�o�b�t�@�i�f�v�X�X�e���V�����w�肷��j
			pContext_->OMSetRenderTargets(1, &pRenderTargetView_, pDepthStencilView);
		}

		//OFF
		else
		{
			pContext_->OMSetRenderTargets(1, &pRenderTargetView_, nullptr);
		}
	}

}
