#pragma once
#include "Weapon.h"
class Shotgun : public Weapon
{
public:
	Shotgun(GameObject* pOwner, float width, float height, const Slot& slot, float fireRate = { 1 }, Texture* pTexture = { nullptr });
	void Update(float dT) override;

private:
	void DoShoot(float dT) override;
};

