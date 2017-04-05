#include "World.h"
#include <cstdio>

World::World(ID3D11Device* device) :
	m_EnemyTexture(new Texture(device, L"./Enemy.dds")),
	m_DirectionalEnemy(new DirectionalEnemy(device, m_EnemyTexture, -960.0f + 64.0f, 540.0f - 64.0f, 335, 0, 500, 0, 0.1f)),
	Bullets(new Bullet*[10000])
{
	for (int i = 0; i < 10000; i++) {
		Bullets[i] = nullptr;
	}
}

World::~World()
{
	delete m_EnemyTexture;
	delete m_DirectionalEnemy;
	for (int i = 0; i < 10000; i++) {
		if (Bullets[i]) {
			delete Bullets[i];
			Bullets[i] = nullptr;
		}
	}
	delete[] Bullets;
}

void World::update(float deltaTime)
{
	if (m_DirectionalEnemy) {
		m_DirectionalEnemy->update(deltaTime, Bullets);
	}
}

void World::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix)
{
	if (m_DirectionalEnemy) {
		m_DirectionalEnemy->draw(deviceContext, orthoMatrix);
	}
	for (int i = 0; i < 10000; i++) {
		if (Bullets[i]) {
			Bullets[i]->draw(deviceContext, orthoMatrix);
		}
	}
}