#include "Enemy.h"
#include "Bullet.h"
#include "GameState.h"
#include "World.h"
#include <xnamath.h>

Enemy::Enemy(ID3D11Device* device, Texture* texture, float x, float y, float interval)
	: GameObject(device, texture, 32, 32), BulletTexture(new Texture (device, L"./Bullet.dds")),
	m_Timer(new GameTimer()), m_BulletIndex(0), m_Interval(interval)
{
	setPosition(x, y);
}

Enemy::~Enemy() {
	delete BulletTexture;
	delete m_Timer;
}

void Enemy::update(float deltaTime) {

}

void Enemy::update(float deltaTime, Bullet** Bullets) {
	m_Timer->Tick();
	if (deltaTime >= 0.1) {
		return;
	}

	if (m_Timer->TotalTime() >= m_Interval) {
		for (int i = 0; i < 4; i++) {
			while (Bullets[m_BulletIndex]) m_BulletIndex++;
			Bullets[m_BulletIndex] = new Bullet(GameState::graphics->getDevice(), BulletTexture, { getPosition().x, getPosition().y }, 90 * i, 0, 500, 0);
			m_BulletIndex = m_BulletIndex % 10000;
		}
		m_Timer->Reset();
	}
	
	for (int i = 0; i < 10000; i++) {
		if (Bullets[i]) {
			Bullets[i]->Bullet::update(deltaTime);
		}
		if (Bullets[i]) {
			if (Bullets[i]->shouldClose()) {
				delete Bullets[i];
				Bullets[i] = nullptr;
			}
		}
	}
}

void Enemy::setPosition(float x, float y)
{
	GameObject::setPosition(x, y, 1.0f);
}

XMFLOAT3 Enemy::getPosition()
{
	return GameObject::getPosition();
}