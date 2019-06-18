#include "pch.h"
#include "Rocketeer.h"
#include "utils.h"
#include "RocketLauncher.h"
Rocketeer::Rocketeer(const Vector2f& pos, float width, float height, Sprite* pSprite, int level, float baseHealth)
	: Enemy{ pos, width, height, pSprite, level, baseHealth }
{
	RocketLauncher* pWeapon = new RocketLauncher{ 10, 10, nullptr, this, 1, Slot(m_pWeapons.size()) };
	m_pWeapons.push_back(pWeapon);
	m_MaxSpeed = 200;
}

void Rocketeer::Update(float dT)
{
	HandleLogic(dT);
	HandleCollision(dT);
}

void Rocketeer::HandleLogic(float dT)
{
	Vector2f eToPVector(m_Pos, m_pPlayer->GetPos());
	HandleCollision(dT);

	if (!IsShooting())
	{
		if (utils::DistPointPoint(m_pPlayer->GetPos(), m_Pos) < 600 && utils::DistPointPoint(m_pPlayer->GetPos(), m_Pos) > 100)
		{
			ToggleShoot();
			std::cout << "Shoot" << std::endl;
		}
	}
	else
	{
		if (utils::DistPointPoint(m_pPlayer->GetPos(), m_Pos) > 700 || utils::DistPointPoint(m_pPlayer->GetPos(), m_Pos) < 100)
		{
			ToggleShoot();
			std::cout << "No Shoot" << std::endl;
		}
	}

	for (Weapon* pWeapon : m_pWeapons)
		pWeapon->Update(dT);



	if (utils::DistPointPoint(m_pPlayer->GetPos(), m_Pos) > 200)
	{
		m_pSteeringManager->Seek(m_pPlayer);

	}
	else
	{
		m_pSteeringManager->Goto(Vector2f{ 750, 750 });

	}
	m_pSteeringManager->Update(dT);
	m_pSteeringManager->Reset();
}