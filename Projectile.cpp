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
#include "Steering.h"
Projectile::Projectile(const Vector2f& pos, float width, float height, Sprite* pSprite, float launchAngle, float baseSpeed, GameObject* pSender, int level, float baseDamage)
	: GameObject{ pos, width, height, pSprite }
	, m_pSender{ pSender }
	, m_BaseSpeed{ baseSpeed }
	, m_Level{ level }
	, m_BaseDamage{ baseDamage }

{
	m_Speed = m_BaseSpeed;
	m_Angle = launchAngle;
	//m_Velocity = Vector2f{ m_Speed * cos(m_Angle), m_Speed * sin(m_Angle) };
}

void Projectile::Update(float dT)
{

	HandleCollision(dT);

	//m_Pos += m_Velocity * dT;
}

void Projectile::Draw() const
{
	utils::DrawPolygon(GetCollider());
}

void Projectile::HandleCollision(float dT)
{
	PolygonCollisionResult result;
	for (GameObject* pGameObject : *m_pGameObjectManager->GetGameObjects())
	{
		//Temporary check, so the enemies can't shoot eachother
		if (typeid(*pGameObject) != typeid(*m_pSender))
		{
			if (pGameObject != m_pSender && pGameObject != this && typeid(*pGameObject) != typeid (MachinegunBullet) && typeid (*pGameObject) != typeid (ShotgunPellet) && typeid(*pGameObject) != typeid (Rocket))
			{
				result = sat::PolygonCollision(this, pGameObject);

				if (result.Intersect)
				{
					if (typeid(*pGameObject) == typeid(Player))
						static_cast<Player*>(pGameObject)->Hit(m_BaseDamage);
					else
					{
						static_cast<Enemy*>(pGameObject)->Hit(m_BaseDamage);
					}
					Delete();
					return;
				}
			}
		}
	}

	if (m_Pos.x > 2000 || m_Pos.x < 0 || m_Pos.y > 2000 || m_Pos.x < 0)
	{
		Delete();
		return;
	}


}