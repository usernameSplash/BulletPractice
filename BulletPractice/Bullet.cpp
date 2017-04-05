#include "Bullet.h"
#include "GameConstant.h"
#include <xnamath.h>

Bullet::Bullet(ID3D11Device* device, Texture* texture, XMFLOAT2 position, float angle, float angle_rate, float speed, float speed_rate) :
	GameObject(device, texture, 16, 16), m_Angle(angle), m_Angle_rate(angle_rate), m_Speed(speed), m_Speed_rate(speed_rate)
{
	setPosition(position.x, position.y);
}

Bullet::~Bullet()
{

}

void Bullet::update(float deltaTime)
{
	float x = getPosition().x + m_Speed*cosf(XMConvertToRadians(m_Angle)) * deltaTime;
	float y = getPosition().y + m_Speed*sinf(XMConvertToRadians(m_Angle)) * deltaTime;

	m_Angle += m_Angle_rate;
	m_Speed += m_Speed_rate;
	
	setPosition(x, y);
}

void Bullet::setPosition(float x, float y)
{
	GameObject::setPosition(x, y, 1.0f);
}

XMFLOAT3 Bullet::getPosition()
{
	return GameObject::getPosition();
}

void Bullet::setSpeed(float speed)
{
	m_Speed = speed;
}

float Bullet::getSpeed()
{
	return m_Speed;
}

bool Bullet::shouldClose()
{
	float x = getPosition().x;
	float y = getPosition().y;
	float left = -GameConstant::GameWidth / 2;
	float right = GameConstant::GameWidth / 2;
	float top = GameConstant::GameHeight / 2;
	float bottom = -GameConstant::GameHeight / 2;

	if (x < left) return true;
	if (right < x) return true;
	if (y < bottom) return true;
	if (top < y) return true;

	return false;
}

