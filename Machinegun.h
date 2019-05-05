#pragma once
#include "Weapon.h"

class Machinegun : public Weapon
{
public:
	Machinegun(float width, float height, Texture* pTexture, GameObject* pOwner, int level, const Slot& slot);
	void Update(float dT) override;

private:
	void DoShoot(float dT) override;
};

