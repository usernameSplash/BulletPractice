#include "VertexArray.h"
#include <cstdio>

VertexArray::VertexArray(ID3D11Device* device, float width, float height) :
	m_Width(width),
	m_Height(height),
	m_VertexBuffer(nullptr),
	m_IndexBuffer(nullptr)
{
	CreateVertexBuffer(device);
	CreateIndexBuffer(device);
}

VertexArray::VertexArray(ID3D11Device* device, FXMVECTOR size) :
	m_Width(XMVectorGetX(size)),
	m_Height(XMVectorGetY(size)),
	m_VertexBuffer(nullptr),
	m_IndexBuffer(nullptr)
{
	CreateVertexBuffer(device);
	CreateIndexBuffer(device);
}

VertexArray::VertexArray(ID3D11Device* device, VertexArray &other) :
	m_Width(other.m_Width),
	m_Height(other.m_Height),
	m_VertexBuffer(nullptr),
	m_IndexBuffer(nullptr)
{
	CreateVertexBuffer(device);
	CreateIndexBuffer(device);
}

VertexArray::~VertexArray()
{
	if (m_VertexBuffer)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = nullptr;
	}
	if (m_IndexBuffer)
	{
		m_IndexBuffer->Release();
		m_IndexBuffer = nullptr;
	}
}

void VertexArray::draw(ID3D11DeviceContext* deviceContext)
{
	UINT stride = sizeof(VertexInputType);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, offset);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->DrawIndexed(INDEX_COUNT, 0, 0);
}

void VertexArray::setSize(ID3D11DeviceContext* deviceContext, float width, float height)
{
	m_Width = width;
	m_Height = height;
	
	fillVertexBuffer(deviceContext);
}

void VertexArray::setSize(ID3D11DeviceContext* deviceContext, FXMVECTOR size)
{
	m_Width = XMVectorGetX(size);
	m_Height = XMVectorGetY(size);

	fillVertexBuffer(deviceContext);
}

void VertexArray::fillVertexBuffer(ID3D11DeviceContext* deviceContext)
{
	D3D11_MAPPED_SUBRESOURCE vmr;
	deviceContext->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vmr);

	VertexInputType* vertexptr = static_cast<VertexInputType*>(vmr.pData);

	vertexptr[0].position = { -m_Width / 2, m_Height / 2, 0.0f, 1.0f };
	vertexptr[1].position = { m_Width / 2, m_Height / 2, 0.0f, 1.0f };
	vertexptr[2].position = { m_Width / 2, -m_Height / 2, 0.0f, 1.0f };
	vertexptr[3].position = { -m_Width / 2, -m_Height / 2, 0.0f, 1.0f };

	vertexptr[0].tex = { 0.0f, 0.0f };
	vertexptr[1].tex = { 1.0f, 0.0f };
	vertexptr[2].tex = { 1.0f, 1.0f };
	vertexptr[3].tex = { 0.0f, 1.0f };

	deviceContext->Unmap(m_VertexBuffer, 0);

}

void VertexArray::CreateVertexBuffer(ID3D11Device* device)
{
	VertexInputType* vertices = new VertexInputType[VERTEX_COUNT];

	vertices[0].position = { -m_Width / 2, m_Height / 2, 0.0f, 1.0f };
	vertices[1].position = { m_Width / 2, m_Height / 2, 0.0f, 1.0f };
	vertices[2].position = { m_Width / 2, -m_Height / 2, 0.0f, 1.0f };
	vertices[3].position = { -m_Width / 2, -m_Height / 2, 0.0f, 1.0f };

	vertices[0].tex = { 0.0f, 0.0f };
	vertices[1].tex = { 1.0f, 0.0f };
	vertices[2].tex = { 1.0f, 1.0f };
	vertices[3].tex = { 0.0f, 1.0f };

	D3D11_BUFFER_DESC vbd;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.ByteWidth = sizeof(VertexInputType) * VERTEX_COUNT;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	vbd.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA vrd;
	vrd.pSysMem = static_cast<void *>(vertices);
	vrd.SysMemPitch = 0;
	vrd.SysMemSlicePitch = 0;

	HRESULT hr = device->CreateBuffer(&vbd, &vrd, &m_VertexBuffer);
	if (FAILED(hr))
	{
		throw "Create VertexArray's VertexBuffer Failed";
	}

	delete vertices;
}

void VertexArray::CreateIndexBuffer(ID3D11Device* device)
{
	UINT* indices = new UINT[INDEX_COUNT];

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	D3D11_BUFFER_DESC ibd;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.ByteWidth = sizeof(UINT) * INDEX_COUNT;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA ird;
	ird.pSysMem = static_cast<void *>(indices);
	ird.SysMemPitch = 0;
	ird.SysMemSlicePitch = 0;

	HRESULT hr = device->CreateBuffer(&ibd, &ird, &m_IndexBuffer);
	if (FAILED(hr))
	{
		throw "Create IndexBuffer Failed";
	}

	delete indices;
}