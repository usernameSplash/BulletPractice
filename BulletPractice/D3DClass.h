#pragma once
#include <DXGI.h>
#include <D3D11.h>
#include <Windows.h>
#include <xnamath.h>
#include "Shader.h"

class D3DClass
{
public:
	D3DClass(HWND hWnd);
	D3DClass(D3DClass &) = default;
	~D3DClass();

	void render();
	ID3D11Device* getDevice();
private:
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DeviceContext;
	IDXGISwapChain* m_SwapChain;
	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11Texture2D* m_DepthStencilBuffer;
	ID3D11DepthStencilView* m_DepthStencilView;
	ID3D11BlendState* m_BlendState;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	UINT m_4xMsaaQuality;
	Shader* m_Shader;
	XMFLOAT4X4 m_OrthoMatrix;
};