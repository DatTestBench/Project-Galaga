#include "pch.h"
#include "Gunner.h"
#include "utils.h"
#include "Machinegun.h"
Gunner::Gunner(const Vector2f& pos, float width, float height, Sprite* pSprite, int level, float baseHealth)
	: Enemy{ pos, width, height, pSprite, level, baseHealth }
{
	Machinegun* pWeapon = new Machinegun{ 10, 10, nullptr, this, 1, Slot(m_pWeapons.size()) };
	m_pWeapons.push_back(pWeapon);
	m_MaxSpeed = 300;
}

void Gunner::Update(float dT)
{
	HandleLogic(dT);
	HandleCollision(dT);
	m_pSteeringManager->Update(dT);
	m_pSteeringManager->Reset();
}

void Gunner::HandleLogic(float dT)
{
	Vector2f eToPVector(m_Pos, m_pPlayer->GetPos());



	
	if (!IsShooting())
	{
		if (utils::DistPointPoint(m_pPlayer->GetPos(), m_Pos) < 500)
		{
			
				ToggleShoot();
				//std::cout << "Shoot" << std::endl;
		}
	}
	else
	{
		if ( utils::DistPointPoint(m_pPlayer->GetPos(), m_Pos) > 500)
		{
			ToggleShoot();
			//std::cout << "No Shoot" << std::endl;
		}
	}
	for (Weapon* pWeapon : m_pWeapons)
	{
		pWeapon->Update(dT);
	}


	if (utils::DistPointPoint(m_pPlayer->GetPos(), m_Pos) < 500)
	{

		m_pSteeringManager->Pursuit(m_pPlayer);

	}
	else
	{
		m_pSteeringManager->Wander(dT);
	}

	m_pSteeringManager->CollisionEvade(m_pLevel->GetPoint2fVertices());
	
}