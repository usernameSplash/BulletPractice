#include "Shader.h"

Shader::Shader(ID3D11Device* device, LPCWSTR vertexPath, LPCWSTR pixelPath):
	m_VertexShader(nullptr),	//¡§¡° ºŒ¿Ã¥ı
	m_PixelShader(nullptr),		//«»ºø ºŒ¿Ã¥ı
	m_InputLayout(nullptr)
{
	DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* vertexShaderBuffer = nullptr;
	ID3D10Blob* pixelShaderBuffer = nullptr;
	ID3D10Blob* errorMessage = nullptr;
	HRESULT hr;

	hr = D3DX11CompileFromFile(vertexPath, NULL, NULL, "main", "vs_5_0", shaderFlags, 0, nullptr, &vertexShaderBuffer, &errorMessage, nullptr);

	if (FAILED(hr))
	{
		if (errorMessage)
		{
			throw static_cast<char*>(errorMessage->GetBufferPointer());
		}
		else
		{
			throw L"No Vertex Shader File";
		}
	}

	hr = D3DX11CompileFromFile(pixelPath, NULL, NULL, "main", "ps_5_0", shaderFlags, 0, nullptr, &pixelShaderBuffer, &errorMessage, nullptr);

	if (FAILED(hr))
	{
		if (errorMessage)
		{
			throw static_cast<char*>(errorMessage->GetBufferPointer());
		}
		else
		{
			throw L"No Pixel Shader File";
		}
	}

	hr = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_VertexShader);

	if (FAILED(hr))
	{
		throw L"CreateVertexShader Failed";
	}

	hr = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_PixelShader);

	if (FAILED(hr))
	{
		throw L"CreatePixelShader Failed";
	}

	D3D11_INPUT_ELEMENT_DESC ed[2];
	ed[0].AlignedByteOffset = 0;
	ed[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	ed[0].InputSlot = 0;
	ed[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	ed[0].InstanceDataStepRate = 0;
	ed[0].SemanticIndex = 0;
	ed[0].SemanticName = "POSITION";

	ed[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	ed[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	ed[1].InputSlot = 0;
	ed[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	ed[1].InstanceDataStepRate = 0;
	ed[1].SemanticIndex = 0;
	ed[1].SemanticName = "TEXCOORD";

	hr = device->CreateInputLayout(ed, 2, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_InputLayout);

	if (FAILED(hr))
	{
		throw L"CreateInputLayout Failed";
	}

	if (vertexShaderBuffer)
	{
		vertexShaderBuffer->Release();
		vertexShaderBuffer = nullptr;
	}

	if (pixelShaderBuffer)
	{
		pixelShaderBuffer->Release();
		pixelShaderBuffer = nullptr;
	}
}

Shader::~Shader()
{
	if (m_InputLayout)
	{
		m_InputLayout->Release();
		m_InputLayout = nullptr;
	}
	if (m_PixelShader)
	{
		m_PixelShader->Release();
		m_PixelShader = nullptr;
	}
	if (m_VertexShader)
	{
		m_VertexShader->Release();
		m_VertexShader = nullptr;
	}
}

void Shader::render(ID3D11DeviceContext* deviceContext)
{
	deviceContext->IASetInputLayout(m_InputLayout);
	deviceContext->VSSetShader(m_VertexShader, NULL, 0);
	deviceContext->PSSetShader(m_PixelShader, NULL, 0);
}