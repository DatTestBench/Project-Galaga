#include "pch.h"
#include "Rocket.h"
#include "ShotgunPellet.h"
#include "MachinegunBullet.h"
#include "utils.h"
#include "Projectile.h"
#include "utils.h"
#include "SteeringManager.h"
#include "Player.h"
#include "Rocketeer.h"
#include "Rusher.h"
#include "Gunner.h"
Rocket::Rocket(const Vector2f& pos, float width, float height, Sprite* pSprite, float launchAngle, GameObject* pSender, int level)
	: Projectile{ pos, width, height, pSprite, launchAngle, 0 /*baseSpeed*/, pSender, level, 100 /*baseDamage*/ }
	, m_Lifespan{ 50.f }
{
	m_MaxSpeed = 500;
	m_Mass = 50;
}

void Rocket::Update(float dT)
{

	HandleCollision(dT);
	HandleLogic(dT);
	//m_Pos += GetVelocity() * dT;
}

void Rocket::HandleLogic(float dT)
{
	GameObject* pClosestObj{ nullptr };
	float closestDist{ std::numeric_limits<float>::infinity() };





	for (GameObject* pGameObject : *m_pGameObjectManager->GetGameObjects())
	{
		if (pGameObject != nullptr && pGameObject->GetFlag() == false && m_pSender != nullptr && m_pSender->GetFlag() == false)
		{
			if (utils::DistPointPoint(m_Pos, pGameObject->GetPos()) < closestDist)
			{
				if (typeid (*m_pSender) == typeid(Player))
				{
					if (typeid (*pGameObject) == typeid(Rocketeer) || typeid (*pGameObject) == typeid(Rusher) || typeid (*pGameObject) == typeid(Gunner))
					{
						pClosestObj = pGameObject;
						closestDist = utils::DistPointPoint(m_Pos, pGameObject->GetPos());
					}
				}

				else if (typeid (*m_pSender) == typeid(Rocketeer) || typeid (*m_pSender) == typeid(Rusher) || typeid (*m_pSender) == typeid(Gunner))
				{
					if (typeid(*pGameObject) == typeid(Player))
					{
						pClosestObj = pGameObject;
						closestDist = utils::DistPointPoint(m_Pos, pGameObject->GetPos());
					}
				}
			}
		}
	}

	m_pSteeringManager->Pursuit(pClosestObj);

	m_pSteeringManager->Update(dT);

	m_pSteeringManager->Reset();
}