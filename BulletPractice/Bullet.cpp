#include "Bullet.h"
#include "GameConstant.h"

Bullet::Bullet(ID3D11Device* device, Texture* texture, XMFLOAT2 position, XMFLOAT2 speed) :
	GameObject(device, texture, 32, 32),
	m_Speed(speed)
{
	setPosition(position.x, position.y);
}

Bullet::~Bullet()
{

}

void Bullet::update(float deltaTime)
{
	float x = getPosition().x + m_Speed.x * deltaTime;
	float y = getPosition().y + m_Speed.y * deltaTime;

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

void Bullet::setSpeed(float x, float y)
{
	m_Speed.x = x;
	m_Speed.y = y;
}

XMFLOAT2 Bullet::getSpeed()
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
	if (x < bottom) return true;
	if (top < x) return true;

	return false;
}

