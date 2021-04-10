#pragma once
#include "Weapon.h"

class RocketLauncher final : public Weapon
{
public:
	RocketLauncher(float width, float height, Sprite* pSprite, GameObject* pOwner, int level, const Slot& slot);
	void Update(float dT) override;

private:
	void DoShoot(float dT) override;
};
