#include "pch.h"
#include "MachineGun.h"
#include "Weapon.h"
#include "Projectile.h"
#include "MachineGunBullet.h"

Machinegun::Machinegun(GameObject* pOwner, float width, float height, const Slot& slot, float fireRate, Texture* pTexture)
	: Weapon{ pOwner, width, height, slot, fireRate, pTexture }
{
}

void Machinegun::Update(float dT)
{
	if (m_IsShooting)
	{
		DoShoot(dT);
	}
	else
	{
		m_TimeSinceLastShot += dT;
	}
}


void Machinegun::DoShoot(float dT)
{
	m_TimeSinceLastShot += dT;

	if (m_TimeSinceLastShot > 1.f / m_FireRate)
	{
		m_pGameObjectManager->Add(new MachinegunBullet{ m_pOwner, GetAbsPos(), GetAngle() });
		m_TimeSinceLastShot = 0;
	}
}

