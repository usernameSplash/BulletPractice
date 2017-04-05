#include "World.h"
#include <cstdio>

World::World(ID3D11Device* device):
	m_EnemyTexture(new Texture(device, L"./Enemy.dds")),
	m_Enemy(new Enemy(device, m_EnemyTexture, 0.0f, 0.0f, 0.1f)),
	Bullets(new Bullet*[10000])
{
	for (int i = 0; i < 10000; i++) {
		Bullets[i] = nullptr;
	}
}

World::~World()
{
	delete m_EnemyTexture;
	delete m_Enemy;
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
	if (m_Enemy) {
		m_Enemy->update(deltaTime, Bullets);
	}
}

void World::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix)
{
	if (m_Enemy) {
		m_Enemy->draw(deviceContext, orthoMatrix);
	}
	for (int i = 0; i < 10000; i++) {
		if (Bullets[i]) {
			Bullets[i]->draw(deviceContext, orthoMatrix);
		}
	}
}