#pragma once
#include "GameObject.h"
#include "GameTimer.h"
#include "Bullet.h"

class Enemy : public GameObject {

public:
	Enemy() = delete;
	Enemy(Enemy&) = delete;
	Enemy(ID3D11Device* device, Texture* texture, float x, float y);
	virtual ~Enemy() override;

	virtual void update(float deltaTime) override;
	virtual void update(float deltaTime, Bullet** Bullets);

	virtual void setPosition(float x, float y);
	virtual XMFLOAT3 getPosition() override;

};