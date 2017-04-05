#include "World.h"

World::World(ID3D11Device* device):
	m_BulletTexture(new Texture(device, L"./Bullet.dds"))
{
	m_Bullet = new Bullet(device, m_BulletTexture, { 0,0 }, 0.0f, 1.0f, 0.0f, 1.0f);
}

World::~World()
{
	if (m_Bullet)
	{
		delete m_Bullet;
	}
	delete m_BulletTexture;
}

void World::update(float deltaTime)
{
	if (m_Bullet)
	{
		m_Bullet->update(deltaTime);
	}
}

void World::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix)
{
	if (m_Bullet)
	{
		m_Bullet->draw(deviceContext, orthoMatrix);
	}
}