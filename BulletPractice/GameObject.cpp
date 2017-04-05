#include "GameObject.h"

GameObject::GameObject(ID3D11Device* device, Texture* texture, float width, float height) :
	m_VertexArray(new VertexArray(device, width, height)),
	m_MatrixBuffer(nullptr),
	m_Texture(texture),
	m_Position({ 0.0f, 0.0f, 0.0f }),
	m_Scale({ 1.0f, 1.0f }),
	m_Angle(0.0f)
{
	createMatrixBuffer(device);
}

GameObject::~GameObject()
{
	if (m_VertexArray)
	{
		delete m_VertexArray;
		m_VertexArray = nullptr;
	}
	if (m_MatrixBuffer)
	{
		m_MatrixBuffer->Release();
		m_MatrixBuffer = nullptr;
	}
}

void GameObject::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix)
{
	fillMatrixBuffer(deviceContext, orthoMatrix);

	deviceContext->VSSetConstantBuffers(0, 1, &m_MatrixBuffer);

	m_Texture->bind(deviceContext);

	m_VertexArray->draw(deviceContext);
}

void GameObject::createMatrixBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC mbd;
	mbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	mbd.ByteWidth = sizeof(XMFLOAT4X4);
	mbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	mbd.MiscFlags = 0;
	mbd.StructureByteStride = 0;
	mbd.Usage = D3D11_USAGE_DYNAMIC;

	HRESULT hr = device->CreateBuffer(&mbd, nullptr, &m_MatrixBuffer);
	if (FAILED(hr))
	{
		throw "Create MatrixBuffer Failed";
	}
}

void GameObject::fillMatrixBuffer(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix)
{
	D3D11_MAPPED_SUBRESOURCE mmr;

	deviceContext->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mmr);

	XMMATRIX translateMatrix = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX rotateMatrix = XMMatrixRotationAxis(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), m_Angle);
	XMMATRIX scaleMatrix = XMMatrixScaling(m_Scale.x, m_Scale.y, 1.0f);

	XMMATRIX worldMatrix = scaleMatrix * rotateMatrix * translateMatrix;
	XMMATRIX worldOrthoMatrix = worldMatrix * orthoMatrix;

	XMStoreFloat4x4(static_cast<XMFLOAT4X4 *>(mmr.pData), XMMatrixTranspose(worldOrthoMatrix));

	deviceContext->Unmap(m_MatrixBuffer, 0);
}

void GameObject::setPosition(float x, float y, float z)
{
	m_Position = { x, y, z };
}

XMFLOAT3 GameObject::getPosition()
{
	return m_Position;
}

void GameObject::setScale(float x, float y)
{
	m_Scale = { x, y };
}

XMFLOAT2 GameObject::getScale()
{
	return m_Scale;
}

void GameObject::setAngle(float angle)
{
	m_Angle = angle;
}

float GameObject::getAngle()
{
	return m_Angle;
}

void GameObject::setTexture(Texture* texture)
{
	m_Texture = texture;
}