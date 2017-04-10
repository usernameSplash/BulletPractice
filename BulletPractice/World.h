#pragma once
#include "Texture.h"
#include "Bullet.h"
#include <D3D11.h>
#include <xnamath.h>

class World
{
public:
	World() = delete;
	World(World&) = delete;
	World(ID3D11Device* device);
	virtual	~World();

	void virtual update(float deltaTime) = 0;
	void virtual draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) = 0;
	
private:
};