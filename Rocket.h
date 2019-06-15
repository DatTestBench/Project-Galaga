#pragma once
#include "Projectile.h"

class Rocket : public Projectile
{
public:
	Rocket(const Vector2f& pos, float width, float height, Sprite* pSprite, float launchAngle, GameObject* pSender, int level);
	void Update (float dT) override;

private:
	void HandleLogic(float dT) override;
	const float m_Lifespan;
};

