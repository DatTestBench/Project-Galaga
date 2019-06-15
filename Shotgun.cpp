#include "pch.h"
#include "Weapon.h"
#include "Shotgun.h"
#include "ShotgunPellet.h"
#include "utils.h"

Shotgun::Shotgun(float width, float height, Sprite* pSprite, GameObject* pOwner, int level, const Slot& slot)
	: Weapon { width, height, pSprite, pOwner, level, slot, 1.f }
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

	if (m_TimeSinceLastShot > 1.f / GetFireRate())
	{
		m_pGameObjectManager->Add(new ShotgunPellet{ GetAbsPos(), 3.f, 3.f, nullptr, GetAngle() - utils::g_Pi / 6, m_pOwner, m_Level });
		m_pGameObjectManager->Add(new ShotgunPellet{ GetAbsPos(), 3.f, 3.f, nullptr, GetAngle(), m_pOwner, m_Level });
		m_pGameObjectManager->Add(new ShotgunPellet{ GetAbsPos(), 3.f, 3.f, nullptr, GetAngle() + utils::g_Pi / 6, m_pOwner, m_Level });
		m_TimeSinceLastShot = 0;
	}
}