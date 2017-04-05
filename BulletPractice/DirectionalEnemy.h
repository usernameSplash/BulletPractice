#pragma once
#include "Enemy.h"

class DirectionalEnemy : public Enemy {
public :
	DirectionalEnemy() = delete;
	DirectionalEnemy(DirectionalEnemy &) = delete;
	DirectionalEnemy(ID3D11Device* device, Texture* texture, float x, float y, float angle, float angle_Rate, float speed, float speed_Rate, float interval);
	virtual ~DirectionalEnemy() override;

	virtual void update(float deltaTime, Bullet** Bullets) override;

private:
	Texture* m_BulletTexture;
	int m_BulletIndex;
	GameTimer* m_Timer;

	float m_Angle;
	float m_Angle_Rate;
	float m_Speed;
	float m_Speed_Rate;
	float m_Interval;
};