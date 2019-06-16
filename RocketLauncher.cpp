#include "pch.h"
#include "RocketLauncher.h"
#include "Rocket.h"

RocketLauncher::RocketLauncher(float width, float height, Sprite* pSprite, GameObject* pOwner, int level, const Slot& slot)
	: Weapon{ width, height, pSprite, pOwner, level, slot, 2 /*baseFireRate*/}
{
}


void RocketLauncher::Update(float dT)
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

void RocketLauncher::DoShoot(float dT)
{
	m_TimeSinceLastShot += dT;

	if (m_TimeSinceLastShot > 1.f / GetFireRate())
	{
		m_pGameObjectManager->Add(new Rocket{ GetAbsPos(), 5, 5, nullptr, GetAngle(), m_pOwner, m_Level });
		m_pResourceManager->GetSoundEffectp("SERocket")->SetVolume(5);
		m_pResourceManager->GetSoundEffectp("SERocket")->Play(0);
		m_TimeSinceLastShot = 0;
	}
}