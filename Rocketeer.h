#pragma once
#include "Enemy.h"
class Rocketeer : public Enemy
{
public:
	Rocketeer(const Vector2f& pos, float width, float height, Sprite* pSprite, int level, float baseHealth);
	void Update(float dT) override;

private:
	// Data Members


	// Member Functions
	void HandleLogic(float dT) override;
};

