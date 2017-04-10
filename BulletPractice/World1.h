#pragma once
#include "World.h"
#include "Enemy.h"
#include "DirectionalEnemy.h"

class World1 : public World {
public:
	World1() = delete;
	World1(World1 &) = delete;
	World1(ID3D11Device* device, Enemy* enemy);
	virtual ~World1();

	void update(float deltaTime) override;
	void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) override;
	
private:
	Enemy* Enemy1;
};



//	m_MultipleSpiralEnemy(new MultipleSpiralEnemy(device, m_EnemyTexture, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 10.0f, 0.2f, 1)),