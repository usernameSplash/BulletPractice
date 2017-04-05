#include "D3DClass.h"
#include "GameState.h"
#include "GameConstant.h"


D3DClass::D3DClass(HWND hWnd) :
	m_Device(nullptr),			//장치
	m_DeviceContext(nullptr),	//장치 문맥
	m_SwapChain(nullptr),		//교환사슬
	m_RenderTargetView(nullptr),//렌더 대상 뷰
	m_Shader(nullptr)			//셰이더
{
	HRESULT hr;
	
	//d3d 디바이스 생성
	UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	
	hr = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, 0, 0, D3D11_SDK_VERSION,
		&m_Device, &m_FeatureLevel, &m_DeviceContext);

	if (FAILED(hr))
	{
		throw L"D3D11CreateDevie Failed";
	}

	if (m_FeatureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		throw L"Direct3D Feature Level 11 unsupported";
	}

	//다중표본화 지원 품질 수준 확인
	hr = m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality);

	if (FAILED(hr))
	{
		throw L"CheckMultisampleQualityLevels Failed";
	}
	else if (m_4xMsaaQuality <= 0)
	{
		throw L"4xMultisampling unsupported";
	}

	//교환사슬 설정
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = GameConstant::GameWidth;
	sd.BufferDesc.Height = GameConstant::GameHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferCount = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Flags = 0;
	sd.OutputWindow = hWnd;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = true;
	sd.SampleDesc.Count = 4;
	sd.SampleDesc.Quality = m_4xMsaaQuality - 1;


	//교환사슬 생성과 오류 검출
	IDXGIDevice* dxgiDevice = nullptr;
	hr = m_Device->QueryInterface(__uuidof(IDXGIDevice), (void **)&dxgiDevice);
	if (FAILED(hr))
	{
		throw L"Get DXGIDevice Failed";
	}

	IDXGIAdapter* dxgiAdapter = nullptr;
	hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&dxgiAdapter);
	if (FAILED(hr))
	{
		throw L"Get DXGIAdapter Failed";
	}

	IDXGIFactory* dxgiFactory = nullptr;
	hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&dxgiFactory);
	if (FAILED(hr))
	{
		throw L"Get DXGIFactory Failed";
	}

	hr = dxgiFactory->CreateSwapChain(m_Device, &sd, &m_SwapChain);
	if (FAILED(hr))
	{
		throw L"Create SwapChain Failed";
	}

	//교환사슬 생성에 사용한 인터페이스 해제 (dxgiDevice, dxgiAdapter, dxgiFactory)
	if (dxgiDevice)
	{
		dxgiDevice->Release();
		dxgiDevice = nullptr;
	}

	if (dxgiAdapter)
	{
		dxgiAdapter->Release();
		dxgiAdapter = nullptr;
	}

	if (dxgiFactory)
	{
		dxgiFactory->Release();
		dxgiFactory = nullptr;
	}

	//렌더 타겟 뷰 생성
	ID3D11Texture2D* backBuffer = nullptr;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backBuffer);
	m_Device->CreateRenderTargetView(backBuffer, 0, &m_RenderTargetView);
	//backBuffer 인터페이스 해제
	if (backBuffer)
	{
		backBuffer->Release();
		backBuffer = nullptr;
	}


	//깊이 스텐실 버퍼 설정
	D3D11_TEXTURE2D_DESC td;
	td.ArraySize = 1;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	td.Height = GameConstant::GameHeight;
	td.MipLevels = 1;
	td.MiscFlags = 0;
	td.SampleDesc.Count = 4;
	td.SampleDesc.Quality = m_4xMsaaQuality - 1;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.Width = GameConstant::GameWidth;

	//깊이 스텐실 버퍼 생성
	hr = m_Device->CreateTexture2D(&td, 0, &m_DepthStencilBuffer);
	if (FAILED(hr))
	{
		throw L"Create DepthStencilBuffer Failed";
	}

	hr = m_Device->CreateDepthStencilView(m_DepthStencilBuffer, 0, &m_DepthStencilView);
	if (FAILED(hr))
	{
		throw L"Create DepthStencilView Failed";
	}

	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	//뷰포트 설정
	D3D11_VIEWPORT viewport;
	viewport.Height = GameConstant::GameHeight;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = GameConstant::GameWidth;

	m_DeviceContext->RSSetViewports(1, &viewport);

	//혼합 상태 설정
	D3D11_BLEND_DESC bd;
	bd.AlphaToCoverageEnable = false;
	bd.IndependentBlendEnable = false;
	
	D3D11_RENDER_TARGET_BLEND_DESC tbd = bd.RenderTarget[0];
	tbd.BlendEnable = true;
	tbd.BlendOp = D3D11_BLEND_OP_ADD;
	tbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	tbd.DestBlend = D3D11_BLEND_SRC_ALPHA;
	tbd.DestBlendAlpha = D3D11_BLEND_ZERO;
	tbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	tbd.SrcBlend = D3D11_BLEND_INV_SRC_ALPHA;
	tbd.SrcBlendAlpha = D3D11_BLEND_DEST_ALPHA;

	
	m_Device->CreateBlendState(&bd, &m_BlendState);
	

	m_Shader = new Shader(m_Device, L"./VertexShader.hlsl", L"./PixelShader.hlsl");

	XMMATRIX ortho = XMMatrixOrthographicLH(GameConstant::GameWidth, GameConstant::GameHeight, 0.0f, 11.0f);

	XMStoreFloat4x4(&m_OrthoMatrix, ortho);
}

D3DClass::~D3DClass()
{
	if (m_Shader)
	{
		delete m_Shader;
		m_Shader = nullptr;
	}
	if (m_BlendState)
	{
		m_BlendState->Release();
		m_BlendState = nullptr;
	}
	if (m_DepthStencilView)
	{
		m_DepthStencilView->Release();
		m_DepthStencilView = nullptr;
	}

	if (m_DepthStencilBuffer)
	{
		m_DepthStencilBuffer->Release();
		m_DepthStencilBuffer = nullptr;
	}

	if (m_RenderTargetView)
	{
		m_RenderTargetView->Release();
		m_RenderTargetView = nullptr;
	}

	if (m_SwapChain)
	{
		m_SwapChain->Release();
		m_SwapChain = nullptr;
	}

	if (m_DeviceContext)
	{
		m_DeviceContext->Release();
		m_DeviceContext = nullptr;
	}

	if (m_Device)
	{
		m_Device->Release();
		m_Device = nullptr;
	}
}

void D3DClass::render()
{
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_DeviceContext->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);
	XMMATRIX ortho = XMLoadFloat4x4(&m_OrthoMatrix); //직교투영 행렬
	float bgColor[4] = { 1.0f, 1.0f, 1.0f, 0.0f };	 //배경색

	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, bgColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	m_Shader->render(m_DeviceContext);
	
	GameState::world->draw(m_DeviceContext, ortho);

	m_SwapChain->Present(0, NULL);
}

ID3D11Device* D3DClass::getDevice()
{
	return m_Device;
}