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
	: Projectile{ pos, width, height, pSprite, launchAngle, 10 /*baseSpeed*/, pSender, level, 100 /*baseDamage*/ }
	, m_Lifespan{ 10.f }
{
	m_MaxSpeed = 500;
	m_Mass = 50;
}

void Rocket::Update(float dT)
{
	HandleCollision(dT);
	HandleLogic(dT);
	m_pSteeringManager->Update(dT);
	m_pSteeringManager->Reset();
}

void Rocket::HandleLogic(float dT)
{

	// Object tracking
	GameObject* pClosestObj{ nullptr };
	float closestDist{ std::numeric_limits<float>::infinity() };
	if (m_pSender == m_pGameObjectManager->GetPlayer())
	{
		for (GameObject* pGameObject : m_pGameObjectManager->GetEnemies())
		{
			if (utils::DistPointPoint(m_Pos, pGameObject->GetPos()) < closestDist)
			{
				pClosestObj = pGameObject;
				closestDist = utils::DistPointPoint(m_Pos, pGameObject->GetPos());
			}
		}
	}
	else
	{
		pClosestObj = m_pGameObjectManager->GetPlayer();
	}


	// Behaviour without target
	if (pClosestObj != nullptr)
	{
		m_pSteeringManager->Pursuit(pClosestObj);
	}
	else if (m_pSender != nullptr)
	{
		m_pSteeringManager->Spin(m_pSender->GetPos(), 1000);
	}
	else
	{
		m_pSteeringManager->Goto(m_Pos + m_Velocity);
	}


	// Lifespan
	m_ElapsedLife += dT;

	if (m_ElapsedLife > m_Lifespan)
	{
		Delete();
	}

}