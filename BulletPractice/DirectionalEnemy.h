#pragma once
#include "Enemy.h"
#include "GameState.h"

class DirectionalEnemy : public Enemy {
public:
	DirectionalEnemy() = delete;
	DirectionalEnemy(DirectionalEnemy&) = delete;
	DirectionalEnemy(ID3D11Device* device, Texture* texture, float x, float y, float angle, float angle_Rate, float speed, float speed_Rate, float interval);
	virtual ~DirectionalEnemy() override;

	virtual void update(float deltaTime) override;

private:
	int m_BulletIndex;
	GameTimer* m_Timer;
	Texture* m_BulletTexture;
	
	float m_Angle;
	float m_Angle_Rate;
	float m_Speed;
	float m_Speed_Rate;
	float m_Interval;	
};