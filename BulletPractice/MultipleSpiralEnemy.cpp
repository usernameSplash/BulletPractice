#include "MultipleSpiralEnemy.h"
#include "Bullet.h"
#include "GameState.h"
#include "World.h"
#include <xnamath.h>

MultipleSpiralEnemy::MultipleSpiralEnemy(ID3D11Device* device, Texture* texture,
	float x, float y, float angle, float angle_Rate, float speed, float speed_Rate, float interval, int count) :
	Enemy(device, texture, x, y, angle, angle_Rate, speed, speed_Rate, interval),
	m_BulletTexture(new Texture(device, L"./Bullet.dds")), m_Timer(new GameTimer()),
	m_BulletIndex(0), m_Angle(angle), m_Angle_Rate(angle_Rate), m_Speed(speed), m_Speed_Rate(speed_Rate), m_Interval(interval), m_Count(count)
{
	setPosition(x, y);
}

MultipleSpiralEnemy::~MultipleSpiralEnemy() {
	delete m_Timer;
	delete m_BulletTexture;
}

void MultipleSpiralEnemy::update(float deltaTime, Bullet** Bullets) {
	m_Timer->Tick();
	if (deltaTime >= 0.05) {
		deltaTime = 0.05;
	}

	if (m_Timer->TotalTime() >= m_Interval) {
		while (Bullets[m_BulletIndex]) {
			m_BulletIndex++;
		}
		for (int i = 0; i < m_Count; i++) {
			Bullets[m_BulletIndex + i] = new Bullet(GameState::graphics->getDevice(), m_BulletTexture, { getPosition().x, getPosition().y }, m_Angle+(float)(i*360/m_Count), 1.5f, m_Speed, 0.0f);	
		}
		m_Angle += m_Angle_Rate;
		m_BulletIndex = m_BulletIndex % 10000;

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