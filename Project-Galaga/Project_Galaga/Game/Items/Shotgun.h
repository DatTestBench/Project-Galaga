#pragma once
#include "Weapon.h"

class Shotgun final : public Weapon
{
public:
	Shotgun(float width, float height, Sprite* pSprite, GameObject* pOwner, int level, const Slot& slot);
	void Update(float dT) override;

private:
	void DoShoot(float dT) override;
};
