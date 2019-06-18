#include "pch.h"
#include "Projectile.h"
#include "utils.h"
#include "GameObjectManager.h"
#include "Enemy.h"
#include "SAT.h"
#include "MachineGunBullet.h"
#include "ShotgunPellet.h"
#include "Rocket.h"
#include "Player.h"
#include "SteeringManager.h"
#include "Rocketeer.h"
#include "Rusher.h"
#include "Gunner.h"
Projectile::Projectile(const Vector2f& pos, float width, float height, Sprite* pSprite, float launchAngle, float baseSpeed, GameObject* pSender, int level, float baseDamage)
	: GameObject{ pos, width, height, pSprite }
	, m_pSender{ pSender }
	, m_BaseSpeed{ baseSpeed }
	, m_Level{ level }
	, m_BaseDamage{ baseDamage }

{
	m_Speed = m_BaseSpeed;
	m_Angle = launchAngle;
	m_Velocity = Vector2f{ m_Speed * cos(m_Angle), m_Speed * sin(m_Angle) };
}

void Projectile::Update(float dT)
{

	HandleCollision(dT);

	m_Pos += m_Velocity * dT;
}

void Projectile::Draw() const
{
	if (typeid (*this) == typeid(Rocket))
	{
		utils::SetColor(Color4f{ 1,0,0,1 });
	}
	if (typeid (*this) == typeid(ShotgunPellet))
	{
		utils::SetColor(Color4f{ 255.f,69.f,0,1 });
	}
	if (typeid (*this) == typeid(MachinegunBullet))
	{
		utils::SetColor(Color4f{ 1,1,0,1 });
	}
	utils::FillPolygon(GetCollider());
}

void Projectile::HitLevel(const Vector2f& dMove)
{
	Delete();
}

void Projectile::HandleCollision(float dT)
{
	PolygonCollisionResult result;
	for (GameObject* pGameObject : *m_pGameObjectManager->GetGameObjects())
	{
		if (m_pSender != nullptr && m_pSender->GetFlag() == false && pGameObject != nullptr && pGameObject->GetFlag() == false)
		{
			if (typeid(*m_pSender) == typeid(Player))
			{
				if (typeid(*pGameObject) == typeid (Rocketeer) || typeid(*pGameObject) == typeid (Rusher) || typeid(*pGameObject) == typeid (Gunner))
				{
					result = sat::PolygonCollision(this, pGameObject);
					if (result.intersect)
					{
						static_cast<Enemy*>(pGameObject)->Hit(m_BaseDamage);
						Delete();
					}
				}
			}
			else if (typeid(*m_pSender) == typeid (Rocketeer) || typeid(*m_pSender) == typeid (Rusher) || typeid(*m_pSender) == typeid (Gunner) || typeid(*m_pSender) == typeid (Enemy))
			{
				if (typeid(*pGameObject) == typeid(Player))
				{
					result = sat::PolygonCollision(this, pGameObject);
					if (result.intersect)
					{
						static_cast<Player*>(pGameObject)->Hit(m_BaseDamage);

						Delete();
					}
				}
			}
		}
	}
}
