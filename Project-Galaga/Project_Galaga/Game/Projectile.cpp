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

GameObject* Projectile::GetSender()
{
	return m_pSender;
}

void Projectile::HitLevel(const Vector2f& dMove)
{
	Delete();
}

void Projectile::HandleCollision(float dT)
{
	PolygonCollisionResult result;

	if (m_pSender == m_pGameObjectManager->GetPlayer())
	{
		for (GameObject* pGameObject : m_pGameObjectManager->GetEnemies())
		{
			result = sat::PolygonCollision(this, pGameObject);
			if (result.intersect)
			{
				static_cast<Enemy*>(pGameObject)->Hit(m_BaseDamage);
				Delete();
			}
		}
	}
	else
	{
		result = sat::PolygonCollision(this, m_pGameObjectManager->GetPlayer());
		if (result.intersect)
		{
			static_cast<Player*>(m_pGameObjectManager->GetPlayer())->Hit(m_BaseDamage);
			Delete();
		}
	}
}
