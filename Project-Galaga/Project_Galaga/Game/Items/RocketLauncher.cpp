#include "Items/RocketLauncher.h"
#include "Items/Rocket.h"

RocketLauncher::RocketLauncher(const float width, const float height, Sprite* pSprite, GameObject* pOwner, const int level, const Slot& slot)
	: Weapon{ width, height, pSprite, pOwner, level, slot, 2.f }
{
}

void RocketLauncher::Update(const float dT)
{
	if (m_IsShooting)
		DoShoot(dT);
	else
		m_TimeSinceLastShot += dT;
}

void RocketLauncher::DoShoot(const float dT)
{
	m_TimeSinceLastShot += dT;

	if (m_TimeSinceLastShot > 1.f / GetFireRate())
	{
		m_pGameObjectManager->Add(new Rocket{ GetAbsPos(), 5, 5, nullptr, GetAngle(), m_pOwner, m_Level });
		// Todo: fix the casting fuckery
		if (m_pOwner == reinterpret_cast<GameObject*>(m_pGameObjectManager->GetPlayer()))
			m_pResourceManager->PlaySoundEffect("SERocket", 0, 5);
		else
			m_pResourceManager->PlaySoundEffect("SERocket", 0, 2);

		m_TimeSinceLastShot = 0;
	}
}
