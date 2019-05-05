#pragma once
#include "Weapon.h"
class Shotgun : public Weapon
{
public:
	Shotgun(float width, float height, Texture* pTexture, GameObject* pOwner, int level, const Slot& slot);
	void Update(float dT) override;

private:
	void DoShoot(float dT) override;
};

