#include "Items/MachineGun.h"
#include "Items/MachineGunBullet.h"

Machinegun::Machinegun(const float width, const float height, Sprite* pSprite, GameObject* pOwner, const int level, const Slot& slot)
	: Weapon{ width, height, pSprite, pOwner, level, slot, 10 }
{
}

void Machinegun::Update(const float dT)
{
	if (m_IsShooting)
		DoShoot(dT);
	else
		m_TimeSinceLastShot += dT;
}


void Machinegun::DoShoot(const float dT)
{
	m_TimeSinceLastShot += dT;

	if (m_TimeSinceLastShot > 1.f / GetFireRate())
	{
		m_pGameObjectManager->Add(new MachinegunBullet{ GetAbsPos(), 3, 3, nullptr, GetAngle(), m_pOwner, m_Level });
		// todo fix the casting fuckery
		if (m_pOwner == reinterpret_cast<GameObject*>(m_pGameObjectManager->GetPlayer()))
			m_pResourceManager->PlaySoundEffect("SEBullet", 0, 5);
		else
			m_pResourceManager->PlaySoundEffect("SEBullet", 0, 2);

		m_TimeSinceLastShot = 0;
	}
}
