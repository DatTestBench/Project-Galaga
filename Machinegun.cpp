#include "pch.h"
#include "MachineGun.h"
#include "Weapon.h"
#include "Projectile.h"
#include "MachineGunBullet.h"

Machinegun::Machinegun(float width, float height, Texture* pTexture, GameObject* pOwner, int level, const Slot& slot)
	: Weapon{ width, height, pTexture, pOwner, level, slot, 30 /*baseFireRate*/}
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

	if (m_TimeSinceLastShot > 1.f / GetFireRate())
	{
		m_pGameObjectManager->Add(new MachinegunBullet{ GetAbsPos(), 3, 3, nullptr, GetAngle(), m_pOwner, m_Level });
		m_TimeSinceLastShot = 0;
	}
}

