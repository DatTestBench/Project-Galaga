#include "Items/Projectile.h"
#include "Entities/Enemy.h"
#include "Entities/Player.h"
#include "Helpers/SAT.h"
#include "Helpers/utils.h"
#include "Items/MachineGunBullet.h"
#include "Items/Rocket.h"
#include "Items/ShotgunPellet.h"

Projectile::Projectile(const Vector2f& pos, const float width, const float height, Sprite* pSprite, const float launchAngle, const float baseSpeed, GameObject* pSender, const int level, const float baseDamage)
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

void Projectile::Update(const float dT)
{
	HandleCollision(dT);

	m_Pos += m_Velocity * dT;
}

void Projectile::Draw() const
{
	if (typeid(*this) == typeid(Rocket))
		utils::SetColor(Color4f{ 1, 0, 0, 1 });
	if (typeid(*this) == typeid(ShotgunPellet))
		utils::SetColor(Color4f{ 255.f, 69.f, 0, 1 });
	if (typeid(*this) == typeid(MachinegunBullet))
		utils::SetColor(Color4f{ 1, 1, 0, 1 });
	utils::FillPolygon(GetCollider());
}

void Projectile::HitLevel(const Vector2f& /*dMove*/)
{
	Delete();
}

void Projectile::HandleCollision(float /*dT*/)
{
	PolygonCollisionResult result;

	if (m_pSender == m_pGameObjectManager->GetPlayer())
		for (GameObject* pGameObject : m_pGameObjectManager->GetEnemies())
		{
			result = sat::PolygonCollision(this, pGameObject);
			if (result.intersect)
			{
				static_cast<Enemy*>(pGameObject)->Hit(m_BaseDamage);
				Delete();
			}
		}
	else
	{
		result = sat::PolygonCollision(this, m_pGameObjectManager->GetPlayer());
		if (result.intersect)
		{
			m_pGameObjectManager->GetPlayer()->Hit(m_BaseDamage);
			Delete();
		}
	}
}
