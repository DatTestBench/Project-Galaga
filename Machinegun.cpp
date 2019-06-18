#include "pch.h"
#include "MachineGun.h"
#include "Weapon.h"
#include "Projectile.h"
#include "MachineGunBullet.h"

Machinegun::Machinegun(float width, float height, Sprite* pSprite, GameObject* pOwner, int level, const Slot& slot)
	: Weapon{ width, height, pSprite, pOwner, level, slot, 10 /*baseFireRate*/}
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
		m_pResourceManager->PlaySoundEffect("SEBullet", 0, 5);
		m_TimeSinceLastShot = 0;
	}
}

