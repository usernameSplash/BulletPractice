#pragma once
#include <D3D11.h>
#include <xnamath.h>

class VertexArray
{
private:
	static const int VERTEX_COUNT = 4;
	static const int INDEX_COUNT = 6;
	struct VertexInputType
	{
		XMFLOAT4 position;
		XMFLOAT2 tex;
	};
public:
	VertexArray(ID3D11Device* device, float width, float height);
	VertexArray(ID3D11Device* device, FXMVECTOR size);
	VertexArray(ID3D11Device* device, VertexArray &other);
	~VertexArray();

	void setSize(ID3D11DeviceContext* deviceContext, float width, float height);
	void setSize(ID3D11DeviceContext* deviceContext, FXMVECTOR size);

	void draw(ID3D11DeviceContext* deviceContext);
private:
	void fillVertexBuffer(ID3D11DeviceContext* deviceContext);
	void CreateVertexBuffer(ID3D11Device* device);
	void CreateIndexBuffer(ID3D11Device* device);
private:
	float m_Width;
	float m_Height;
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
};