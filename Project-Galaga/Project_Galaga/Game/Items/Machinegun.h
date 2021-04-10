#pragma once
#include "Weapon.h"

class Machinegun final : public Weapon
{
public:
	explicit Machinegun(float width, float height, Sprite* pSprite, GameObject* pOwner, int level, const Slot& slot);
	void Update(float dT) override;

private:
	void DoShoot(float dT) override;
};
