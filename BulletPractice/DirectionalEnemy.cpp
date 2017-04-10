#include "DirectionalEnemy.h"

DirectionalEnemy::DirectionalEnemy(ID3D11Device* device, Texture* texture, float x, float y, 
	float angle, float angle_Rate, float speed, float speed_Rate, float interval) :
	Enemy(device, texture, x, y, angle, angle_Rate, speed, speed_Rate, interval),
	m_Angle(angle), m_Angle_Rate(angle_Rate), m_Speed(speed), m_Speed_Rate(speed_Rate), m_Interval(interval),
	m_BulletTexture(new Texture(device, L"./res/Bullet.dds")),
	m_Timer(new GameTimer()),
	m_BulletIndex(0)
{

}

DirectionalEnemy::~DirectionalEnemy() {
	
}

void DirectionalEnemy::update(float deltaTime) {

}