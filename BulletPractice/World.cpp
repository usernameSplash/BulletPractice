#include "World.h"
#include <cstdio>

World::World(ID3D11Device* device) :
	m_EnemyTexture(new Texture(device, L"./Enemy.dds")),
//	m_DirectionalEnemy(new DirectionalEnemy(device, m_EnemyTexture, -960.0f + 64.0f, 540.0f - 64.0f, 335.0f, 0.0f, 500.0f, 0.0f, 0.1f)),
//	m_SpiralEnemy(new SpiralEnemy(device, m_EnemyTexture, 0.0f, 0.0f, 0.0f, 10.0f, 500.0f, 0.0f, 0.1f)),
	m_MultipleSpiralEnemy(new MultipleSpiralEnemy(device, m_EnemyTexture, 0.0f, 0.0f, 0.0f, 10.0f, 500.0f, 0.0f, 0.1f, 8)),
	Bullets(new Bullet*[10000])
{
	for (int i = 0; i < 10000; i++) {
		Bullets[i] = nullptr;
	}
}

World::~World()
{
	delete m_EnemyTexture;
//	delete m_DirectionalEnemy;
//	delete m_SpiralEnemy;
	delete m_MultipleSpiralEnemy;
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
//	if (m_DirectionalEnemy) {
//		m_DirectionalEnemy->update(deltaTime, Bullets);
//	}
//	if (m_SpiralEnemy) {
//		m_SpiralEnemy->update(deltaTime, Bullets);
//	}
	if (m_MultipleSpiralEnemy) {
		m_MultipleSpiralEnemy->update(deltaTime, Bullets);
	}
}

void World::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix)
{
//	if (m_DirectionalEnemy) {
//		m_DirectionalEnemy->draw(deviceContext, orthoMatrix);
//	}
//	if (m_SpiralEnemy) {
//		m_SpiralEnemy->draw(deviceContext, orthoMatrix);
//	}
	if (m_MultipleSpiralEnemy) {
		m_MultipleSpiralEnemy->draw(deviceContext, orthoMatrix);
	}
	for (int i = 0; i < 10000; i++) {
		if (Bullets[i]) {
			Bullets[i]->draw(deviceContext, orthoMatrix);
		}
	}
}