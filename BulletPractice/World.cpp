#include "World.h"

World::World(ID3D11Device* device):
	m_BulletTexture(new Texture(device, L"./Bullet.dds"))
{
	m_Bullet = new Bullet(device, m_BulletTexture, { 0,0 }, 0.0f, 0.25f, 500.0f, 1.0f);
	m_Bullet2 = new Bullet(device, m_BulletTexture, { 0,0 }, 90.0f, 0.25f, 500.0f, 1.0f);
	m_Bullet3 = new Bullet(device, m_BulletTexture, { 0,0 }, 180.0f, 0.25f, 500.0f, 1.0f);
	m_Bullet4 = new Bullet(device, m_BulletTexture, { 0,0 }, 270.0f, 0.25f, 500.0f, 1.0f);
}

World::~World()
{
	if (m_Bullet)
	{
		delete m_Bullet;
	}
	if (m_Bullet2)
	{
		delete m_Bullet2;
	}
	if (m_Bullet3)
	{
		delete m_Bullet3;
	}
	if (m_Bullet4)
	{
		delete m_Bullet4;
	}
	delete m_BulletTexture;
}

void World::update(float deltaTime)
{
	if (m_Bullet)
	{
		m_Bullet->update(deltaTime);
	}
	if (m_Bullet2)
	{
		m_Bullet2->update(deltaTime);
	}
	if (m_Bullet3)
	{
		m_Bullet3->update(deltaTime);
	}
	if (m_Bullet4)
	{
		m_Bullet4->update(deltaTime);
	}
}

void World::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix)
{
	if (m_Bullet)
	{
		m_Bullet->draw(deviceContext, orthoMatrix);
	}
	if (m_Bullet2)
	{
		m_Bullet2->draw(deviceContext, orthoMatrix);
	}
	if (m_Bullet3)
	{
		m_Bullet3->draw(deviceContext, orthoMatrix);
	}
	if (m_Bullet4)
	{
		m_Bullet4->draw(deviceContext, orthoMatrix);
	}
}