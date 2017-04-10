#include "Enemy.h"
#include "Bullet.h"
#include "GameState.h"
#include "World.h"
#include <xnamath.h>

Enemy::Enemy(ID3D11Device* device, Texture* texture, float x, float y, float angle, float angle_Rate, float speed, float speed_Rate, float interval)
	: GameObject(device, texture, 32, 32)
{
	setPosition(x, y);
}

Enemy::~Enemy(){

}

void Enemy::update(float deltaTime) {

}

void Enemy::update(float deltaTime, Bullet** Bullets) {

}

void Enemy::setPosition(float x, float y)
{
	GameObject::setPosition(x, y, 1.0f);
}

XMFLOAT3 Enemy::getPosition()
{
	return GameObject::getPosition();
}