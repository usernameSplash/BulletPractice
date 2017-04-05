#include "Texture.h"

Texture::Texture(ID3D11Device* device, LPCWSTR imagePath) :
	m_Texture(nullptr),
	m_State(nullptr)
{
	HRESULT hr;

	hr = D3DX11CreateShaderResourceViewFromFile(device, imagePath, nullptr, nullptr, &m_Texture, nullptr);
	if (FAILED(hr))
	{
		throw "Image Load Failed";
	}
	
	D3D11_SAMPLER_DESC sd;
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.MipLODBias = 0.0f;
	sd.MaxAnisotropy = 1;
	sd.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sd.BorderColor[0] = 1;
	sd.BorderColor[1] = 0;
	sd.BorderColor[2] = 1;
	sd.BorderColor[3] = 0;
	sd.MinLOD = -D3D11_FLOAT32_MAX;
	sd.MaxLOD = D3D11_FLOAT32_MAX;

	hr = device->CreateSamplerState(&sd, &m_State);
	if (FAILED(hr))
	{
		throw "Create SamplerState Failed";
	}
}

Texture::~Texture()
{
	if (m_Texture)
	{
		m_Texture->Release();
		m_Texture = nullptr;
	}
	if (m_State)
	{
		m_State->Release();
		m_State = nullptr;
	}
}

void Texture::bind(ID3D11DeviceContext* deviceContext)
{
	deviceContext->PSSetShaderResources(0, 1, &m_Texture);

	deviceContext->PSSetSamplers(0, 1, &m_State);
}