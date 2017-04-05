#pragma once
#include "VertexArray.h"
#include "Texture.h"
#include <D3D11.h>
#include <xnamath.h>

class GameObject
{
public:
	GameObject() = delete;
	GameObject(GameObject&) = delete;
	GameObject(ID3D11Device* device, Texture* texture, float width, float height);
	virtual ~GameObject();

	void virtual draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) final;
	void virtual update(float deltaTime) = 0;

protected:
	void virtual setPosition(float x, float y, float z);
	XMFLOAT3 virtual getPosition();

	void virtual setScale(float x, float y);
	XMFLOAT2 virtual getScale();

	void virtual setAngle(float angle);
	float virtual getAngle();

	void virtual setTexture(Texture* texture);

private:
	void createMatrixBuffer(ID3D11Device* device);
	void fillMatrixBuffer(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix);
	
private:
	XMFLOAT3 m_Position;
	XMFLOAT2 m_Scale;
	float m_Angle;
	VertexArray* m_VertexArray;
	ID3D11Buffer* m_MatrixBuffer;
	Texture* m_Texture;
};