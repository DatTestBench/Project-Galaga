#include "pch.h"
#include "Weapon.h"
#include "Shotgun.h"
#include "ShotgunPellet.h"
#include "utils.h"

Shotgun::Shotgun(GameObject* pOwner, float width, float height, const Slot& slot, float fireRate, Texture* pTexture)
	: Weapon { pOwner, width, height, slot, fireRate, pTexture }
{
}

void Shotgun::Update(float dT)
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

void Shotgun::DoShoot(float dT)
{
	m_TimeSinceLastShot += dT;

	if (m_TimeSinceLastShot > 1.f / m_FireRate)
	{
		m_pGameObjectManager->Add(new ShotgunPellet{ m_pOwner, GetAbsPos(), GetAngle() - utils::g_Pi / 6 });
		m_pGameObjectManager->Add(new ShotgunPellet{ m_pOwner, GetAbsPos(), GetAngle() });
		m_pGameObjectManager->Add(new ShotgunPellet{ m_pOwner, GetAbsPos(), GetAngle() + utils::g_Pi / 6 });
		m_TimeSinceLastShot = 0;
	}
}