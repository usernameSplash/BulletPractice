#pragma once
#include "Texture.h"
#include "DirectionalEnemy.h"
#include "SpiralEnemy.h"
#include "Bullet.h"
#include <D3D11.h>
#include <xnamath.h>

class World
{
public:
	World() = delete;
	World(World&) = delete;
	World(ID3D11Device* device);
	~World();

	void update(float deltaTime);
	void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix);
	Bullet** Bullets;
private:
	Texture* m_EnemyTexture;
	DirectionalEnemy* m_DirectionalEnemy;
	SpiralEnemy* m_SpiralEnemy;
};