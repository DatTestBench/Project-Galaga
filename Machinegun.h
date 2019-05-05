#pragma once
#include "Weapon.h"

class Machinegun : public Weapon
{
public:
	Machinegun(GameObject* pOwner, float width, float height, const Slot& slot, float fireRate = { 10 }, Texture* pTexture = { nullptr });
	void Update(float dT) override;

private:
	void DoShoot(float dT) override;
};

