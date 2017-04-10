#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet() = delete;
	Bullet(Bullet&) = delete;
	Bullet(ID3D11Device* device, Texture* texture, XMFLOAT2 position, float angle, float angle_rate, float speed, float speed_rate);
	virtual ~Bullet() override;

	virtual void update(float deltaTime);

	virtual void setPosition(float x, float y);
	virtual XMFLOAT3 getPosition() override;

	virtual void setSpeed(float speed);
	virtual float getSpeed();

	virtual bool shouldClose();
private:
	float m_Speed;
	float m_Speed_rate;
	float m_Angle;
	float m_Angle_rate;
	float m_Direction_rate;
};