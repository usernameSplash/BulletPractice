#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet() = delete;
	Bullet(Bullet&) = delete;
	Bullet(ID3D11Device* device, Texture* texture, XMFLOAT2 position, XMFLOAT2 speed);
	virtual ~Bullet() override;

	virtual void update(float deltaTime);

	virtual void setPosition(float x, float y);
	virtual XMFLOAT3 getPosition() override;

	virtual void setSpeed(float x, float y);
	virtual XMFLOAT2 getSpeed();

	virtual bool shouldClose();
private:
	XMFLOAT2 m_Speed;
};