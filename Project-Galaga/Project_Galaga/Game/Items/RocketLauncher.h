#pragma once
#include "Weapon.h"

class RocketLauncher : public Weapon
{
public:
	RocketLauncher(float widht, float height, Sprite* pSprite, GameObject* pOwner, int level, const Slot& slot);
	void Update(float dT) override;

private:
	void DoShoot(float dT) override;
};
