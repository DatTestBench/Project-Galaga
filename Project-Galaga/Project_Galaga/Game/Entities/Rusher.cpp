#include "Entities/Rusher.h"
#include "Helpers/utils.h"
#include "Items/Shotgun.h"
Rusher::Rusher(const Vector2f& pos, float width, float height, Sprite* pSprite, int level, float baseHealth)
	: Enemy{ pos, width, height, pSprite, level, baseHealth }
{
	Shotgun* pWeapon = new Shotgun{ 10, 10, nullptr, this, 1, Slot(m_pWeapons.size()) };
	m_pWeapons.push_back(pWeapon);
	m_MaxSpeed = 400;
}

void Rusher::Update(float dT)
{
	HandleLogic(dT);
	HandleCollision(dT);
	m_pSprite->Update(dT);
}

void Rusher::HandleLogic(float dT)
{
	Vector2f eToPVector(m_Pos, m_pPlayer->GetPos());

	if (!IsShooting())
	{
		if (utils::DistPointPoint(m_pPlayer->GetPos(), m_Pos) < 150)
		{
			ToggleShoot();
			//std::cout << "Shoot" << std::endl;
		}
	}
	else
	{
		if (utils::DistPointPoint(m_pPlayer->GetPos(), m_Pos) > 150)
		{
			ToggleShoot();
			//std::cout << "No Shoot" << std::endl;
		}
	}

	for (Weapon* pWeapon : m_pWeapons)
	{
		pWeapon->Update(dT);
	}


	m_pSteeringManager->Pursuit(m_pPlayer);

	m_pSteeringManager->Update(dT);
	m_pSteeringManager->Reset();
}
