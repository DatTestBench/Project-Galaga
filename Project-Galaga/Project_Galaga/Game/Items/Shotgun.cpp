#include "Items/Weapon.h"
#include "Items/Shotgun.h"
#include "Items/ShotgunPellet.h"
#include "Helpers/utils.h"

Shotgun::Shotgun(const float width, const float height, Sprite* pSprite, GameObject* pOwner, const int level, const Slot& slot)
	: Weapon{ width, height, pSprite, pOwner, level, slot, 1.f }
{
}

void Shotgun::Update(const float dT)
{
	if (m_IsShooting)
		DoShoot(dT);
	else
		m_TimeSinceLastShot += dT;
}

void Shotgun::DoShoot(const float dT)
{
	m_TimeSinceLastShot += dT;

	if (m_TimeSinceLastShot > 1.f / GetFireRate())
	{
		m_pGameObjectManager->Add(new ShotgunPellet{ GetAbsPos(), 3.f, 3.f, nullptr, GetAngle() - utils::g_Pi / 6, m_pOwner, m_Level });
		m_pGameObjectManager->Add(new ShotgunPellet{ GetAbsPos(), 3.f, 3.f, nullptr, GetAngle(), m_pOwner, m_Level });
		m_pGameObjectManager->Add(new ShotgunPellet{ GetAbsPos(), 3.f, 3.f, nullptr, GetAngle() + utils::g_Pi / 6, m_pOwner, m_Level });
		m_TimeSinceLastShot = 0;

		// Todo: fix the casting fuckery
		if (m_pOwner == reinterpret_cast<GameObject*>(m_pGameObjectManager->GetPlayer()))
			m_pResourceManager->PlaySoundEffect("SEPellet", 0, 5);
		else
			m_pResourceManager->PlaySoundEffect("SEPellet", 0, 2);

		m_TimeSinceLastShot = 0;
	}
}
